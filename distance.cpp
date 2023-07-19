#include "distance.h"

Distance::Distance(QObject *parent)
    : QObject(parent)
{
   // qDebug()<<"Distance uart_init  uart1 ";
    //fd =wt.uart_init(uart_1,0x50,0x03,0x0034,0x0001);
    //qDebug() << "construct1:"<<QThread::currentThreadId();
    //d_sharedData=new SharedData();
}

void Distance::readDistance(){
   // qDebug() << "t1 distance"<<SharedData::share_temperature1;
   //SharedData::share_temperature1=2;
   //qDebug() << "t1 distance after"<<SharedData::share_temperature1;
    //qDebug()<<"readDistance";
   while(1){
     qDebug()<<"readDistance while 1";
    //delay(100);
    //QTimer d_timeoutTimer; // 用于检测阻塞的定时器
    //connect(&d_timeoutTimer, &QTimer::timeout, this, &Distance::handleTimeout);
    // 启动定时器
    //d_timeoutTimer.start(100000); // 设置适当的超时时间 100s
    //qDebug()<<"readDistance timer 100s";
    fd =wt.uart_init(uart_1,0x50,0x03,0x0034,0x0001);
    qDebug()<<"fd"<<fd;
    float a=wt.read_data(fd);
   // sleep(2);
     qDebug()<<"readDistance wt.read_data"<<a;
    //shared data
   // d_sharedDatashare_distance=1;
     // qDebug()<<"store share data "<<a<<" 1"<<d_sharedData->share_distance;
     SharedData::share_distance=a;
      qDebug()<<"share_distance "<<SharedData::share_distance;
    //d_timeoutTimer.stop();
     sleep(1);
    }
}

void Distance::handleTimeout(){
       emit threadBlocked();
     qDebug()<<"threadBlocked";
}
Distance::~Distance()
{
    //delete ui;
}
