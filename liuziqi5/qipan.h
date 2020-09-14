#ifndef QIPAN_H
#define QIPAN_H

#include <QFrame>

class Qipan : public QFrame
{
    Q_OBJECT
public:
    Qipan();

    int a[21][21];  //储存棋子的位置,保存当前位置的状态，0代表为空，2代表为黑子，1代表为白子
    int chuzi1,chuzi;  //出子先，当前出子的人
    int qir;      //棋子半径
    QPoint dian;//平面上的一个点,坐标基点

      void startset(int _chuqi1);     //开始绘制棋盘
      void chujie(int hang,  int lie);    //出界判定
      void clearqipan();   //清空棋盘
      virtual void paintEvent(QPaintEvent *);//绘图
      void painqipan(QPainter &q);    //绘制棋盘
      void painqizi(QPainter &q);   //绘制棋子
      void painback();

      //绘制棋子的坐标
      QPoint zhongxin(int hang,int lie);  //棋子的中心坐标
      QPoint zuoshang(int hang,int lie);   //棋子左上角到中心的距离，即左上角的大小
      QRect qizi(int hang,int lie);  //棋子所在的矩形
      bool dianzaiyuan(QPoint q1,int &hang,int &lie);  //判断像素点是否在棋子内

      bool judge(int hang, int lie);   //判断是否赢
      //void mousePressEvent(QMouseEvent *event);

};

#endif // MANVSMAN_H
