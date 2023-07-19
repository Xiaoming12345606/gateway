#ifndef GPIO_UP_H
#define GPIO_UP_H
#include <QThread>
#include "gpio.h"
#include "QDebug"
#include "shareddata.h"
class GPIO : public QObject{
    Q_OBJECT
public:
    explicit GPIO(QObject *parent = nullptr);
       ~GPIO();
    bool rd61();
    bool rd62();
    bool rd63();
    void mode61(unsigned char mode);
    void value61(unsigned char dat);
    gpio G;
private:

public slots:
    void readGPIOdata();
};

#endif // GPIO_UP_H
