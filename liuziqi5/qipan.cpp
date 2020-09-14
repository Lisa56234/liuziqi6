#include "qipan.h"
#include <QPainter>
#include <QPixmap>
#include <QDebug>

#include<QPaintEvent>
#include<QMessageBox>
#include<QMouseEvent>

Qipan::Qipan()
{
    clearqipan();
    qir=15;  //设置棋子的大小
    setMinimumSize(qir*20*2+1,qir*20*2+1);//设置窗口大小
    startset(2);  //黑子先下棋，0代表为空，2代表黑子，1代表白子
}
void Qipan::startset(int _chuqi1){   //开始建立
    chuzi1=_chuqi1;   //设置先下一方
    chuzi=_chuqi1;   //设置当前一方
    update();   //更新,绘制棋盘
}
void Qipan::chujie(int hang,  int lie){  //出界判定
    if(hang<1||hang>20||lie<1||lie>20)   return;
    if(a[hang][lie]!=0)  return;
    a[hang][lie]=chuzi;
}
void Qipan::clearqipan(){
    for(int i=1;i<21;i++){
        for(int j=1;j<21;j++)
            a[i][j]=0;
    }
}
bool Qipan::judge(int hang, int lie){  //判断胜负
    int x3[8]={0,1,1,1,0,-1,-1,-1};   //棋子朝八个方向延申查找
    int y3[8]={1,1,0,-1,-1,-1,0,1};
    int nowwei=a[hang][lie];   //当前所在的位置
    int sum,hang1,lie1;   //sum储存连子数，hang1和lie1作为临时寄存行列
    for(int i=0;i<4;i++){
        int j=i;
        sum=0;hang1=hang;lie1=lie;
        while(a[hang1][lie1]==nowwei){  //先横向右左找，再撇向下上找，再竖向下上，捺向下上找
            sum++;
            hang1+=y3[j];
            lie1+=x3[j];
        }
        j+=4;hang1=hang;lie1=lie;
        while(a[hang1][lie1]==nowwei){
            sum++;
            hang1+=y3[j];
            lie1+=x3[j];
        }
        if(sum>6)  return true;
        }
    return false;
}

void Qipan::paintEvent(QPaintEvent *){
    painback();
    int r=height()/(20*2);  //设置半径
    qir=r;
    dian=QPoint(qir+1,qir+1);
    QPainter p1(this);
    p1.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);    //抗锯齿处理
    painqipan(p1);
    painqizi(p1);
}
void Qipan::painback(){
    QPainter p(this);  //设置Qpainter,关联当前窗口
    p.drawPixmap(rect(),QPixmap("://Image/u=3606751862,1869919184&fm=26&gp=0.jpg"));

}

void Qipan::painqipan(QPainter &q){  //绘制棋盘
    // 绘制条横线
    for (int i = 1; i <= 20; ++i) {
            q.setPen(QPen(Qt::black, 2, Qt::SolidLine));
        q.drawLine(zhongxin(i, 1), zhongxin(i, 20));
    }

    // 绘制条竖线
    for (int i = 1; i <=20; ++i) {
        q.setPen(QPen(Qt::black, 2, Qt::SolidLine));
        q.drawLine(zhongxin(1, i), zhongxin(20, i));
    }
}

void Qipan::painqizi(QPainter &q){ //绘制棋子
    QColor ys;
    for(int i=1;i<21;i++){  //黑子
        for(int j=1;j<21;j++){
            if(a[i][j]==2){
                ys=Qt::black;
               q.setBrush(Qt::black);
               q.setPen(QPen(QBrush(ys), 2));
               q.drawEllipse(qizi(i,j));
            }
        }
    }
    for(int i=1;i<21;i++){  //白子
        for(int j=1;j<21;j++){
            if(a[i][j]==1){
                ys=Qt::white;
               q.setBrush(Qt::white);
               q.setPen(QPen(QBrush(ys), 2));     //线条的粗细
               q.drawEllipse(qizi(i,j));
            }
        }
    }
}
QPoint Qipan::zhongxin(int hang,int lie){   //棋子的中心坐标
    QPoint q1(qir*(lie-1)*2,qir*(hang-1)*2);
    return q1+dian;
}
QPoint Qipan::zuoshang(int hang,int lie){//棋子左上角到中心的距离，即左上角的大小
    return zhongxin(hang,lie)-QPoint(qir,qir);
}
QRect Qipan::qizi(int hang,int lie){  //棋子所在的矩形
    return QRect(zuoshang(hang,lie),QSize(qir*2-1,qir*2-1));
}
bool Qipan::dianzaiyuan(QPoint q1,int &hang,int &lie){  //判断像素点是否在棋子内
    hang=q1.y()/(2*qir)+1;  //获取当前像素点所在的位置
    lie=q1.x()/(2*qir)+1;

    QPoint s=zhongxin(hang,lie);
    int x0=s.x()-q1.x();   //鼠标像素点所在的位置
    int y0=s.y()-q1.y();
    int juli=x0*x0+y0*y0;  //与鼠标像素点所处的矩形左上顶点的距离
    if(juli<qir*qir)  return true;

    hang+=1;      //矩形左下顶点
    s=zhongxin(hang,lie);  //更新数据
    x0=s.x()-q1.x();
    y0=s.y()-q1.y();
    juli=x0*x0+y0*y0;
    if(juli<qir*qir)  return true;

    hang-=1;   //矩形右上顶点
    lie+=1;
    s=zhongxin(hang,lie);  //更新数据
    x0=s.x()-q1.x();
    y0=s.y()-q1.y();
    juli=x0*x0+y0*y0;
    if(juli<qir*qir)  return true;

    hang+=1;       //矩形右下顶点
    s=zhongxin(hang,lie);  //更新数据
    x0=s.x()-q1.x();
    y0=s.y()-q1.y();
    juli=x0*x0+y0*y0;
    if(juli<qir*qir)  return true;

    return false;      //不在棋子内
}

