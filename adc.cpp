#include "adc.h"
ADC::ADC(QObject *parent)
    : QObject(parent)
{
   int initResult1 = adc.init(0x48,current_device);
       if (initResult1 != 0) {
           qDebug()<<"48初始化错误";
       }
  int initResult2 = adc.init(0x49,volt_device);
  if (initResult2!= 0) {
      qDebug()<<"49初始化错误";
  }

}
float ADC ::readVoltage(){
    float voltage = adc.rd(0x49,volt_device);
    qDebug()<<"vo"<<voltage;
    return voltage;
}
float ADC ::readCurrent(){
    float current = adc.rd(0x48,current_device);
    qDebug()<<"c0"<<current;
    return current;
}
void ADC::readADCdata(){
    while(1){
    qDebug()<<"readADCdata";
    SharedData::share_voltage=readVoltage();
    qDebug()<<"share_voltage"<<SharedData::share_voltage;
    float tmp=readCurrent();
    SharedData::share_current=4+16/5*tmp;
    qDebug()<<"share_current"<<SharedData::share_current;
    SharedData::share_temperature=(SharedData::share_current-4)*7.5-40;
    qDebug()<<"share_temperature"<<SharedData::share_temperature;
    SharedData::share_atmosphere_pressure=(SharedData::share_current-4)*7.5;
    qDebug()<<"share_atmosphere_pressure"<<SharedData::share_atmosphere_pressure;
    //current_state
    if(SharedData::current_state==2||SharedData::current_state==1){
        SharedData::share_current_state=true;
    }else{
        SharedData::share_current_state=false;
    }
    sleep(1);
 }
}
ADC::~ADC()
{
    //delete ui;
}
