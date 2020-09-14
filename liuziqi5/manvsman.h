#ifndef MANVSMAN_H
#define MANVSMAN_H

#include <QMainWindow>
#include"qipan.h"

class Manvsman : public Qipan
{
public:
    Manvsman();

    virtual void mouseReleaseEvent(QMouseEvent *event); // 鼠标点击棋子并释放鼠标时候触发
    void play(QPoint q);  //开始游戏
};


#endif // MANVSMAN_H
