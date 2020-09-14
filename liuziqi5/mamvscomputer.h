#ifndef MAMVSCOMPUTER_H
#define MAMVSCOMPUTER_H

#include"qipan.h"

class Mamvscomputer : public Qipan
{
public:
    Mamvscomputer();

    //人下棋
    virtual void mouseReleaseEvent(QMouseEvent *event);  //点击鼠标时触发,排除鼠标左击
    void play(QPoint q);   //开始游戏

    //人机
    void computerxaiqi();   //人机开始下棋
    void ai(int *p1,int *p2);    //ai分析最佳下棋位置
    int zuijiadain(int hang,int lie);    //寻找得分最高的点
    int qixing(int d,int q1,int q2);   //棋型
    void fangxiang(int d,int *i,int *j);  //历遍八个方向

};

#endif // MAMVSCOMPUTER_H
