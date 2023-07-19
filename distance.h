#ifndef DISTANCE_H
#define DISTANCE_H
#include <QTimer>
#include <QThread>
#include "QDebug"
#include "wt53r-485.h"
#include "shareddata.h"
class Distance : public QObject{
    Q_OBJECT
public:
    explicit Distance(QObject *parent = nullptr);
       ~Distance();
    //SharedData d_sharedData;//shared data pointer
    //void setSharedData(SharedData data);
     QTimer d_timeoutTimer; // 用于检测阻塞的定时器
    wt53r wt;
    int fd;
private:

public slots:
    void readDistance();
    void handleTimeout();
signals:
    void threadBlocked();

};
#endif // DISTANCE_H
