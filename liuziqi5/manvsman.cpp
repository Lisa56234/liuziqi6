#include "manvsman.h"
#include<QMouseEvent>
#include<QMessageBox>

Manvsman::Manvsman()
{

}
void Manvsman::mouseReleaseEvent(QMouseEvent *event){
    if(event->button()!=Qt::LeftButton)  return;  //排除鼠标右击
    play(event->pos());
}
void Manvsman::play(QPoint q){
    int hang,lie;  //鼠标点中的点坐标
    if(dianzaiyuan(q,hang,lie)&&a[hang][lie]==0){
        chujie(hang,lie);  //出界判定，之后会使当前方改变，所以要反过来
        if(judge(hang,lie)){
        if(chuzi==2){
            QMessageBox xinxi(QMessageBox::NoIcon, "gameover", "黑子获胜");
            xinxi.exec();
        }
        else if(chuzi==1){
            QMessageBox xinxi(QMessageBox::NoIcon, "gameover", "白子获胜");
            xinxi.exec();
        }
        clearqipan();
        return;
        }
        chuzi=(chuzi==1)? 2:1;
        update();
       }
    int sum=0;
    for(int i=0;i<20;i++){
        for(int j=0;j<20;j++){
            if(a[i][j]==0)
                sum++;
        }
    }
    if(sum==0){          //和棋的情况
        QMessageBox xinxi(QMessageBox::NoIcon, "gameover", "和棋");
        xinxi.exec();
        clearqipan();
        return;
    }

}
