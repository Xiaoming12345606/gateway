#ifndef SERIAL_H
#define SERIAL_H
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QTimer>
class Serial : public QSerialPort
{
    Q_OBJECT
public:
    Serial(QObject *parent = nullptr);
    ~Serial();
    void openSerialPort(QString serialport);
   // QString read();
    //void temperature(QString &s);
   // void close();
private:
    //QSerialPort *serial;
   // QByteArray data;
    //int i,flag1,flag2;
    //float temperature1,temperature2;
    //QTimer timer1;
    //QTimer timer2;
private slots:
    //void onTimer1Timeout();
    //void onTimer2Timeout();

};
#endif // SERIAL_H
