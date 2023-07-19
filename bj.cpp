#include "bj.h"
BJ::BJ(QObject *parent)
    :QObject (parent)
{
  //fd=yx.uart_init(1);
}
/*void BJ::setSharedData(SharedData* data)
{
    b_sharedData = data;
}*/
//void BJ::bj_stm(unsigned char add,float limit,int io,unsigned char method){
void BJ::bj_stm(){
   // qDebug()<<"32 start";
    while(1){
     //qDebug()<<"32 while1";
     //SharedData::bj_GPIO=11;
  //  qDebug()<<" SharedData::bj_GPIO"<<SharedData::bj_GPIO;
        if(SharedData::bj_GPIO==62){
            qDebug()<<"GPIO_62";
           SharedData::tmp=SharedData::share_GPIO2_value;
        }else if(SharedData::bj_GPIO==63){
            qDebug()<<"GPIO_63";
           SharedData::tmp=SharedData::share_GPIO3_value;
           qDebug()<<"SharedData::share_GPIO3_value"<<SharedData::share_GPIO3_value;
        }
         qDebug()<<"32 tiaojian "<<SharedData::flag_stm<<" "<<SharedData::share_distance<<" "<<SharedData::bj_stm_limit;
        if((SharedData::flag_stm==1)&&(!SharedData::tmp)&&(SharedData::share_distance<=SharedData::bj_stm_limit)){
            qDebug()<<"32 BJ";
             qDebug()<<"SharedData::share_distance"<<SharedData::share_distance;
             fd=yx.uart_init(uart_1);
             qDebug()<<"yx57r 32bj"<<fd;
            yx.write_commad(fd,SharedData::bj_stm_method,SharedData::bj_stm_add);      
        }else{
            qDebug()<<"no BJ";
            fd=yx.uart_init(uart_1);
            yx.write_commad(fd,commad_close,SharedData::bj_stm_add);
        }
        sleep(1);
    }
}
//void BJ::bj_zigbee(unsigned char add, float limit, unsigned char method){
void BJ::bj_zigbee(){
    //qDebug()<<"BJ::bj_zigbee()";
    while (1) {
        //qDebug()<<"bj_zigbee while(1)";
        //qDebug()<<"flag_zigbee"<<SharedData::flag_zigbee;
        //qDebug()<<"SharedData::share_temperature1"<<SharedData::share_temperature1;
        //qDebug()<<"SharedData::share_temperature2"<<SharedData::share_temperature2;
       // qDebug()<<"SharedData::bj_zigbee_limit"<<SharedData::bj_zigbee_limit;
        if((SharedData::flag_zigbee==1)&&((SharedData::share_temperature1>=SharedData::bj_zigbee_limit)||(SharedData::share_temperature2>=SharedData::bj_zigbee_limit))){
         //     qDebug()<<"temperature BJ";
              fd=yx.uart_init(uart_1);
           // qDebug()<<"yx57r temperature bj"<<fd;
            yx.write_commad(fd,SharedData::bj_zigbee_method,SharedData::bj_zigbee_add);
             //qDebug()<<"bj end"<<fd;
        }else{
            fd=yx.uart_init(uart_1);
            yx.write_commad(fd,commad_close,SharedData::bj_zigbee_add);
            //qDebug()<<"bj end"<<fd;
        }
         sleep(1);
   }
}

BJ::~BJ()
{
    //delete ui;
}
