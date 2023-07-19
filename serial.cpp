#include "QDebug"
#include "QPushButton"
#include "serial.h"
Serial::Serial(QObject *parent):QSerialPort(parent)
{
   /*serial = this;
   //i=0;
   serial->setPortName("/dev/ttyS3");
   serial->setBaudRate(Serial::Baud9600);
   serial->setDataBits(Serial::Data8);
   serial->setParity(Serial::NoParity);
  serial->setStopBits(Serial::OneStop);
 bool flag=serial->open(QIODevice::ReadWrite);
 */
 //获取可以用的串口
  QList<QSerialPortInfo> serialPortInfos = QSerialPortInfo::availablePorts();
  //输出当前系统可以使用的串口个数
  qDebug() << "Total numbers of ports: " << serialPortInfos.count();
  foreach (const QSerialPortInfo &portInfo, serialPortInfos) {
          qDebug() << "port：" << portInfo.portName();
      }
}
 /*if(flag)
 {
     qDebug() << "open!!!!";
     //配置串口参数
     serial->setBaudRate(Serial::Baud9600);
     serial->setDataBits(Serial::Data8);
     serial->setParity(Serial::NoParity);
     serial->setStopBits(Serial::OneStop);
   //  connect(serial, SIGNAL(readyRead()), this, SLOT(read()));
     //connect(serial,&QSerialPort::readyRead, this, &Widget::read);
 }else
 {
     qDebug() << "not open";
 }
}*/

/*QString Serial::read(){
      qDebug() << "read start";
      while (serial->bytesAvailable()) {
          data = serial->readAll();
      }
      qDebug() <<i<< ":The received words are" << data;
      qDebug() << "read end";
      i++;
      QString strData(data); // 将 QByteArray 转换为 QString
      return strData;
}
*/

void Serial::openSerialPort(QString serialport){
    setPortName(serialport);
    setBaudRate(Serial::Baud9600);
    setDataBits(Serial::Data8);
    setParity(Serial::NoParity);
   setStopBits(Serial::OneStop);
  bool flag=open(QIODevice::ReadWrite);
  if(flag)
   {
       qDebug() << "open!!!!";
       //配置串口参数
       setBaudRate(Serial::Baud9600);
       setDataBits(Serial::Data8);
       setParity(Serial::NoParity);
       setStopBits(Serial::OneStop);
   }else
   {
       qDebug() << "not open";
   }
  }
/*void Serial::temperature(QString &s){
    temperature1=0;
    temperature2=0;
    qDebug()<<s<<endl;
    if (s== "Device1:ready") {
                flag1 = 1;
      }else if(s== "Device2:ready"){
        flag2=1;
    }else if(s== "Device1:readyDevice2:ready"){
        flag1=flag2=1;
    }else{
           /* int index = 0;
            while (index < s.length()) {
                // 查找设备ID的起始位置
                int deviceIdIndex = s.indexOf("Device", index);
                if (deviceIdIndex == -1) {
                    // 未找到设备ID，忽略剩余部分
                    break;
                }
                // 提取设备ID
                QString deviceIdStr = s.mid(deviceIdIndex, 7); // 假设设备ID的长度为固定的7个字符
                QString deviceId = deviceIdStr.mid(6, 1); // 提取设备ID中的数字部分

                // 查找温度值的起始位置
                int temperatureIndex = s.indexOf(":", deviceIdIndex);
                if (temperatureIndex == -1) {
                    // 未找到温度值，忽略当前设备ID
                    index = deviceIdIndex + deviceIdStr.length();
                    continue;
                }

                // 查找温度值的结束位置
                int endIndex = s.indexOf("Device", temperatureIndex);
                if (endIndex == -1) {
                    // 未找到下一个设备ID，说明当前温度值是最后一个
                    endIndex = s.length();
                }
                // 提取温度值
                QString temperatureStr = s.mid(temperatureIndex + 1, endIndex - temperatureIndex - 1);
                bool ok;
                int temperature = temperatureStr.toInt(&ok);
                if (!ok) {
                    // 温度值解析失败，忽略当前设备ID
                    index = endIndex;
                    continue;
                }
                // 根据设备ID将温度值赋给相应的变量
                if (deviceId == "1") {
                    temperature1 = temperature;
                } else if (deviceId == "2") {
                    temperature2 = temperature;
                }
                // 更新索引位置，从当前设备ID的结束位置继续查找
                index = endIndex + 1;
            }*/
        // 在初始化函数或构造函数中设置定时器
/*
            timer1.setInterval(5000);
            timer2.setInterval(5000);
            // 连接定时器的超时信号与槽函数
            connect(&timer1, &QTimer::timeout, this,  &Serial::onTimer1Timeout);
            connect(&timer2, &QTimer::timeout, this,  &Serial::onTimer2Timeout);
            // 启动定时器
            timer1.start();
            timer2.start();
        }
        // 分割消息，提取每个设备的数据
        QStringList dataList = s.split("Device", QString::SkipEmptyParts);
        for (const QString& deviceData : dataList) {
            QStringList deviceInfo = deviceData.split(":", QString::SkipEmptyParts);
            if (deviceInfo.length() == 2) {
                // 提取设备ID和温度值
                QString deviceId = deviceInfo[0].trimmed();
                QString temperatureStr = deviceInfo[1].trimmed();
                bool ok;
                int temperature = temperatureStr.toInt(&ok);
                if (ok) {
                    if (deviceId == "1") {
                        // 收到设备1的消息，重置定时器
                        timer1.start();
                        flag1 = 1; // 标志位设为 1
                        temperature1 = temperature; // 更新温度值
                    } else if (deviceId == "2") {
                        // 收到设备2的消息，重置定时器
                        timer2.start();
                        flag2 = 1; // 标志位设为 1
                        temperature2 = temperature; // 更新温度值
                    }
                }
            }
        }

        qDebug()<<"temperature1:"<<temperature1;
        qDebug()<<"temperature2:"<<temperature2;
        qDebug()<<"flag1:"<<flag1;
        qDebug()<<"flag2:"<<flag2;
        }
        */
/*void Serial::onTimer1Timeout(){
    // 在设备1的定时器超时时将 flag1 置为 0
    flag1 = 0;
}
void Serial::onTimer2Timeout(){
    // 在设备2的定时器超时时将 flag2 置为 0
    flag2 = 0;
}
*/
Serial::~Serial()
{
    // 析构函数的实现代码
    // 可以在这里释放资源或进行其他必要的清理操作
}

/*void Serial::close(){
      serial->close();
      qDebug() << "serial close!";
  }
*/
