#include "gpio_up.h"
GPIO::GPIO(QObject *parent)
    : QObject(parent)
{

    G.init(gpio_62,gpio_input_mode);
    G.init(gpio_63,gpio_input_mode);
}
bool GPIO::rd61(){
    if(G.rd(gpio_61)==0){
        return false;
    }else {
   return true;
}
}

bool GPIO::rd62(){
    if(G.rd(gpio_62)==0){
        return false;
    }else {
   return true;
}
}

bool GPIO::rd63(){
    if(G.rd(gpio_63)==0){
        return false;
    }else {
   return true;
}
}
void GPIO::mode61(unsigned char mode){
    G.init(gpio_61,mode);
}
void GPIO::value61(unsigned char dat){
    G.wr(gpio_61,dat);
}
void GPIO::readGPIOdata(){
    while(1){
        qDebug()<<"readGPIOdata";
    if(SharedData::mode==1){
        mode61(gpio_output_mode);
        SharedData::share_GPIO1_state=true;
        if(SharedData::dat==1){
            value61(gpio_high);
            SharedData::share_GPIO1_value=true;
        }else{
             value61(gpio_low);
            SharedData::share_GPIO1_value=false;
        }
    }else{
        mode61(gpio_input_mode);
        //g.value61(SharedData::dat);
       SharedData::share_GPIO1_state=false;
       SharedData::share_GPIO1_value=rd61();
    }
    SharedData::share_GPIO2_value=rd62();
    SharedData::share_GPIO3_value=rd63();
    qDebug()<<"readGPIOdata"<<"63"<<SharedData::share_GPIO3_value;
    sleep(1);
   }
}
GPIO::~GPIO()
{
    //delete ui;
}
