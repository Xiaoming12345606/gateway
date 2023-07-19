#ifndef TEMPERATURE_H
#define TEMPERATURE_H
#include <QTimer>
#include <QThread>
#include "uart.h"
#include "qdebug.h"
#include <QRegularExpression>
#include <QString>
#include <QStringList>
#include "shareddata.h"
#include <QThread>
class Temperature : public QObject{
    Q_OBJECT
public:
    explicit Temperature(QObject *parent = nullptr);
       ~Temperature();
    float temperature1=0;
    float temperature2=0;
    bool flag1 =false;
    bool flag2=false;
    //void readSerialData(unsigned char serialport);
    void readSerialData();

private:
    uart u;
    QString tmp;
    int count_a=0;
    int count_b=0;
    //QTimer *timer1;
    //QTimer *timer2;
    //int flag=0;
public slots:
    //void read(unsigned char serialport);
    //void onTimer1Timeout();
    //void onTimer2Timeout();
    void readTemperature();
    //void readSerialData();
    void handleTimeout();

signals:
    void threadBlocked();
};

#endif // TEMPERATURE_H
