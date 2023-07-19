#ifndef BJ_H
#define BJ_H
#include <QTimer>
#include "QDebug"
#include "shareddata.h"
#include "yx75r.h"
class BJ : public QObject{
    Q_OBJECT
public:
    explicit BJ(QObject *parent = nullptr);
       ~BJ();
    //SharedData* b_sharedData;//shared data pointer
    void setSharedData(SharedData* data);
    yx75r yx;
    int fd;
private:

public slots:
    void bj_stm();
    void bj_zigbee();


signals:


};
#endif // BJ_H
