#ifndef NETWORKWIDGET_H
#define NETWORKWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QPen>
#include <QBrush>
#include <QLabel>

class NetWorkWidget : public QWidget
{
    Q_OBJECT
public:
    explicit NetWorkWidget(QWidget *parent = nullptr);

    // 改变节点和线的状态
    void setNodeAndLineState(int node[], int line[]);

protected:
    void paintEvent(QPaintEvent *event);

private:
    // 线的状态，0-主节点到节点1的线，1-主节点到节点2的线
    int lineState[2]={0, 0};
    // 主、1、2结点的状态
    int nodeState[3]={1, 0, 0};

};

#endif // NETWORKWIDGET_H
