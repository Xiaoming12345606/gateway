#include "fourg.h"
FourG::FourG(QObject *parent)
    : QObject(parent)
{

}
void FourG::upload(){
    EC.connect();
    while(1){
    EC.update_rs485(SharedData::share_distance);//1
    EC.update_data_uart(SharedData::share_temperature1_state,SharedData::share_temperature1,SharedData::share_temperature2_state,SharedData::share_temperature2);//4
    EC.update_data_port(SharedData::share_GPIO1_state,SharedData::share_GPIO1_value,SharedData::share_GPIO2_state,SharedData::share_GPIO2_value,SharedData::share_GPIO3_state,SharedData::share_GPIO3_value);//6
    EC.update_data_iic(SharedData::share_voltage,SharedData::share_current,SharedData::share_atmosphere_pressure,SharedData::share_temperature,SharedData::share_current_state);//5
    EC.send_iic();
    EC.send_port();
    EC.send_uart();
    EC.send_rs485();
    }
}

FourG::~FourG()
{
    //delete ui;
}
