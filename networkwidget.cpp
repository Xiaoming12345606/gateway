#include "networkwidget.h"
#include "QDebug"
NetWorkWidget::NetWorkWidget(QWidget *parent) : QWidget(parent)
{
    // 文字位置数组
    QList<QPoint> posList = {
        QPoint(220, 70),   // 主节点位置
        QPoint(70, 260),   // 节点1位置
        QPoint(370, 260)   // 节点2位置
    };
    QStringList list = {"协调器", "终端一", "终端二"};
    for (int i = 0; i < 3; i++) {
        QLabel *label = new QLabel(this);
        label->setText(list[i]);
        label->move(posList[i]);
    }
}

void NetWorkWidget::setNodeAndLineState(int node[], int line[])
{
    // 更新状态
    for (int i = 0; i < 3; i++) {
        nodeState[i] = node[i];
    }
    for (int i = 0; i < 2; i++) {
        lineState[i] = line[i];
    }
    // 更新图
    update();
    //qDebug()<<"node[0]"<<nodeState[0];
    //qDebug()<<"node[1]"<<nodeState[1];
    //qDebug()<<"node[2]"<<nodeState[2];
}

void NetWorkWidget::NetWorkWidget::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    // 灰色笔刷
    QPen grayPen;
    grayPen.setWidth(3);
    grayPen.setColor(Qt::gray);
    // 绿色笔刷
    QPen greenPen;
    greenPen.setWidth(3);
    greenPen.setColor(Qt::green);
    // 笔刷数组
    QList<QPen> penList = {grayPen, greenPen};
    // 协调器笔刷
    p.setPen(penList[nodeState[0]]);
    p.drawRect(200, 50, 100, 60);
    // 终端1笔刷
    p.setPen(penList[nodeState[1]]);
    p.drawRect(50, 250, 100, 60);
    // 终端2笔刷
    p.setPen(penList[nodeState[2]]);
    p.drawRect(350, 250, 100, 60);
    // 画线
    p.setPen(penList[lineState[0]]);
    p.drawLine(250, 110, 100, 250);
    p.setPen(penList[lineState[1]]);
    p.drawLine(250, 110, 400, 250);
}
