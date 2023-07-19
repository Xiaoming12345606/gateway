#ifndef FOURG_H
#define FOURG_H
#include <QTimer>
#include "QDebug"
#include "shareddata.h"
#include "ec600n.h"

class FourG : public QObject{
    Q_OBJECT
public:
    explicit FourG(QObject *parent = nullptr);
       ~FourG();
    ec600n EC;
   // void upload();
private:

public slots:
    void upload();
signals:


};
#endif // FOURG_H
