#ifndef ADC_H
#define ADC_H
#include "QObject"
#include "qdebug.h"
#include "ads_1115.h"
#include "shareddata.h"
class ADC : public QObject{
     Q_OBJECT
public:
    explicit ADC(QObject *parent = nullptr);
       ~ADC();
    float readVoltage();
    float readCurrent();
    ads1115 adc;
private:

public slots:
    void readADCdata();

};

#endif // ADC_H
