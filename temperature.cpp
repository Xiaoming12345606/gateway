#include "temperature.h"
Temperature::Temperature(QObject *parent)
    : QObject(parent)
{
    qDebug() << "1 t:"<<QThread::currentThreadId();
}

/*void Temperature::readSerialData(unsigned char serialport){
         qDebug() << "read ";
        u.read_uart(serialport,9600);//contain init_uart
       qDebug() << "rx " <<u.rx ;
      int length = strlen(u.rx);
      qDebug() << "length " <<length;
     // tmp=QString::fromLatin1(u.rx);
       //qDebug() << "tmp0 " <<tmp ;
      tmp= QString::fromLatin1(u.rx, length);
      qDebug() << "tmp" <<tmp;
      qDebug() << "temperature:"<<QThread::currentThreadId();
      timer1->setInterval(5000);
      timer2->setInterval(5000);
      connect(timer1, &QTimer::timeout, this,  &Temperature::onTimer1Timeout);
      connect(timer2, &QTimer::timeout, this,  &Temperature::onTimer2Timeout);
      // 启动定时器
      timer1->start();
      timer2->start();
      qDebug() << "timer start ";
      // 提取温度数据和设备准备就绪的信息
              QRegularExpression temperatureRegex("(A|B):(\\d+)");
              QRegularExpression readyRegex("(A|B): Rd");
              QStringList temperatureList;
              QStringList readyList;
              // 提取温度数据
              QRegularExpressionMatchIterator matchIterator = temperatureRegex.globalMatch(tmp);
              while (matchIterator.hasNext()) {
                  QRegularExpressionMatch match = matchIterator.next();
                  QString device = match.captured(1);
                 float  temperature = match.captured(2).toInt();

                  if (device == "A") {
                     // temperatureList.append("Device 1 temperature: " + QString::number(temperature1));
        //              timer1->start();
                      //flag1=true;
                      qDebug() << "tem before ";
                      temperature1=temperature;
                      qDebug() << "tem after ";
                      qDebug()<<"Device 1 temperature: "<<temperature1;
                    //  return 1;
                  } else if (device == "B") {
                      //temperatureList.append("Device 2 temperature: " + QString::number(temperature2));
          //           timer2->start();
                     // flag2=true;
                      temperature2=temperature;
                      qDebug()<<"Device 2 temperature: "<<temperature2;
                  }
                 // return 2;
              }
              // 提取设备准备就绪的信息
              matchIterator = readyRegex.globalMatch(tmp);
              while (matchIterator.hasNext()) {
                  QRegularExpressionMatch match = matchIterator.next();
                  QString device = match.captured(1);
                  if (device == "A") {
                      flag1=true;
                      qDebug()<<"Device 1 is ready: ";
                     // return 1;
                     // readyList.append("Device 1 is ready");
                  } else if (device == "B") {
                      qDebug()<<"Device 2 is ready ";
                      flag2=true;
                      //readyList.append("Device 2 is ready");
                  }
                  //return 2;
              }
}*/

/*void Temperature::read(unsigned char serialport){

}*/
void Temperature::readTemperature(){
     qDebug() << "readTemperature ";
   /*QTimer timer1;
   qDebug() << "new timer1";
  connect(&timer1, &QTimer::timeout, this, &Temperature::readSerialData);
   //readSerialData();
   qDebug() << "timer1  connect ";
   timer1.setInterval(1000);
   qDebug() << "timer1  start before  ";
   timer1.start();
   qDebug() << "timer1  start after  ";
   */
     while(1){
         sleep(1);
         readSerialData();
         if(count_a>=10){
            SharedData::share_temperature1_state=false;
         }
         if(count_b>=10){
            SharedData::share_temperature2_state=false;
         }
          SharedData::share_temperature1=temperature1;
          //qDebug() << "temperature1"<<SharedData::share_temperature1;
          SharedData::share_temperature2=temperature2;
         // qDebug() << "temperature2"<<SharedData::share_temperature2;
     }
}
void Temperature::readSerialData(){
       //qDebug() << "readSerialData ";
        QTimer d_timeoutTimer; // 用于检测阻塞的定时器
        connect(&d_timeoutTimer, &QTimer::timeout, this, &Temperature::handleTimeout);
        d_timeoutTimer.start(10000); // 设置适当的超时时间 10s
       if(SharedData::zigbee==3){
         //   qDebug() << "uart3";
             u.read_uart(uart3,9600);
        }else if(SharedData::zigbee==2){
           // qDebug() << "uart2";
            u.read_uart(uart2,9600);
        }
    d_timeoutTimer.stop();
       // u.read_uart(uart3,9600);
      //qDebug() << "rx " <<u.rx ;
     int length = strlen(u.rx);
     //qDebug() << "length " <<length;
     tmp= QString::fromLatin1(u.rx, length);
     //qDebug() << "tmp" <<tmp;
     if(tmp=="OK"){
         SharedData::share_mainTemperature_state=true;
     }else{
         QRegularExpression temperatureRegex("(A|B):(\\d+)");
         QRegularExpression readyRegex("(A|B):Rd");
         // 提取温度数据
         QRegularExpressionMatchIterator matchIterator = temperatureRegex.globalMatch(tmp);
         while (matchIterator.hasNext()) {
             QRegularExpressionMatch match = matchIterator.next();
             QString device = match.captured(1);
            float  temperature = match.captured(2).toInt();

             if (device == "A") {
                // temperatureList.append("Device 1 temperature: " + QString::number(temperature1));
    //              timer1->start();
                // qDebug() << "tem before ";
                 SharedData::share_temperature1_state=true;
                 temperature1=temperature;
                 count_a=0;
                 count_b++;
                 //qDebug() << "tem after ";
                 //qDebug()<<"Device 1 temperature: "<<temperature1;
               //  return 1;
             } else if (device == "B") {
                 //temperatureList.append("Device 2 temperature: " + QString::number(temperature2));
     //           timer2->start();
               SharedData::share_temperature2_state=true;
                count_b=0;
                count_a++;
                 temperature2=temperature;
                 //qDebug()<<"Device 2 temperature: "<<temperature2;
             }
            // return 2;
         }
         // 提取设备准备就绪的信息
         matchIterator = readyRegex.globalMatch(tmp);
         while (matchIterator.hasNext()) {
             QRegularExpressionMatch match = matchIterator.next();
             QString device = match.captured(1);
             if (device == "A") {
                 SharedData::share_temperature1_state=true;
                 //qDebug()<<"Device 1 is ready: ";
                // return 1;
                // readyList.append("Device 1 is ready");
             } else if (device == "B") {
                 //qDebug()<<"Device 2 is ready ";
                 SharedData::share_temperature2_state=true;
                 //readyList.append("Device 2 is ready");
             }
             //return 2;
         }
         //qDebug()<<"while end";
     }



  //  }

}

/*void Temperature::onTimer1Timeout(){
    // 在设备1的定时器超时时将 flag1 置为 0
    flag1 = false;
}
void Temperature::onTimer2Timeout(){
    // 在设备2的定时器超时时将 flag2 置为 0
    flag2 = false;
}
*/
void Temperature::handleTimeout(){
    qDebug()<<"handleTimeout";
    SharedData::share_temperature1_state=false;
    SharedData::share_temperature2_state=false;
    emit threadBlocked();
    qDebug()<<" temperature threadBlocked";
}
Temperature::~Temperature()
{
    //delete ui;
}

