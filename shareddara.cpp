#include "shareddata.h"

          float SharedData::share_temperature1=0;
          float SharedData::share_temperature2=0;
          float SharedData::share_voltage=0;
          float SharedData::share_current=0;
          float SharedData::share_temperature=0;
          float SharedData::share_atmosphere_pressure=0;
          float SharedData::share_distance=0;


          bool SharedData::share_temperature1_state=false;
          bool SharedData::share_temperature2_state=false;
          bool SharedData::share_mainTemperature_state=false;
          bool SharedData::share_current_state=false;

          bool SharedData::share_GPIO1_value=false;
          bool SharedData::share_GPIO2_value=false;
          bool SharedData::share_GPIO3_value=false;
          bool SharedData::share_GPIO1_state=false;
          bool SharedData::share_GPIO2_state=false;
          bool SharedData::share_GPIO3_state=false;
          bool SharedData::tmp=false;


          /* GUI */
          int SharedData::flag_stm=0;
          int SharedData::flag_zigbee=0;

           unsigned char SharedData::zigbee=1;

           unsigned char SharedData::mode=2;
           unsigned char SharedData::dat=0;
           int SharedData::current_state=5;//0(current)  1(pressure)   2(temperature)

           float SharedData::bj_stm_limit=0;
           float SharedData::bj_zigbee_limit=0;

           unsigned char SharedData::bj_stm_method='0';
           unsigned char SharedData::bj_zigbee_method='0';
          // unsigned char SharedData::bj_close='0';
           int SharedData::bj_GPIO=1;

           unsigned char SharedData::bj_stm_add='0';
           unsigned char SharedData::bj_zigbee_add='0';





