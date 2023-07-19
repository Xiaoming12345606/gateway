#ifndef UIDEMO08_H
#define UIDEMO08_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <networkwidget.h>

#include <QThread>
#include "QDebug"
#include "serial.h"
#include "wt53r-485.h"
#include "yx75r.h"
#include "deviceworker.h"
#include "shareddata.h"
#include "distance.h"
#include <QString>
#include"fourg.h"
#include <QComboBox>
#include"bj.h"
#include"temperature.h"
#include"gpio.h"
#include "gpio_up.h"
#include "adc.h"

class QToolButton;

namespace Ui {
class UIDemo08;
}

class UIDemo08 : public QWidget
{
    Q_OBJECT

public:
    explicit UIDemo08(QWidget *parent = 0);
    ~UIDemo08();

    //gpio G_61;
    void startDeviceThread();
    void startFourgThread();

    void startDistanceThread();
    void startTemperatureThread();
    void startADCThread();
    void startGPIOThread();

    void startZigbeeThread();
    void startSTMThread();


    /* GUI */
  QString selectedOption_zigbee;
  QString selectedOption_stm32;
  QString selectedOption_GPIO;
  QString selectedOption_current;

  QString selectedOption_bj_stm_io;
  QString selectedOption_bj_stm_method;
  QString selectedOption_bj_zigbee_method;

  QString bj_stm_add_string;
  QString bj_zigbee_add_string;

private:
    Ui::UIDemo08 *ui;    
    QList<int> pixCharMain;
    QList<QToolButton *> btnsMain;

    QList<int> pixCharConfig;
    QList<QToolButton *> btnsConfig;
    // 拓扑图
    NetWorkWidget *networkWidget;




    Serial *serial;//stm32 control

    QThread* deviceThread;
    DeviceWorker* deviceWorker;
    QThread* fourgThread;
    FourG *fourg;


    QThread* distanceThread;
    Distance* distance;
    bool isDistanceThreadRunning; // 用于跟踪子线程的运行状态
    QThread* temperatureThread;
    Temperature* temperature_T;
    bool isTemperatureThreadRunning; // 用于跟踪子线程的运行状态
    QThread* ADCThread;
    ADC* adc;
    QThread* GPIOThread;
    GPIO* gpio;


    QThread* zigbeeThread;
    BJ* bjZigbee;
    QThread* stmThread;
    BJ* bjStm;

    int node[3]={0,0,0};
    int line[2]={0,0};

private slots:
    void initForm();
    void buttonClick();
    void initLeftMain();
    void initLeftConfig();
    void leftMainClick();
    void leftConfigClick();

private slots:
    void on_btnMenu_Min_clicked();
    void on_btnMenu_Max_clicked();
    void on_btnMenu_Close_clicked();

private slots:
   //distance

    void killDistanceThread();
    void restartDistanceThread();
    void checkDistanceThread();

    //temperature
     void killTemperatureThread();
     void restartTemperatureThread();
     void checkTemperatureThread();

     void on_zigbeeConfirmButton_clicked();
     void on_gpioConfirmButton_clicked();
     void on_interfaceConfirmButton_clicked();
     void on_openAlarmButton2_clicked();
     void on_closeAlarmButton2_clicked();
     void on_openAlarmButton1_clicked();
     void on_closeAlarmButton1_clicked();
     void on_openUartButton_clicked();
     void on_closeUartButton_clicked();
     void on_leftButton_clicked();
     void on_rightButton_clicked();
     void on_stopButton_clicked();

     void updateRealtimeData();
     void showTemperature();
     void showDistance();

     void updateNetwork();
     void stopMachine();
};

#endif // UIDEMO08_H
