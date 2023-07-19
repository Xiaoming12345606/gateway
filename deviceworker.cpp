#include "deviceworker.h"
#include <QCoreApplication>
#include <QDebug>
DeviceWorker::DeviceWorker(QObject *parent)
    : QObject(parent)
{
    // 构造函数实现
}
void DeviceWorker::_init_data_template()
{
       sg_ProductData.m_temperature1 = 0;
        sg_DataTemplate[0].data_property.data = &sg_ProductData.m_temperature1;
        sg_DataTemplate[0].data_property.key  = "temperature1";
        sg_DataTemplate[0].data_property.type = TYPE_TEMPLATE_FLOAT;
        sg_DataTemplate[0].state = eCHANGED;
    
        sg_ProductData.m_temperature2 = 0;
        sg_DataTemplate[1].data_property.data = &sg_ProductData.m_temperature2;
        sg_DataTemplate[1].data_property.key  = "temperature2";
        sg_DataTemplate[1].data_property.type = TYPE_TEMPLATE_FLOAT;
        sg_DataTemplate[1].state = eCHANGED;
    
        sg_ProductData.m_state1 = 0;
        sg_DataTemplate[2].data_property.data = &sg_ProductData.m_state1;
        sg_DataTemplate[2].data_property.key  = "state1";
        sg_DataTemplate[2].data_property.type = TYPE_TEMPLATE_BOOL;
        sg_DataTemplate[2].state = eCHANGED;
    
        sg_ProductData.m_state2 = 0;
        sg_DataTemplate[3].data_property.data = &sg_ProductData.m_state2;
        sg_DataTemplate[3].data_property.key  = "state2";
        sg_DataTemplate[3].data_property.type = TYPE_TEMPLATE_BOOL;
        sg_DataTemplate[3].state = eCHANGED;
    
        sg_ProductData.m_voltage = 0;
        sg_DataTemplate[4].data_property.data = &sg_ProductData.m_voltage;
        sg_DataTemplate[4].data_property.key  = "voltage";
        sg_DataTemplate[4].data_property.type = TYPE_TEMPLATE_FLOAT;
        sg_DataTemplate[4].state = eCHANGED;
    
        sg_ProductData.m_current = 0;
        sg_DataTemplate[5].data_property.data = &sg_ProductData.m_current;
        sg_DataTemplate[5].data_property.key  = "current";
        sg_DataTemplate[5].data_property.type = TYPE_TEMPLATE_FLOAT;
        sg_DataTemplate[5].state = eCHANGED;
    
        sg_ProductData.m_temperature = 0;
        sg_DataTemplate[6].data_property.data = &sg_ProductData.m_temperature;
        sg_DataTemplate[6].data_property.key  = "temperature";
        sg_DataTemplate[6].data_property.type = TYPE_TEMPLATE_FLOAT;
        sg_DataTemplate[6].state = eCHANGED;
    
        sg_ProductData.m_atmosphere_pressure = 0;
        sg_DataTemplate[7].data_property.data = &sg_ProductData.m_atmosphere_pressure;
        sg_DataTemplate[7].data_property.key  = "atmosphere_pressure";
        sg_DataTemplate[7].data_property.type = TYPE_TEMPLATE_FLOAT;
        sg_DataTemplate[7].state = eCHANGED;
    
        sg_ProductData.m_distance = 0;
        sg_DataTemplate[8].data_property.data = &sg_ProductData.m_distance;
        sg_DataTemplate[8].data_property.key  = "distance";
        sg_DataTemplate[8].data_property.type = TYPE_TEMPLATE_FLOAT;
        sg_DataTemplate[8].state = eCHANGED;
    
        sg_ProductData.m_GPIO1_state = 0;
        sg_DataTemplate[9].data_property.data = &sg_ProductData.m_GPIO1_state;
        sg_DataTemplate[9].data_property.key  = "GPIO1_state";
        sg_DataTemplate[9].data_property.type = TYPE_TEMPLATE_BOOL;
        sg_DataTemplate[9].state = eCHANGED;
    
        sg_ProductData.m_GPIO2_state = 0;
        sg_DataTemplate[10].data_property.data = &sg_ProductData.m_GPIO2_state;
        sg_DataTemplate[10].data_property.key  = "GPIO2_state";
        sg_DataTemplate[10].data_property.type = TYPE_TEMPLATE_BOOL;
        sg_DataTemplate[10].state = eCHANGED;
    
        sg_ProductData.m_GPIO3_state = 0;
        sg_DataTemplate[11].data_property.data = &sg_ProductData.m_GPIO3_state;
        sg_DataTemplate[11].data_property.key  = "GPIO3_state";
        sg_DataTemplate[11].data_property.type = TYPE_TEMPLATE_BOOL;
        sg_DataTemplate[11].state = eCHANGED;
    
        sg_ProductData.m_GPIO1_value = 0;
        sg_DataTemplate[12].data_property.data = &sg_ProductData.m_GPIO1_value;
        sg_DataTemplate[12].data_property.key  = "GPIO1_value";
        sg_DataTemplate[12].data_property.type = TYPE_TEMPLATE_BOOL;
        sg_DataTemplate[12].state = eCHANGED;
    
        sg_ProductData.m_GPIO2_value = 0;
        sg_DataTemplate[13].data_property.data = &sg_ProductData.m_GPIO2_value;
        sg_DataTemplate[13].data_property.key  = "GPIO2_value";
        sg_DataTemplate[13].data_property.type = TYPE_TEMPLATE_BOOL;
        sg_DataTemplate[13].state = eCHANGED;
    
        sg_ProductData.m_GPIO3_value = 0;
        sg_DataTemplate[14].data_property.data = &sg_ProductData.m_GPIO3_value;
        sg_DataTemplate[14].data_property.key  = "GPIO3_value";
        sg_DataTemplate[14].data_property.type = TYPE_TEMPLATE_BOOL;
        sg_DataTemplate[14].state = eCHANGED;
    
        sg_ProductData.m_current_state = 0;
        sg_DataTemplate[15].data_property.data = &sg_ProductData.m_current_state;
        sg_DataTemplate[15].data_property.key  = "current_state";
        sg_DataTemplate[15].data_property.type = TYPE_TEMPLATE_BOOL;
        sg_DataTemplate[15].state = eCHANGED;

            sg_ProductData.m_V[0] = '\0';
            sg_DataTemplate[16].data_property.data = sg_ProductData.m_V;
            sg_DataTemplate[16].data_property.data_buff_len = sizeof(sg_ProductData.m_V)/sizeof(sg_ProductData.m_V[0]);
            sg_DataTemplate[16].data_property.key  = "V";
            sg_DataTemplate[16].data_property.type = TYPE_TEMPLATE_STRING;
            sg_DataTemplate[16].state = eCHANGED;

            sg_ProductData.m_T1[0] = '\0';
            sg_DataTemplate[17].data_property.data = sg_ProductData.m_T1;
            sg_DataTemplate[17].data_property.data_buff_len = sizeof(sg_ProductData.m_T1)/sizeof(sg_ProductData.m_T1[0]);
            sg_DataTemplate[17].data_property.key  = "T1";
            sg_DataTemplate[17].data_property.type = TYPE_TEMPLATE_STRING;
            sg_DataTemplate[17].state = eCHANGED;

            sg_ProductData.m_T1_S[0] = '\0';
            sg_DataTemplate[18].data_property.data = sg_ProductData.m_T1_S;
            sg_DataTemplate[18].data_property.data_buff_len = sizeof(sg_ProductData.m_T1_S)/sizeof(sg_ProductData.m_T1_S[0]);
            sg_DataTemplate[18].data_property.key  = "T1_S";
            sg_DataTemplate[18].data_property.type = TYPE_TEMPLATE_STRING;
            sg_DataTemplate[18].state = eCHANGED;

            sg_ProductData.m_T2[0] = '\0';
            sg_DataTemplate[19].data_property.data = sg_ProductData.m_T2;
            sg_DataTemplate[19].data_property.data_buff_len = sizeof(sg_ProductData.m_T2)/sizeof(sg_ProductData.m_T2[0]);
            sg_DataTemplate[19].data_property.key  = "T2";
            sg_DataTemplate[19].data_property.type = TYPE_TEMPLATE_STRING;
            sg_DataTemplate[19].state = eCHANGED;

            sg_ProductData.m_T2_S[0] = '\0';
            sg_DataTemplate[20].data_property.data = sg_ProductData.m_T2_S;
            sg_DataTemplate[20].data_property.data_buff_len = sizeof(sg_ProductData.m_T2_S)/sizeof(sg_ProductData.m_T2_S[0]);
            sg_DataTemplate[20].data_property.key  = "T2_S";
            sg_DataTemplate[20].data_property.type = TYPE_TEMPLATE_STRING;
            sg_DataTemplate[20].state = eCHANGED;

            sg_ProductData.m_C[0] = '\0';
            sg_DataTemplate[21].data_property.data = sg_ProductData.m_C;
            sg_DataTemplate[21].data_property.data_buff_len = sizeof(sg_ProductData.m_C)/sizeof(sg_ProductData.m_C[0]);
            sg_DataTemplate[21].data_property.key  = "C";
            sg_DataTemplate[21].data_property.type = TYPE_TEMPLATE_STRING;
            sg_DataTemplate[21].state = eCHANGED;

            sg_ProductData.m_P[0] = '\0';
            sg_DataTemplate[22].data_property.data = sg_ProductData.m_P;
            sg_DataTemplate[22].data_property.data_buff_len = sizeof(sg_ProductData.m_P)/sizeof(sg_ProductData.m_P[0]);
            sg_DataTemplate[22].data_property.key  = "P";
            sg_DataTemplate[22].data_property.type = TYPE_TEMPLATE_STRING;
            sg_DataTemplate[22].state = eCHANGED;

            sg_ProductData.m_T[0] = '\0';
            sg_DataTemplate[23].data_property.data = sg_ProductData.m_T;
            sg_DataTemplate[23].data_property.data_buff_len = sizeof(sg_ProductData.m_T)/sizeof(sg_ProductData.m_T[0]);
            sg_DataTemplate[23].data_property.key  = "T";
            sg_DataTemplate[23].data_property.type = TYPE_TEMPLATE_STRING;
            sg_DataTemplate[23].state = eCHANGED;

            sg_ProductData.m_C_S[0] = '\0';
            sg_DataTemplate[24].data_property.data = sg_ProductData.m_C_S;
            sg_DataTemplate[24].data_property.data_buff_len = sizeof(sg_ProductData.m_C_S)/sizeof(sg_ProductData.m_C_S[0]);
            sg_DataTemplate[24].data_property.key  = "C_S";
            sg_DataTemplate[24].data_property.type = TYPE_TEMPLATE_STRING;
            sg_DataTemplate[24].state = eCHANGED;

            sg_ProductData.m_G1_S[0] = '\0';
            sg_DataTemplate[25].data_property.data = sg_ProductData.m_G1_S;
            sg_DataTemplate[25].data_property.data_buff_len = sizeof(sg_ProductData.m_G1_S)/sizeof(sg_ProductData.m_G1_S[0]);
            sg_DataTemplate[25].data_property.key  = "G1_S";
            sg_DataTemplate[25].data_property.type = TYPE_TEMPLATE_STRING;
            sg_DataTemplate[25].state = eCHANGED;

            sg_ProductData.m_G2_S[0] = '\0';
            sg_DataTemplate[26].data_property.data = sg_ProductData.m_G2_S;
            sg_DataTemplate[26].data_property.data_buff_len = sizeof(sg_ProductData.m_G2_S)/sizeof(sg_ProductData.m_G2_S[0]);
            sg_DataTemplate[26].data_property.key  = "G2_S";
            sg_DataTemplate[26].data_property.type = TYPE_TEMPLATE_STRING;
            sg_DataTemplate[26].state = eCHANGED;

            sg_ProductData.m_G3_S[0] = '\0';
            sg_DataTemplate[27].data_property.data = sg_ProductData.m_G3_S;
            sg_DataTemplate[27].data_property.data_buff_len = sizeof(sg_ProductData.m_G3_S)/sizeof(sg_ProductData.m_G3_S[0]);
            sg_DataTemplate[27].data_property.key  = "G3_S";
            sg_DataTemplate[27].data_property.type = TYPE_TEMPLATE_STRING;
            sg_DataTemplate[27].state = eCHANGED;

            sg_ProductData.m_G1[0] = '\0';
            sg_DataTemplate[28].data_property.data = sg_ProductData.m_G1;
            sg_DataTemplate[28].data_property.data_buff_len = sizeof(sg_ProductData.m_G1)/sizeof(sg_ProductData.m_G1[0]);
            sg_DataTemplate[28].data_property.key  = "G1";
            sg_DataTemplate[28].data_property.type = TYPE_TEMPLATE_STRING;
            sg_DataTemplate[28].state = eCHANGED;

            sg_ProductData.m_G2[0] = '\0';
            sg_DataTemplate[29].data_property.data = sg_ProductData.m_G2;
            sg_DataTemplate[29].data_property.data_buff_len = sizeof(sg_ProductData.m_G2)/sizeof(sg_ProductData.m_G2[0]);
            sg_DataTemplate[29].data_property.key  = "G2";
            sg_DataTemplate[29].data_property.type = TYPE_TEMPLATE_STRING;
            sg_DataTemplate[29].state = eCHANGED;

            sg_ProductData.m_G3[0] = '\0';
            sg_DataTemplate[30].data_property.data = sg_ProductData.m_G3;
            sg_DataTemplate[30].data_property.data_buff_len = sizeof(sg_ProductData.m_G3)/sizeof(sg_ProductData.m_G3[0]);
            sg_DataTemplate[30].data_property.key  = "G3";
            sg_DataTemplate[30].data_property.type = TYPE_TEMPLATE_STRING;
            sg_DataTemplate[30].state = eCHANGED;

            sg_ProductData.m_D[0] = '\0';
            sg_DataTemplate[31].data_property.data = sg_ProductData.m_D;
            sg_DataTemplate[31].data_property.data_buff_len = sizeof(sg_ProductData.m_D)/sizeof(sg_ProductData.m_D[0]);
            sg_DataTemplate[31].data_property.key  = "D";
            sg_DataTemplate[31].data_property.type = TYPE_TEMPLATE_STRING;
            sg_DataTemplate[31].state = eCHANGED;

}
ProductDataDefine DeviceWorker::sg_ProductData;
sDataPoint DeviceWorker::sg_DataTemplate[TOTAL_PROPERTY_COUNT];

DeviceInfo DeviceWorker::sg_devInfo;
Timer DeviceWorker::sg_reportTimer;
char  DeviceWorker:: sg_data_report_buffer[2048];
MQTTEventType  DeviceWorker::sg_subscribe_event_result = MQTT_EVENT_UNDEF;
bool  DeviceWorker::sg_control_msg_arrived    = false;
bool  DeviceWorker::lxstate    = false;
size_t   DeviceWorker::sg_data_report_buffersize = sizeof(sg_data_report_buffer) / sizeof(sg_data_report_buffer[0]);
//Temperature DeviceWorker::t;
//ADC DeviceWorker::adc;
 //GPIO DeviceWorker::g;
//GPIO DeviceWorker::g;

//offline zigbee*4
 QVector<QString> DeviceWorker:: dataStorage_temperature1;
 //int  DeviceWorker::offline_count_temperature1=0;
 int  DeviceWorker::temperature1_i=0;
 QVector<QString> DeviceWorker:: dataStorage_temperature2;
 //int  DeviceWorker::offline_count_temperature2=0;
 int  DeviceWorker::temperature2_i=0;
 QVector<QString> DeviceWorker::dataStorage_temperature1_state;
 //int DeviceWorker::offline_count_temperature1_state=0;
 int DeviceWorker::temperature1_state_i=0;
 QVector<QString> DeviceWorker::dataStorage_temperature2_state;
 //int DeviceWorker::offline_count_temperature2_state=0;
 int DeviceWorker::temperature2_state_i=0;
//offline ADC *5
// voltage
 QVector<QString> DeviceWorker::dataStorage_voltage;
 //int DeviceWorker::offline_count_voltage=0;
 int DeviceWorker::voltage_i=0;
 // current
 QVector<QString> DeviceWorker::dataStorage_current;
 //int DeviceWorker::offline_count_current=0;
 int DeviceWorker::current_i=0;
 //pressure
 QVector<QString> DeviceWorker:: dataStorage_pressure;
 //int DeviceWorker::offline_count_pressure=0;
 int DeviceWorker::pressure_i=0;
 //temperature
 QVector<QString> DeviceWorker::dataStorage_temperature;
 //int DeviceWorker::offline_count_temoerature=0;
 int DeviceWorker::temperature_i=0;
 //Current_state
 QVector<QString> DeviceWorker::dataStorage_current_state;
 //int DeviceWorker::offline_count_current_state=0;
 int DeviceWorker::current_state_i=0;


 //offline distance
 QVector<QString> DeviceWorker::dataStorage_distance;
 //int DeviceWorker::offline_count_distance=0;
 int DeviceWorker::distance_i=0;

 //offline GPIO*6
 QVector<QString> DeviceWorker::dataStorage_gpio1_state;
// int DeviceWorker::offline_count_gpio1_state=0;
 int DeviceWorker::gpio1_state_i=0;
 QVector<QString> DeviceWorker::dataStorage_gpio2_state;
 //int DeviceWorker::offline_count_gpio2_state=0;
 int DeviceWorker::gpio2_state_i=0;
 QVector<QString> DeviceWorker::dataStorage_gpio3_state;
 //int DeviceWorker::offline_count_gpio3_state=0;
 int DeviceWorker::gpio3_state_i=0;
 QVector<QString> DeviceWorker::dataStorage_gpio1;
 //int DeviceWorker::offline_count_gpio1=0;
 int DeviceWorker::gpio1_i=0;
 QVector<QString> DeviceWorker::dataStorage_gpio2;
 //int DeviceWorker::offline_count_gpio2=0;
 int DeviceWorker::gpio2_i=0;
 QVector<QString> DeviceWorker::dataStorage_gpio3;
 //int DeviceWorker::offline_count_gpio3=0;
 int DeviceWorker::gpio3_i=0;

/* shared data function */

void DeviceWorker::event_handler(void *pclient, void *handle_context, MQTTEventMsg *msg)
{
    uintptr_t packet_id = (uintptr_t)msg->msg;

    switch (msg->event_type) {
        case MQTT_EVENT_UNDEF:
            Log_i("undefined event occur.");
            break;
        case MQTT_EVENT_DISCONNECT:
            Log_i("MQTT disconnect.");
            break;
    case MQTT_EVENT_RECONNECT:
        Log_i("MQTT reconnect.");
        break;

    case MQTT_EVENT_SUBCRIBE_SUCCESS:
        sg_subscribe_event_result = msg->event_type;
        Log_i("subscribe success, packet-id=%u", packet_id);
        break;

    case MQTT_EVENT_SUBCRIBE_TIMEOUT:
        sg_subscribe_event_result = msg->event_type;
        Log_i("subscribe wait ack timeout, packet-id=%u", packet_id);
        break;

    case MQTT_EVENT_SUBCRIBE_NACK:
        sg_subscribe_event_result = msg->event_type;
        Log_i("subscribe nack, packet-id=%u", packet_id);
        break;

    case MQTT_EVENT_PUBLISH_SUCCESS:
        Log_i("publish success, packet-id=%u", (unsigned int)packet_id);
        break;

    case MQTT_EVENT_PUBLISH_TIMEOUT:
        Log_i("publish timeout, packet-id=%u", (unsigned int)packet_id);
        break;

    case MQTT_EVENT_PUBLISH_NACK:
        Log_i("publish nack, packet-id=%u", (unsigned int)packet_id);
        break;
    default:
        Log_i("Should NOT arrive here.");
        break;
}
}
int DeviceWorker::_setup_connect_init_params(TemplateInitParams *initParams)
{
int ret;

ret = HAL_GetDevInfo((void *)&sg_devInfo);
if (QCLOUD_RET_SUCCESS != ret) {
    return ret;
}

initParams->device_name = sg_devInfo.device_name;
initParams->product_id  = sg_devInfo.product_id;

#ifdef AUTH_MODE_CERT
/* TLS with certs*/
char  certs_dir[PATH_MAX + 1] = "certs";
char  current_path[PATH_MAX + 1];
char *cwd = getcwd(current_path, sizeof(current_path));
if (cwd == NULL) {
    Log_e("getcwd return NULL");
    return QCLOUD_ERR_FAILURE;
}
sprintf(sg_cert_file, "%s/%s/%s", current_path, certs_dir, sg_devInfo.dev_cert_file_name);
sprintf(sg_key_file, "%s/%s/%s", current_path, certs_dir, sg_devInfo.dev_key_file_name);

initParams->cert_file = sg_cert_file;
initParams->key_file  = sg_key_file;
#else
initParams->device_secret = sg_devInfo.device_secret;
#endif

initParams->command_timeout        = QCLOUD_IOT_MQTT_COMMAND_TIMEOUT;
initParams->keep_alive_interval_ms = QCLOUD_IOT_MQTT_KEEP_ALIVE_INTERNAL;
initParams->auto_connect_enable    = 1;
initParams->event_handle.h_fp      = event_handler;
initParams->usr_control_handle         = NULL;

return QCLOUD_RET_SUCCESS;
}

void DeviceWorker::OnControlMsgCallback(void *pClient, const char *pJsonValueBuffer, uint32_t valueLength,
                             DeviceProperty *pProperty)
{
int i = 0;
for (i = 0; i < TOTAL_PROPERTY_COUNT; i++) {
    /* handle self defined string/json here. Other properties are dealed in _handle_delta()*/
    if (strcmp(sg_DataTemplate[i].data_property.key, pProperty->key) == 0) {
        sg_DataTemplate[i].state = eCHANGED;
        Log_i("Property=%s changed", pProperty->key);
        sg_control_msg_arrived = true;
        return;
    }
}

Log_e("Property=%s changed no match", pProperty->key);
}
void DeviceWorker::OnReportReplyCallback(void *pClient, Method method, ReplyAck replyAck, const char *pJsonDocument,
                              void *pUserdata)
{
Log_i("recv report reply response, reply ack: %d", replyAck);
if(replyAck==0){
    lxstate=true;
   qDebug()<<"lx true";
    qDebug()<<"size"<<dataStorage_temperature1.size();
   //offline data upload
    /* zigbee 4 */
    if (!dataStorage_temperature1.empty()) {
        qDebug() << "uploadOfflineData t1";
      uploadOfflineData(sg_ProductData.m_T1,temperature1_i,17,dataStorage_temperature1);
           }
    if (!dataStorage_temperature2.empty()) {
        uploadOfflineData(sg_ProductData.m_T2,temperature2_i,19,dataStorage_temperature2);
           }
    if(!dataStorage_temperature1_state.empty()) {
            uploadOfflineData(sg_ProductData.m_T1_S,temperature1_state_i,18,dataStorage_temperature1_state);
             }
    if(!dataStorage_temperature2_state.empty()){
        uploadOfflineData(sg_ProductData.m_T1_S,temperature2_state_i,20,dataStorage_temperature2_state);
    }

    /*ADC 5*/
    if (!dataStorage_voltage.empty()) {   
        uploadOfflineData(sg_ProductData.m_V,voltage_i,16,dataStorage_voltage);
         //offline_count_voltage=dataStorage_voltage.size();
         //qDebug() << "offline count voltage"<<offline_count_voltage;
           }
    if (!dataStorage_current.empty()) {
        uploadOfflineData(sg_ProductData.m_C,current_i,21,dataStorage_current);
//         offline_count_current=dataStorage_current.size();
        // qDebug() << "offline count curent"<<offline_count_current;
           }
    if(!dataStorage_pressure.empty()) {
            uploadOfflineData(sg_ProductData.m_P,pressure_i,22,dataStorage_pressure);
    }
     if(!dataStorage_temperature.empty()) {
             uploadOfflineData(sg_ProductData.m_T,temperature_i,23,dataStorage_temperature);
     }
     if(!dataStorage_current_state.empty()) {
         uploadOfflineData(sg_ProductData.m_C_S,current_state_i,24,dataStorage_current_state);
     }
 /* distance */
     if(!dataStorage_distance.empty()) {
             uploadOfflineData(sg_ProductData.m_D,distance_i,31,dataStorage_distance);
     }
 /*GPIO 6*/
     if(!dataStorage_gpio1_state.empty()) {
        uploadOfflineData(sg_ProductData.m_G1_S,gpio1_state_i,25,dataStorage_gpio1_state);
     }
     if(!dataStorage_gpio2_state.empty()) {
             uploadOfflineData(sg_ProductData.m_G2_S,gpio2_state_i,26,dataStorage_gpio2_state);
     }
     if(!dataStorage_gpio3_state.empty()) {
         uploadOfflineData(sg_ProductData.m_G3_S,gpio3_state_i,27,dataStorage_gpio3_state);
     }
     if(!dataStorage_gpio1.empty()) {
         uploadOfflineData(sg_ProductData.m_G1,gpio1_i,28,dataStorage_gpio1);
     }
     if(!dataStorage_gpio2.empty()) {
         uploadOfflineData(sg_ProductData.m_G1,gpio2_i,29,dataStorage_gpio2);
     }
     if(!dataStorage_gpio3.empty()) {
         uploadOfflineData(sg_ProductData.m_G1,gpio3_i,30,dataStorage_gpio3);
     }
}else{
     //offline data store
    //storeDataLocally_voltage(QString::number(sg_ProductData.m_voltage));
   
    /*zigbee *4*/
    storeDataLocally(QString::number(sg_ProductData.m_temperature1), dataStorage_temperature1);
    storeDataLocally(QString::number(sg_ProductData.m_temperature2), dataStorage_temperature2);
    storeDataLocally(QString::number(sg_ProductData.m_state1), dataStorage_temperature1_state);
    storeDataLocally(QString::number(sg_ProductData.m_state2), dataStorage_temperature2_state);    
    /*ADC 5*/
    storeDataLocally(QString::number(sg_ProductData.m_voltage), dataStorage_voltage);
    storeDataLocally(QString::number(sg_ProductData.m_current), dataStorage_current);
    storeDataLocally(QString::number(sg_ProductData.m_temperature), dataStorage_temperature);
    storeDataLocally(QString::number(sg_ProductData.m_atmosphere_pressure), dataStorage_pressure);
    storeDataLocally(QString::number(sg_ProductData.m_current_state), dataStorage_current_state);
    
    /* distance*/
    storeDataLocally(QString::number(sg_ProductData.m_distance), dataStorage_distance);  
    /* GPIO 6*/
    storeDataLocally(QString::number(sg_ProductData.m_GPIO1_state), dataStorage_gpio1_state);
    storeDataLocally(QString::number(sg_ProductData.m_GPIO2_state), dataStorage_gpio2_state);
    storeDataLocally(QString::number(sg_ProductData.m_GPIO3_state), dataStorage_gpio3_state);
    storeDataLocally(QString::number(sg_ProductData.m_GPIO1_value), dataStorage_gpio1);
    storeDataLocally(QString::number(sg_ProductData.m_GPIO2_value), dataStorage_gpio2);
    storeDataLocally(QString::number(sg_ProductData.m_GPIO3_value), dataStorage_gpio3);
    lxstate=false;
}
}

void DeviceWorker::storeDataLocally(const QString& data, QVector<QString>& dataStorage){
      QString entry ="数据:"+data + " 时间:" + QDateTime::currentDateTime().toString("yyyy.MM.dd hh:mm:ss");
        dataStorage.push_back(entry);
        qDebug() << "Data stored locally.";
         qDebug() << "Data stored size"<<dataStorage_temperature1.size();
}


// register data template properties
int DeviceWorker::_register_data_template_property(void *pTemplate_client)
{
int i, rc;

for (i = 0; i < TOTAL_PROPERTY_COUNT; i++) {
    rc = IOT_Template_Register_Property(pTemplate_client, &sg_DataTemplate[i].data_property, OnControlMsgCallback);
    if (rc != QCLOUD_RET_SUCCESS) {
        Log_e("register device data template property failed, err: %d", rc);
        return rc;
    } else {
        Log_i("data template property=%s registered.", sg_DataTemplate[i].data_property.key);
    }
}

return QCLOUD_RET_SUCCESS;
}

// when control msg received, data_template's properties has been parsed in pData you should add your logic how to use pData
void DeviceWorker::deal_down_stream_user_logic(void *client, ProductDataDefine *pData)
{
Log_d("someting about your own product logic wait to be done");

#ifdef EVENT_POST_ENABLED
// IOT_Event_setFlag(client, FLAG_EVENT0);  //set the events flag when the evnts your defined occured, see
// events_config.c
#endif
}
/*set property state, changed or no change*/

void DeviceWorker::set_property_state(void *pProperyData, eDataState state)
{
int i;
for (i = 0; i < TOTAL_PROPERTY_COUNT; i++) {
    if (sg_DataTemplate[i].data_property.data == pProperyData) {
        sg_DataTemplate[i].state = state;
        break;
    }
}
}

void DeviceWorker:: cycle_report(Timer *reportTimer)
{

if (expired(reportTimer)) {
    refreshOnlineData();
    //ADC
    sg_DataTemplate[4].state=eCHANGED;
    if(SharedData::share_current_state){
        sg_DataTemplate[5].state=eCHANGED;
        sg_DataTemplate[6].state=eCHANGED;
        sg_DataTemplate[7].state=eCHANGED;
    }else{
        sg_DataTemplate[5].state=eCHANGED;
    }
        sg_DataTemplate[9].state=eCHANGED;
        sg_DataTemplate[10].state=eCHANGED;
        sg_DataTemplate[11].state=eCHANGED;
        sg_DataTemplate[12].state=eCHANGED;
        sg_DataTemplate[13].state=eCHANGED;
        sg_DataTemplate[14].state=eCHANGED;
   // }

    //zigbee
    if(SharedData::share_temperature1_state==true){
        sg_DataTemplate[0].state=eCHANGED;
        sg_DataTemplate[2].state=eCHANGED;
    }else{
        sg_DataTemplate[2].state=eCHANGED;
    }

    if(SharedData::share_temperature2_state==true){
        sg_DataTemplate[1].state=eCHANGED;
        sg_DataTemplate[3].state=eCHANGED;
    }else{
        sg_DataTemplate[3].state=eCHANGED;
    }

    sg_DataTemplate[4].state=eCHANGED;
    sg_DataTemplate[8].state=eCHANGED;
    sg_DataTemplate[15].state=eCHANGED;
       countdown_ms(reportTimer, 2000);
}
}
/*get local property data, like sensor data*/
void DeviceWorker::_refresh_local_property(void)
{
   /* 5s上传一次数据。5s读取一次数据，只用该改变state上传数据*/
    /* upload offline data */
    cycle_report(&sg_reportTimer);
// add your local property refresh logic
}
void DeviceWorker::uploadOfflineData(char* data,int up,int order,QVector<QString>& dataStorage){
    if((lxstate==true)&&(!dataStorage.empty())){
    if(up<dataStorage.size()){
        //qDebug()<<"voltage_i"<<voltage_i;
        qDebug()<<"offline data converse";
        qDebug() << "Offline data: " << dataStorage[up];
        QByteArray byteArray = dataStorage[up].toUtf8();
        std::strcpy(data, byteArray.constData());
       // qDebug() << "sg_ProductData.m_V:" << sg_ProductData.m_V;
        sg_DataTemplate[order].state = eCHANGED;
    }
}
}

void DeviceWorker::refreshOnlineData(){
    sg_ProductData.m_temperature1 =SharedData::share_temperature1;
    sg_ProductData.m_temperature2 =SharedData::share_temperature2;
    sg_ProductData.m_state1=SharedData::share_temperature1_state;
    sg_ProductData.m_state2=SharedData::share_temperature2_state;
    sg_ProductData.m_voltage=SharedData::share_voltage;
    sg_ProductData.m_current=SharedData::share_current;
    sg_ProductData.m_temperature=SharedData::share_temperature;
    sg_ProductData.m_atmosphere_pressure=SharedData::share_atmosphere_pressure;
    sg_ProductData.m_distance=SharedData::share_distance;
    sg_ProductData.m_GPIO1_state=SharedData::share_GPIO1_state;
    sg_ProductData.m_GPIO2_state=SharedData::share_GPIO2_state;
    sg_ProductData.m_GPIO3_state=SharedData::share_GPIO3_state;
    sg_ProductData.m_GPIO1_value=SharedData::share_GPIO1_value;
    sg_ProductData.m_GPIO2_value=SharedData::share_GPIO2_value;
    sg_ProductData.m_GPIO3_value=SharedData::share_GPIO3_value;
    sg_ProductData.m_current_state=SharedData::share_current_state;
}


/*find propery need report*/
int DeviceWorker::find_wait_report_property(DeviceProperty *pReportDataList[])
{
int i, j;
for (i = 0, j = 0; i < TOTAL_PROPERTY_COUNT; i++) {
    if (eCHANGED == sg_DataTemplate[i].state) {
        pReportDataList[j++]     = &(sg_DataTemplate[i].data_property);
        sg_DataTemplate[i].state = eNOCHANGE;
    }
}
            /*offline data upload*/
/*if((offline_count_voltage-voltage_i)==1){
    offline_count_voltage=0;
    voltage_i=0;
    dataStorage_voltage.clear();
}
if(voltage_i<offline_count_voltage){
   voltage_i++;
}*/
/*zigbee 4*/
//if(lxstate==true&&(!dataStorage_temperature1.empty()){
temperature1_i=numberChange(temperature1_i,dataStorage_temperature1);
temperature2_i=numberChange(temperature2_i,dataStorage_temperature2);
temperature1_state_i=numberChange(temperature1_state_i,dataStorage_temperature1_state);
temperature2_state_i=numberChange(temperature2_state_i,dataStorage_temperature2_state);

/*ADC 5*/
voltage_i=numberChange(voltage_i,dataStorage_voltage);
current_i=numberChange(current_i,dataStorage_current);
pressure_i=numberChange(pressure_i,dataStorage_pressure);
temperature_i=numberChange(temperature_i,dataStorage_temperature);
current_state_i=numberChange(current_state_i,dataStorage_current_state);

/* distance */
distance_i=numberChange(distance_i,dataStorage_distance);

/*GPIO 6*/
gpio1_state_i=numberChange(gpio1_state_i,dataStorage_gpio1_state);
gpio2_state_i=numberChange(gpio2_state_i,dataStorage_gpio2_state);
gpio3_state_i=numberChange(gpio1_state_i,dataStorage_gpio3_state);
gpio1_i=numberChange(gpio1_i,dataStorage_gpio1);
gpio2_i=numberChange(gpio2_i,dataStorage_gpio2);
gpio3_i=numberChange(gpio3_i,dataStorage_gpio3);

return j;
}
int DeviceWorker::numberChange(int up, QVector<QString> &dataStorage){
    if((lxstate==true)&&(!dataStorage.empty())){
            if((dataStorage.size()-up)==1&&(up!=0)){
                qDebug()<<"datastorage clear";
                //count=0;
                up=0;
                dataStorage.clear();
            }
            if(up<dataStorage.size()){ 
               qDebug()<<"size"<<dataStorage.size();
               up++;
               qDebug()<<"up"<<up;
            }
            return up;
}
    return 0;
}
// demo for up-stream
// add changed properties to pReportDataList, then the changed properties would be reported
// you should add your own logic for how to get the changed properties
int DeviceWorker::deal_up_stream_user_logic(DeviceProperty *pReportDataList[], int *pCount)
{
// refresh local property
_refresh_local_property();

/*find propery need report*/
*pCount = find_wait_report_property(pReportDataList);

return (*pCount > 0) ? QCLOUD_RET_SUCCESS : QCLOUD_ERR_FAILURE;
}
/*You should get the real info for your device, here just for example*/
int  DeviceWorker::_get_sys_info(void *handle, char *pJsonDoc, size_t sizeOfBuffer)
{
/*platform info has at least one of module_hardinfo/module_softinfo/fw_ver property*/
DeviceProperty plat_info[] = {
    {.key = "module_hardinfo", .data = (void*)"ESP8266",.type = TYPE_TEMPLATE_STRING,},
    {.key = "module_softinfo", .data = (void*)"V1.0",.type = TYPE_TEMPLATE_STRING},
    {.key = "fw_ver", .data =(void*) QCLOUD_IOT_DEVICE_SDK_VERSION,.type = TYPE_TEMPLATE_STRING},
    {.key = "imei",  .data = (void*)"11-22-33-44",.type = TYPE_TEMPLATE_STRING,},
    {.key = "lat", .data = (void*)"22.546015",.type = TYPE_TEMPLATE_STRING, },
    {.key = "lon", .data = (void*)"113.941125",.type = TYPE_TEMPLATE_STRING, },
    {.key = NULL, .data = NULL}  // end
};

/*self define info*/
DeviceProperty self_info[] = {
    {.key = "append_info", .data = (void*)"your self define info",.type = TYPE_TEMPLATE_STRING},
    {.key = NULL, .data = NULL}  // end
};

return IOT_Template_JSON_ConstructSysInfo(handle, pJsonDoc, sizeOfBuffer, plat_info, self_info);
}

int DeviceWorker:: parse_arguments(int argc, char **argv)
{
int c;
while ((c = utils_getopt(argc, argv, "c:l:")) != EOF) switch (c){
        case 'c':
            if (HAL_SetDevInfoFile(utils_optarg))
                return -1;
            break;

        default:
            HAL_Printf(
                "usage: %s [options]\n"
                "  [-c <config file for DeviceInfo>] \n",
                argv[0]);
            return -1;
    }
return 0;
}

int DeviceWorker::runDeviceTemplate()
{

    qDebug()<<"RUN";
    // c 语言的main
    // 信号槽连接和线程间通信
    int             rc;
    sReplyPara      replyPara;
    DeviceProperty *pReportDataList[TOTAL_PROPERTY_COUNT];
    int             ReportCont;
    _init_data_template();
    // init log level
    IOT_Log_Set_Level(eLOG_DEBUG);
    // parse arguments for device info file
    QStringList arguments = QCoreApplication::arguments();
       QVector<QByteArray> argumentBytes;
       for (const QString& argument : arguments) {
           argumentBytes.append(argument.toUtf8());
       }
       QVector<char*> argumentPointers;
       for (int i = 0; i < argumentBytes.size(); i++) {
           argumentPointers.append(argumentBytes[i].data());
       }

       rc = parse_arguments(argumentPointers.size(), argumentPointers.data());
    if (rc != QCLOUD_RET_SUCCESS) {
        Log_e("parse arguments error, rc = %d", rc);
        return rc;
    }

    // init connection
    TemplateInitParams init_params = DEFAULT_TEMPLATE_INIT_PARAMS;
    rc                             = _setup_connect_init_params(&init_params);
    if (rc != QCLOUD_RET_SUCCESS) {
        Log_e("init params err,rc=%d", rc);
        return rc;
    }

    void *client = IOT_Template_Construct(&init_params, NULL);
    if (client != NULL) {
        Log_i("Cloud Device Construct Success");
    } else {
        Log_e("Cloud Device Construct Failed");
        return QCLOUD_ERR_FAILURE ;
    }

#ifdef MULTITHREAD_ENABLED
    if (QCLOUD_RET_SUCCESS != IOT_Template_Start_Yield_Thread(client)) {
        Log_e("start template yield thread fail");
        goto exit;
    }
#endif
// report device info, then you can manager your product by these info, like position
rc = _get_sys_info(client, sg_data_report_buffer, sg_data_report_buffersize);
if (QCLOUD_RET_SUCCESS == rc) {
    rc = IOT_Template_Report_SysInfo_Sync(client, sg_data_report_buffer, sg_data_report_buffersize,
                                          QCLOUD_IOT_MQTT_COMMAND_TIMEOUT);
    if (rc != QCLOUD_RET_SUCCESS) {
        Log_e("Report system info fail, err: %d", rc);
    }
} else {
    Log_e("Get system info fail, err: %d", rc);
}

// get the property changed during offline
rc = IOT_Template_GetStatus_sync(client, QCLOUD_IOT_MQTT_COMMAND_TIMEOUT);
if (rc != QCLOUD_RET_SUCCESS) {
    Log_e("Get data status fail, err: %d", rc);
} else {
    Log_d("Get data status success");
}

while (IOT_Template_IsConnected(client) || rc == QCLOUD_ERR_MQTT_ATTEMPTING_RECONNECT ||
       rc == QCLOUD_RET_MQTT_RECONNECTED || QCLOUD_RET_SUCCESS == rc) {

    rc = IOT_Template_Yield(client, 200);
    if (rc == QCLOUD_ERR_MQTT_ATTEMPTING_RECONNECT) {
        HAL_SleepMs(1000);
        continue;
    } else if (rc != QCLOUD_RET_SUCCESS) {
        Log_e("Exit loop caused of errCode: %d", rc);
    }
    /* handle control msg from server */
    if (sg_control_msg_arrived) {
        deal_down_stream_user_logic(client, &sg_ProductData);

        /* control msg should reply, otherwise server treat device didn't receive and retain the msg which would be
         * get by  get status*/
        memset((char *)&replyPara, 0, sizeof(sReplyPara));
        replyPara.code          = eDEAL_SUCCESS;
        replyPara.timeout_ms    = QCLOUD_IOT_MQTT_COMMAND_TIMEOUT;
        replyPara.status_msg[0] = '\0';  // add extra info to replyPara.status_msg when error occured

        rc = IOT_Template_ControlReply(client, sg_data_report_buffer, sg_data_report_buffersize, &replyPara);
        if (rc == QCLOUD_RET_SUCCESS) {
            Log_d("Contol msg reply success");
            sg_control_msg_arrived = false;
        } else {
            Log_e("Contol msg reply failed, err: %d", rc);
        }
    } else {
        Log_d("No control msg received...");
    }

    /*report msg to server*/
    /*report the lastest properties's status*/
    //qDebug()<<"QCLOUD_RET_SUCCESS before";
    if (QCLOUD_RET_SUCCESS == deal_up_stream_user_logic(pReportDataList, &ReportCont)) {
         //qDebug()<<"buffer1"<<sg_ProductData.m_V;

        rc = IOT_Template_JSON_ConstructReportArray(client, sg_data_report_buffer, sg_data_report_buffersize,
                                                    ReportCont, pReportDataList);
        if (rc == QCLOUD_RET_SUCCESS) {
             //qDebug()<<"buffer2"<<sg_ProductData.m_V;
            rc = IOT_Template_Report(client, sg_data_report_buffer, sg_data_report_buffersize,
                                     OnReportReplyCallback, NULL, QCLOUD_IOT_MQTT_COMMAND_TIMEOUT);
             //qDebug()<<"buffer3"<<sg_ProductData.m_V;
            if (rc == QCLOUD_RET_SUCCESS) {
              //  qDebug()<<"RC"<<rc;
                //qDebug()<<"ack"<<lxstate;
                Log_i("data template reporte success");
            } else {
                Log_e("data template reporte failed, err: %d", rc);
            }
        } else {
            Log_e("construct reporte data failed, err: %d", rc);
        }

    } else {
        // Log_d("no data need to be reported or someting goes wrong");
    }
    //qDebug()<<"QCLOUD_RET_SUCCESS_end";
#ifdef EVENT_POST_ENABLED0
    eventPostCheck(client);
#endif
    HAL_SleepMs(3000);
}
exit:

#ifdef MULTITHREAD_ENABLED
IOT_Template_Stop_Yield_Thread(client);
#endif
rc = IOT_Template_Destroy(client);

return rc;
}
DeviceWorker::~DeviceWorker()
{

}
