/*
 * Tencent is pleased to support the open source community by making IoT Hub
 available.
 * Copyright (C) 2016 THL A29 Limited, a Tencent company. All rights reserved.

 * Licensed under the MIT License (the "License"); you may not use this file
 except in
 * compliance with the License. You may obtain a copy of the License at
 * http://opensource.org/licenses/MIT

 * Unless required by applicable law or agreed to in writing, software
 distributed under the License is
 * distributed on an "AS IS" basis, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 KIND,
 * either express or implied. See the License for the specific language
 governing permissions and
 * limitations under the License.
 *
 */

#ifdef __cplusplus
extern "C" {
#endif

#include "qcloud_iot_c_sdk/sdk_src/internal_inc/data_template_client_json.h"

#include <inttypes.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "qcloud_iot_c_sdk/include/lite-utils.h"
#include "qcloud_iot_c_sdk/sdk_src/internal_inc/qcloud_iot_device.h"
#include "qcloud_iot_c_sdk/include/exports/qcloud_iot_export_method.h"

int check_snprintf_return(int32_t returnCode, size_t maxSizeOfWrite)
{
    if (returnCode >= maxSizeOfWrite) {
        return QCLOUD_ERR_JSON_BUFFER_TRUNCATED;
    } else if (returnCode < 0) {  // err
        return QCLOUD_ERR_JSON;
    }

    return QCLOUD_RET_SUCCESS;
}

void insert_str(char *pDestStr, char *pSourceStr, int pos)
{
    int len  = strlen(pDestStr);
    int nlen = strlen(pSourceStr);
    int i;
    for (i = len - 1; i >= pos; --i) {
        *(pDestStr + i + nlen) = *(pDestStr + i);
    }

    int n;
    for (n = 0; n < nlen; n++) *(pDestStr + pos + n) = *pSourceStr++;
    *(pDestStr + len + nlen) = 0;
}

static int _direct_update_value(char *value, DeviceProperty *pProperty)
{
    int      rc    = QCLOUD_RET_SUCCESS;
    uint16_t index = 0;

    switch (pProperty->type) {
        case JBOOL:
            rc = LITE_get_boolean(pProperty->data, value);
            break;
        case JINT32:
            rc = LITE_get_int32(pProperty->data, value);
            break;
        case JINT16:
            rc = LITE_get_int16(pProperty->data, value);
            break;
        case JINT8:
            rc = LITE_get_int8(pProperty->data, value);
            break;
        case JUINT32:
            rc = LITE_get_uint32(pProperty->data, value);
            break;
        case JUINT16:
            rc = LITE_get_uint16(pProperty->data, value);
            break;
        case JUINT8:
            rc = LITE_get_uint8(pProperty->data, value);
            break;
        case JFLOAT:
            rc = LITE_get_float(pProperty->data, value);
            break;
        case JDOUBLE:
            rc = LITE_get_double(pProperty->data, value);
            break;
        case JSTRING:
            Log_d("property data_buff_len %d", pProperty->data_buff_len);
            rc = LITE_get_string(pProperty->data, value, pProperty->data_buff_len);
            break;
        case JOBJECT:
            for (index = 0; index < pProperty->struct_obj_num; index++) {
                DeviceProperty *pJsonNode = &((((sDataPoint *)(pProperty->data)) + index)->data_property);
                if ((pJsonNode != NULL) && (pJsonNode->key != NULL)) {
                    update_value_if_key_match(value, pJsonNode);
                }
            }
            break;
        case JARRAY:
            rc = LITE_get_string(pProperty->data, value, pProperty->data_buff_len);
            break;
        default:
            Log_e("Unknown type %d", pProperty->type);
            break;
    }

    return rc;
}

static int _format_json_buffer(char *jsonBuffer, size_t remain_size, int type, void *pData)
{
    int rc_of_snprintf = -1;
    switch (type) {
        case JINT32:
            rc_of_snprintf = HAL_Snprintf(jsonBuffer, remain_size, "%" PRIi32 ",", *(int32_t *)(pData));
            break;
        case JINT16:
            rc_of_snprintf = HAL_Snprintf(jsonBuffer, remain_size, "%" PRIi16 ",", *(int16_t *)(pData));
            break;
        case JINT8:
            rc_of_snprintf = HAL_Snprintf(jsonBuffer, remain_size, "%" PRIi8 ",", *(int8_t *)(pData));
            break;
        case JUINT32:
            rc_of_snprintf = HAL_Snprintf(jsonBuffer, remain_size, "%" PRIu32 ",", *(uint32_t *)(pData));
            break;
        case JUINT16:
            rc_of_snprintf = HAL_Snprintf(jsonBuffer, remain_size, "%" PRIu16 ",", *(uint16_t *)(pData));
            break;
        case JUINT8:
            rc_of_snprintf = HAL_Snprintf(jsonBuffer, remain_size, "%" PRIu8 ",", *(uint8_t *)(pData));
            break;
        case JDOUBLE:
            rc_of_snprintf = HAL_Snprintf(jsonBuffer, remain_size, "%f,", *(double *)(pData));
            break;
        case JFLOAT:
            rc_of_snprintf = HAL_Snprintf(jsonBuffer, remain_size, "%f,", *(float *)(pData));
            break;
        case JSTRING:
            rc_of_snprintf = HAL_Snprintf(jsonBuffer, remain_size, "\"%s\",", (char *)(pData));
            break;
        default:
            Log_e("Shouldnt reach here");
            break;
    }

    return rc_of_snprintf;
}

int put_json_node(char *jsonBuffer, size_t sizeOfBuffer, DeviceProperty *pJsonNode)
{
    int          rc;
    int32_t      rc_of_snprintf = 0;
    size_t       remain_size    = 0;
    size_t       current_size   = 0;
    char *       pKey           = pJsonNode->key;
    void *       pData          = pJsonNode->data;
    JsonDataType type           = pJsonNode->type;

    current_size = strlen(jsonBuffer);
    if ((ssize_t)(remain_size = sizeOfBuffer - current_size) <= 1) {
        return QCLOUD_ERR_JSON_BUFFER_TOO_SMALL;
    }

    rc_of_snprintf =
        HAL_Snprintf(jsonBuffer + current_size, remain_size, "\"%s\":", STRING_PTR_PRINT_SANITY_CHECK(pKey));
    rc = check_snprintf_return(rc_of_snprintf, remain_size);
    if (rc != QCLOUD_RET_SUCCESS) {
        return rc;
    }
    current_size += rc_of_snprintf;

    if ((ssize_t)(remain_size = sizeOfBuffer - current_size) <= 1) {
        return QCLOUD_ERR_JSON_BUFFER_TOO_SMALL;
    }

    if (pData == NULL) {
        rc_of_snprintf = HAL_Snprintf(jsonBuffer + current_size, remain_size, "null,");
        return check_snprintf_return(rc_of_snprintf, remain_size);
    }

    if (type != JBOOL && type != JOBJECT && type != JARRAY) {
        return check_snprintf_return(_format_json_buffer(jsonBuffer + current_size, remain_size, type, pData),
                                     remain_size);
    }

    switch (type) {
        case JBOOL:
            rc_of_snprintf =
                HAL_Snprintf(jsonBuffer + current_size, remain_size, "%s,", *(bool *)(pData) ? "true" : "false");
            break;
        case JOBJECT:
            rc_of_snprintf = HAL_Snprintf(jsonBuffer + current_size, remain_size, "{");
            rc             = check_snprintf_return(rc_of_snprintf, remain_size);
            if (rc != QCLOUD_RET_SUCCESS) {
                return rc;
            }
            current_size += rc_of_snprintf;
            remain_size = sizeOfBuffer - current_size;
            if ((ssize_t)remain_size <= 1) {
                return QCLOUD_ERR_JSON_BUFFER_TOO_SMALL;
            }
            uint16_t index = 0;

            for (index = 0; index < pJsonNode->struct_obj_num; index++) {
                DeviceProperty *pNode = &((((sDataPoint *)(pJsonNode->data)) + index)->data_property);
                if ((pNode != NULL) && (pNode->key) != NULL) {
                    rc = put_json_node(jsonBuffer + current_size, remain_size, pNode);
                    if (rc != QCLOUD_RET_SUCCESS) {
                        return rc;
                    }
                    current_size = strlen(jsonBuffer);
                    remain_size  = sizeOfBuffer - current_size;
                    if ((ssize_t)remain_size <= 1) {
                        return QCLOUD_ERR_JSON_BUFFER_TOO_SMALL;
                    }
                }
            }
            rc_of_snprintf = HAL_Snprintf(jsonBuffer + current_size - 1, remain_size, "},");
            break;
        case JARRAY:
            rc_of_snprintf = HAL_Snprintf(jsonBuffer + current_size, remain_size, "%s,", (char *)(pData));
            break;
        default:
            Log_e("Type %d is unknown", type);
            break;
    }

    rc = check_snprintf_return(rc_of_snprintf, remain_size);

    return rc;
}

int template_put_json_node(char *jsonBuffer, size_t sizeOfBuffer, const char *pKey, void *pData, JsonDataType type)
{
    int     rc;
    int32_t rc_of_snprintf = 0;
    size_t  current_size   = strlen(jsonBuffer);
    size_t  remain_size    = sizeOfBuffer - current_size;

    if ((ssize_t)remain_size <= 1) {
        return QCLOUD_ERR_JSON_BUFFER_TOO_SMALL;
    }

    rc_of_snprintf =
        HAL_Snprintf(jsonBuffer + current_size, remain_size, "\"%s\":", STRING_PTR_PRINT_SANITY_CHECK(pKey));
    rc = check_snprintf_return(rc_of_snprintf, remain_size);
    if (rc != QCLOUD_RET_SUCCESS) {
        return rc;
    }

    current_size += rc_of_snprintf;
    if ((ssize_t)(remain_size = sizeOfBuffer - current_size) <= 1) {
        return QCLOUD_ERR_JSON_BUFFER_TOO_SMALL;
    }

    if (pData == NULL) {
        rc_of_snprintf = HAL_Snprintf(jsonBuffer + current_size, remain_size, "null,");
        return check_snprintf_return(rc_of_snprintf, remain_size);
    }

    if (type != JBOOL && type != JOBJECT && type != JARRAY) {
        return check_snprintf_return(_format_json_buffer(jsonBuffer + current_size, remain_size, type, pData),
                                     remain_size);
    }

    switch (type) {
        case JBOOL:
            rc_of_snprintf = HAL_Snprintf(jsonBuffer + current_size, remain_size, "%u,", *(bool *)(pData) ? 1 : 0);
            break;
        case JOBJECT:
            rc_of_snprintf = HAL_Snprintf(jsonBuffer + current_size, remain_size, "%s,", (char *)(pData));
            break;
        case JARRAY:
            rc_of_snprintf = HAL_Snprintf(jsonBuffer + current_size, remain_size, "\"%s\",", (char *)(pData));
            break;
        default:
            Log_e("Unknown type %d", type);
            break;
    }

    rc = check_snprintf_return(rc_of_snprintf, remain_size);

    return rc;
}

void build_empty_json(uint32_t *tokenNumber, char *pJsonBuffer, char *tokenPrefix)
{
    HAL_Snprintf(pJsonBuffer, MAX_SIZE_OF_JSON_WITH_CLIENT_TOKEN, "{\"clientToken\":\"%s-%u\"}",
                 STRING_PTR_PRINT_SANITY_CHECK(tokenPrefix), (*tokenNumber)++);
}

bool parse_client_token(char *pJsonDoc, char **pClientToken)
{
    *pClientToken = LITE_json_value_of(CLIENT_TOKEN_FIELD, pJsonDoc);
    return *pClientToken == NULL ? false : true;
}

bool parse_action_id(char *pJsonDoc, char **pActionID)
{
    *pActionID = LITE_json_value_of(ACTION_ID_FIELD, pJsonDoc);
    return *pActionID == NULL ? false : true;
}

bool parse_time_stamp(char *pJsonDoc, int32_t *pTimestamp)
{
    bool ret = false;

    char *timestamp = LITE_json_value_of(TIME_STAMP_FIELD, pJsonDoc);
    if (timestamp == NULL)
        return false;

    if (sscanf(timestamp, "%" SCNu32, pTimestamp) != 1) {
        Log_e("parse code failed, errCode: %d", QCLOUD_ERR_JSON_PARSE);
    } else {
        ret = true;
    }

    HAL_Free(timestamp);

    return ret;
}

bool parse_action_input(char *pJsonDoc, char **pActionInput)
{
    *pActionInput = LITE_json_value_of(CMD_CONTROL_PARA, pJsonDoc);
    return *pActionInput == NULL ? false : true;
}

bool parse_code_return(char *pJsonDoc, int32_t *pCode)
{
    bool ret = false;

    char *code = LITE_json_value_of(REPLY_CODE, pJsonDoc);
    if (code == NULL)
        return false;

    if (sscanf(code, "%" SCNi32, pCode) != 1) {
        Log_e("parse code failed, errCode: %d", QCLOUD_ERR_JSON_PARSE);
    } else {
        ret = true;
    }

    HAL_Free(code);

    return ret;
}

bool parse_status_return(char *pJsonDoc, char **pStatus)
{
    *pStatus = LITE_json_value_of(REPLY_STATUS, pJsonDoc);
    return *pStatus == NULL ? false : true;
}

bool update_value_if_key_match(char *pJsonDoc, DeviceProperty *pProperty)
{
    bool ret = false;

    char *property_data = LITE_json_value_of(pProperty->key, pJsonDoc);
    if ((property_data == NULL) || !(strncmp(property_data, "null", 4)) || !(strncmp(property_data, "NULL", 4))) {
        ret = false;
    } else {
        _direct_update_value(property_data, pProperty);
        ret = true;
    }

    HAL_Free(property_data);

    return ret;
}

bool parse_template_method_type(char *pJsonDoc, char **pMethod)
{
    *pMethod = LITE_json_value_of(METHOD_FIELD, pJsonDoc);
    return *pMethod == NULL ? false : true;
}

bool parse_template_get_control(char *pJsonDoc, char **control)
{
    *control = LITE_json_value_of(GET_CONTROL_PARA, pJsonDoc);
    return *control == NULL ? false : true;
}

bool parse_template_cmd_control(char *pJsonDoc, char **control)
{
    *control = LITE_json_value_of(CMD_CONTROL_PARA, pJsonDoc);
    return *control == NULL ? false : true;
}

#ifdef __cplusplus
}
#endif
