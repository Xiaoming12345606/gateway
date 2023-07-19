#ifndef SHAREDDATA_H
#define SHAREDDATA_H
#include "qdebug.h"
#include <QObject>
#include <QMutex>
class SharedData {
public:
    //explicit SharedData(QObject *parent = nullptr);
    /* upload data */
     static float share_temperature1;
     static float share_temperature2;
     static float share_voltage;
     static float share_current;
     static float share_temperature;
     static float share_atmosphere_pressure;
     static float share_distance;
     
     static bool share_mainTemperature_state;
     static bool share_temperature1_state;
     static bool share_temperature2_state;
     
     static bool share_current_state;
     
     static bool share_GPIO1_value;
     static bool share_GPIO2_value;
     static bool share_GPIO3_value;
     static bool share_GPIO1_state;
     static bool share_GPIO2_state;
     static bool share_GPIO3_state;

    static bool tmp;

     /* GUI */
     static unsigned char zigbee;
     static unsigned char mode;
     static unsigned char dat;
     static int current_state;//0(current)  1(pressure)   2(temperature)

     static  int flag_stm;
     static int flag_zigbee;

     static float bj_stm_limit;
     static float bj_zigbee_limit;

     static unsigned char bj_stm_method;
     static  unsigned char bj_zigbee_method;
    // static  unsigned char bj_close;
     static int bj_GPIO;

    static unsigned char bj_stm_add;
    static unsigned char bj_zigbee_add;
     //char* abc;
};
#endif // SHAREDDATA_H
