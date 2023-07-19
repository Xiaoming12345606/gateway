#ifndef DEVICEWORKER_H
#define DEVICEWORKER_H
#define MAX_ARRAY_JSON_STR_LEN (512)
#define MAX_SAMPLE_ARRAY_SIZE (16)
#define TOTAL_PROPERTY_COUNT 32
#include <QObject>
#include <QThread>
#include "shareddata.h"
#include "QDebug"
#include <QVector>
#include <chrono>
#include <QDateTime>
#include "qcloud_iot_c_sdk/sdk_src/internal_inc/utils_timer.h"
#include "qcloud_iot_c_sdk/include/qcloud_iot_export.h"
#include "qcloud_iot_c_sdk/include/qcloud_iot_import.h"
#include "qcloud_iot_c_sdk/include/lite-utils.h"
#include "qcloud_iot_c_sdk/include/utils_getopt.h"
#include <cstring>
#ifdef EVENT_POST_ENABLED

#include "events_config.c"
static void update_events_timestamp(sEvent *pEvents, int count)
{
    int i;

    for (i = 0; i < count; i++) {
        if (NULL == (&pEvents[i])) {
            Log_e("null event pointer");
            return;
        }
#ifdef EVENT_TIMESTAMP_USED
        pEvents[i].timestamp = time(NULL);  // should be UTC and accurate
#else
        pEvents[i].timestamp = 0;
#endif
    }
}

static void event_post_cb(void *pClient, MQTTMessage *msg)
{
    Log_d("Reply:%.*s", msg->payload_len, msg->payload);
    //    IOT_Event_clearFlag(pClient, FLAG_EVENT0 | FLAG_EVENT1 | FLAG_EVENT2);
}

// event check and post
static void eventPostCheck(void *client)
{
    int      i;
    int      rc;
    uint32_t eflag;
    uint8_t  event_count;
    sEvent * pEventList[EVENT_COUNTS];

    eflag = IOT_Event_getFlag(client);
    if ((EVENT_COUNTS > 0) && (eflag > 0)) {
        event_count = 0;
        for (i = 0; i < EVENT_COUNTS; i++) {
            if ((eflag & (1 << i)) & ALL_EVENTS_MASK) {
                pEventList[event_count++] = &(g_events[i]);
                update_events_timestamp(&g_events[i], 1);
                IOT_Event_clearFlag(client, (1 << i) & ALL_EVENTS_MASK);
            }
        }

        rc = IOT_Post_Event(client, sg_data_report_buffer, sg_data_report_buffersize, event_count, pEventList,
                            event_post_cb);
        if (rc < 0) {
            Log_e("events post failed: %d", rc);
        }
    }
}

#endif

typedef struct _ProductDataDefine{
    TYPE_DEF_TEMPLATE_FLOAT m_temperature1;
       TYPE_DEF_TEMPLATE_FLOAT m_temperature2;
       TYPE_DEF_TEMPLATE_BOOL m_state1;
       TYPE_DEF_TEMPLATE_BOOL m_state2;
       TYPE_DEF_TEMPLATE_FLOAT m_voltage;
       TYPE_DEF_TEMPLATE_FLOAT m_current;
       TYPE_DEF_TEMPLATE_FLOAT m_temperature;
       TYPE_DEF_TEMPLATE_FLOAT m_atmosphere_pressure;
       TYPE_DEF_TEMPLATE_FLOAT m_distance;
       TYPE_DEF_TEMPLATE_BOOL m_GPIO1_state;
       TYPE_DEF_TEMPLATE_BOOL m_GPIO2_state;
       TYPE_DEF_TEMPLATE_BOOL m_GPIO3_state;
       TYPE_DEF_TEMPLATE_BOOL m_GPIO1_value;
       TYPE_DEF_TEMPLATE_BOOL m_GPIO2_value;
       TYPE_DEF_TEMPLATE_BOOL m_GPIO3_value;
       TYPE_DEF_TEMPLATE_BOOL m_current_state;
       TYPE_DEF_TEMPLATE_STRING m_V[2048+1];
       TYPE_DEF_TEMPLATE_STRING m_T1[2048+1];
       TYPE_DEF_TEMPLATE_STRING m_T1_S[2048+1];
       TYPE_DEF_TEMPLATE_STRING m_T2[2048+1];
       TYPE_DEF_TEMPLATE_STRING m_T2_S[2048+1];
       TYPE_DEF_TEMPLATE_STRING m_C[2048+1];
       TYPE_DEF_TEMPLATE_STRING m_P[2048+1];
       TYPE_DEF_TEMPLATE_STRING m_T[2048+1];
       TYPE_DEF_TEMPLATE_STRING m_C_S[2048+1];
       TYPE_DEF_TEMPLATE_STRING m_G1_S[2048+1];
       TYPE_DEF_TEMPLATE_STRING m_G2_S[2048+1];
       TYPE_DEF_TEMPLATE_STRING m_G3_S[2048+1];
       TYPE_DEF_TEMPLATE_STRING m_G1[2048+1];
       TYPE_DEF_TEMPLATE_STRING m_G2[2048+1];
       TYPE_DEF_TEMPLATE_STRING m_G3[2048+1];
       TYPE_DEF_TEMPLATE_STRING m_D[2048+1];
} ProductDataDefine;
#ifdef AUTH_MODE_CERT
static char sg_cert_file[PATH_MAX + 1];  // full path of device cert file
static char sg_key_file[PATH_MAX + 1];   // full path of device key file
#endif
#ifdef ACTION_ENABLED
#include "action_config.c"

// action : regist action and set the action handle callback, add your aciton logic here
static void OnActionCallback(void *pClient, const char *pClientToken, DeviceAction *pAction)
{
    int        i;
    sReplyPara replyPara;

    // do something base on input, just print as an sample
    DeviceProperty *pActionInput = pAction->pInput;
    for (i = 0; i < pAction->input_num; i++) {
        if (JSTRING == pActionInput[i].type) {
            Log_d("Input:[%s], data:[%s]", pActionInput[i].key, pActionInput[i].data);
        } else {
            if (JINT32 == pActionInput[i].type) {
                Log_d("Input:[%s], data:[%d]", pActionInput[i].key, *((int *)pActionInput[i].data));
            } else if (JFLOAT == pActionInput[i].type) {
                Log_d("Input:[%s], data:[%f]", pActionInput[i].key, *((float *)pActionInput[i].data));
            } else if (JUINT32 == pActionInput[i].type) {
                Log_d("Input:[%s], data:[%u]", pActionInput[i].key, *((uint32_t *)pActionInput[i].data));
            }
        }
    }

    // construct output
    memset((char *)&replyPara, 0, sizeof(sReplyPara));
    replyPara.code       = eDEAL_SUCCESS;
    replyPara.timeout_ms = QCLOUD_IOT_MQTT_COMMAND_TIMEOUT;
    strcpy(replyPara.status_msg, "action execute success!");  // add the message about the action resault

    DeviceProperty *pActionOutnput = pAction->pOutput;
    (void)pActionOutnput;  // elimate warning
    // TO DO: add your aciont logic here and set output properties which will be reported by action_reply

    IOT_Action_Reply(pClient, pClientToken, sg_data_report_buffer, sg_data_report_buffersize, pAction, &replyPara);
}

static int _register_data_template_action(void *pTemplate_client)
{
    int i, rc;

    for (i = 0; i < TOTAL_ACTION_COUNTS; i++) {
        rc = IOT_Template_Register_Action(pTemplate_client, &g_actions[i], OnActionCallback);
        if (rc != QCLOUD_RET_SUCCESS) {
            rc = IOT_Template_Destroy(pTemplate_client);
            Log_e("register device data template action failed, err: %d", rc);
            return rc;
        } else {
            Log_i("data template action=%s registered.", g_actions[i].pActionId);
        }
    }

    return QCLOUD_RET_SUCCESS;
}
#endif
class DeviceWorker : public QObject
{
    Q_OBJECT
public:
    explicit DeviceWorker(QObject *parent = nullptr);
       ~DeviceWorker();
    static void _init_data_template();
    static void event_handler(void *pclient, void *handle_context, MQTTEventMsg *msg);
    static int _setup_connect_init_params(TemplateInitParams *initParams);
    static void OnControlMsgCallback(void *pClient, const char *pJsonValueBuffer, uint32_t valueLength,
                                     DeviceProperty *pProperty);
    static void OnReportReplyCallback(void *pClient, Method method, ReplyAck
                                      replyAck, const char *pJsonDocument,
                                      void *pUserdata);
    static int _register_data_template_property(void *pTemplate_client);
    void deal_down_stream_user_logic(void *client, ProductDataDefine *pData);
    static void set_property_state(void *pProperyData, eDataState state);
    static void cycle_report(Timer *reportTimer);
    static void _refresh_local_property(void);
    static int find_wait_report_property(DeviceProperty *pReportDataList[]);
    int deal_up_stream_user_logic(DeviceProperty *pReportDataList[], int *pCount);
    static int _get_sys_info(void *handle, char *pJsonDoc, size_t sizeOfBuffer);
    static int parse_arguments(int argc, char **argv);
    
  
    static void refreshOnlineData();
    
      
      /* offline data upload */
      static void storeDataLocally(const QString& data,  QVector<QString>& dataStorage);
      static void uploadOfflineData(char* data,int up,int order,QVector<QString>& dataStorage);
      static int numberChange(int up,QVector<QString>& dataStorage);


      //offline zigbee*4
      static QVector<QString> dataStorage_temperature1;
      //static int offline_count_temperature1;
      static int temperature1_i;
      static QVector<QString> dataStorage_temperature2;
      //static int offline_count_temperature2;
      static int temperature2_i;
      static QVector<QString> dataStorage_temperature1_state;
      //static int offline_count_temperature1_state;
      static int temperature1_state_i;
      static QVector<QString> dataStorage_temperature2_state;
      //static int offline_count_temperature2_state;
      static int temperature2_state_i;

      //offline ADC *5
      // voltage
      static QVector<QString> dataStorage_voltage;
      //static int offline_count_voltage;
      static int voltage_i;
      //current
      static QVector<QString> dataStorage_current;
      //static int offline_count_current;
      static int current_i;
      //pressure
      static QVector<QString> dataStorage_pressure;
      //static int offline_count_pressure;
      static int pressure_i;
      //temperature
      static QVector<QString> dataStorage_temperature;
      //static int offline_count_temoerature;
      static int temperature_i;
      //Current_state
      static QVector<QString> dataStorage_current_state;
      //static int offline_count_current_state;
      static int current_state_i;
      
      //offline distance
      static QVector<QString> dataStorage_distance;
      //static int offline_count_distance;
      static int distance_i;

      //offline GPIO*6
      static QVector<QString> dataStorage_gpio1_state;
      //static int offline_count_gpio1_state;
      static int gpio1_state_i;
      static QVector<QString> dataStorage_gpio2_state;
      //static int offline_count_gpio2_state;
      static int gpio2_state_i;
      static QVector<QString> dataStorage_gpio3_state;
      //static int offline_count_gpio3_state;
      static int gpio3_state_i;
      static QVector<QString> dataStorage_gpio1;
      //static int offline_count_gpio1;
      static int gpio1_i;
      static QVector<QString> dataStorage_gpio2;
      //static int offline_count_gpio2;
      static int gpio2_i;
      static QVector<QString> dataStorage_gpio3;
      //static int offline_count_gpio3;
      static int gpio3_i;

private:
    //Ui::Widget *ui;
    static sDataPoint    sg_DataTemplate[TOTAL_PROPERTY_COUNT];
    static   ProductDataDefine     sg_ProductData;
    
    static DeviceInfo    sg_devInfo;
    static Timer      sg_reportTimer;
    static MQTTEventType sg_subscribe_event_result;
    static bool          sg_control_msg_arrived;
    static char          sg_data_report_buffer[2048];
    static size_t        sg_data_report_buffersize ;
    static bool lxstate;
   // static QString tmp;
    //static float temperature1;
    //static float temperature2;
    //static uart u;
public slots:
    int runDeviceTemplate();//main
    //void readSerialData();
};
#endif // DEVICEWORKER_H
