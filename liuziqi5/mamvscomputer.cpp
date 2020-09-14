#include "mamvscomputer.h"

#include<QMouseEvent>
#include <QMessageBox>
//#include<windows.h>

#define kong 0   //定义宏来标出棋盘的状况,以及人与机器的执子情况
#define man 2  //人执黑子
#define jiqi 1  //机器执白子

Mamvscomputer::Mamvscomputer()
{

}
void Mamvscomputer::mouseReleaseEvent(QMouseEvent *event){
    if (event->button() != Qt::LeftButton) { // 排除鼠标右键点击
        return;
    }
    play(event->pos());
}
void Mamvscomputer::play(QPoint q){   //类似于人人对战
    int hang,lie;
    if(dianzaiyuan(q,hang,lie)&&a[hang][lie]==0){
        chujie(hang,lie);
        if(judge(hang,lie)){
            if(chuzi==2){
                QMessageBox xinxi(QMessageBox::NoIcon, "gameover", "你赢了");
                xinxi.exec();
            }
            else if(chuzi==1){
                QMessageBox xinxi(QMessageBox::NoIcon, "gameover", "你输了");
                xinxi.exec();
            }
            clearqipan();
            return;
        }
        chuzi=(chuzi==1)?2:1;  //换人下棋
        update();
        computerxaiqi();    //机器下棋
        chuzi=(chuzi==1)?2:1;
        update();
    }
       int sum=0;
        for(int i=0;i<20;i++)
            for(int j=0;j<20;j++)
                if(a[i][j]==0)
                    sum++;

    if(sum==0){
        QMessageBox xinxi(QMessageBox::NoIcon, "gameover", "和棋");
        xinxi.exec();
        clearqipan();
        return;
    }

}
void Mamvscomputer::computerxaiqi(){
    int hang,lie;  //鼠标点中的点坐标
    ai(&lie,&hang);
        chujie(hang+1,lie+1);  //出界判定，之后会使当前方改变，所以要反过来
        if(judge(hang+1,lie+1)){
        if(chuzi==2){
            QMessageBox xinxi(QMessageBox::NoIcon, "gameover", "你赢了");
            xinxi.exec();
        }
        else if(chuzi==1){
            QMessageBox xinxi(QMessageBox::NoIcon, "gameover", "你输了");
            xinxi.exec();
        }
        clearqipan();
        return;

       }
        int sum=0;
        for(int i=0;i<20;i++)
            for(int j=0;j<20;j++)
                if(a[i][j]==0)
                    sum++;

    if(sum==0){
        QMessageBox xinxi(QMessageBox::NoIcon, "gameover", "和棋");
        xinxi.exec();
        clearqipan();
        return;
    }

}
void Mamvscomputer::ai(int *p1,int *p2){
    int max=0,zuijia,hang,lie;    //zuijia表示得分最高的点
    for(int i=0;i<20;i++)
        for(int j=0;j<20;j++)
            if(a[i+1][j+1]==0){     //历遍棋盘，遇到空点则计算价值，取最大价值点下子
                zuijia=zuijiadain(j,i);    //找到最高得分点
                if(zuijia>=max){
                    hang=j;lie=i;max=zuijia;
                }
            }
    *p1=hang;*p2=lie;
}
int Mamvscomputer::zuijiadain(int hang,int lie){
    int fx=1,value=0,df1,df2,bh1,bh2,x1,x2,y1,y2,z1,z2;
    //fx记录方向，value记录最高得分，df记录得分，bh记录得分的数据编号
    //X Y Z分别表示 己方0对方1    活0冲1空活2空冲3    子数0-3（0表示1个子，3表示4个子）
    /*一共有40种棋型，把有界的棋成为冲，无界称为活
     * 自己 ：  己冲，己活
     *         己空冲，己空活
     * 对手：   对冲，对活
     *         对空冲，对空活
     * 每种棋型分为1-5子
     * */
    int b[2][4][5]{{{30,300,400,2500,8000},{2,8,80,300,5000},{26,160,170,0,0},{4,20,100,300,0}},
                   {{40,400,500,3000,10000},{6,10,150,600,10000},{20,120,180,200,0},{6,10,150,500,0}}};   //创建三维数组储存权值

    while(fx!=5){       //四个方向历遍
        df1=qixing(fx,hang,lie); fx+=4;   //分别代表两个相反方向的棋型
        df2=qixing(fx,hang,lie); fx-=3;    //-3使fax的值加一
        int temp;
        if(df1>df2){
            temp=df1;df1=df2;df2=temp;  //使编号较小的为df1
        }
        bh1=df1;bh2=df2;
        z1=df1%10;df1/=10;y1=df1%10;df1/=10;x1=df1%10;
        z2=df2%10;df2/=10;y2=df1%10;df2/=10;x2=df1%10;

        //对边界空，边界冲，临界三种情况分别赋值
        if(bh1==-1){       //空棋型and其他
            if(bh2<0){value+=0;continue;}
            else  {value+=b[x2][y2][z2]+5;continue;  }  //选择权值最大的点，此时b[x1][y1[z1]没有对应值
        }
        else if(bh1==-2){       //边界冲棋型and其他
            if(bh2<0){value+=0;continue;}
            else {value+=b[x2][y2][z2]/2;continue;}
        }
        else if(bh1==-3){     //边界空冲棋型and其他
            if(bh2<0){value+=0;continue;}
            else {value+=b[x2][y2][z2]/3;continue;}
        }

        //己活己活，己活己冲，对活对活，对活对冲四种情况赋值
        else if(((bh1>=0&&bh1<=4)&&((bh2>-1&&bh2<5)||(bh2>9&&bh2<15)))
                ||((bh1>99&&bh1<105)&&((bh2>99&&bh2<105)||(bh2>109&&bh2<115)))){
            if(z1+z2>=3){value+=b[x2][y2][4];continue;}   // 选择权值最大的点
            else  {value+=b[x2][y2][z1+z2+1];continue;}
        }
        //己冲己冲，对冲对冲情况赋值   因为两边被堵死，如果能凑出六子应赋予极大权值，否则为0
        else if(((bh1>9&&bh1<15)&&(bh2>9&&bh2<15))||((bh1>109&&bh1<115)&&(bh2>109&&bh2<115))){
            if(z1+z2>=3){value+=10000;continue;}
            else {value+=0;continue;}
        }
        //己活对活，己活对冲，己冲对活，己冲对冲
        else if(((bh1>-1&&bh1<5)&&((bh2>99&&bh2<105)||(bh2>109&&bh2<115)))
                ||((bh1>9&&bh1<15)&&((bh2>99&&bh2<105)||(bh2>109&&bh2<115)))){
            if(z1==4&&z2==4){value+=10000;continue;}
            else{value+=b[x2][y2][z2]+b[x1][y1][z1]/4;continue;}
        }
        else  {value+=b[x1][y1][z1]+b[x2][y2][z2];continue;}
    }
    return value;
}
int Mamvscomputer::qixing(int d,int q1,int q2){
    int  sum,n=0;   //棋型号注解:  己活000-003 己冲010-013 对活100-103 对冲110-113 己空活020-023 己空冲030-033 对空活120-123 对空冲130-133 空-1 边界冲-2 边界空冲-3
    fangxiang(d,&q1,&q2);
    if(q1<0||q1>19||q2<0||q2>19) {sum=-2;return sum;}  //边界冲棋
    switch(a[q2+1][q1+1]){
    case jiqi:{
            n++;fangxiang(d,&q1,&q2);
            if(q1<0||q1>19||q2<0||q2>19){
                sum=n+9;return sum;
            }
            while(a[q2+1][q1+1]==jiqi){n++;fangxiang(d,&q1,&q2);if(q1<0||q1>19||q2<0||q2>19){sum=n+9;return sum;}}
            if(a[q2+1][q1+1]==kong)sum=n-1;   //己活
            else sum=n+9;     //己冲
        }break;
    case man:{
        n++;fangxiang(d,&q1,&q2);
        if(q1<0||q1>19||q2<0||q2>19){
            sum=n+109;return sum;}
        while(a[q2+1][q1+1]==man){n++;fangxiang(d,&q1,&q2);if(q1<0||q1>19||q2<0||q2>19){sum=n+109;return sum;}}
        if(a[q2+1][q1+1]==kong)sum=n+99;     //对活
        else sum=n+109;           //对冲
       }break;
    case kong:{
        fangxiang(d,&q1,&q2);
        if(q1<0||q1>19||q2<0||q2>19){sum=-3;return sum;}   //边空冲

        switch(a[q2+1][q1+1]){
        case jiqi:{
        n++;fangxiang(d,&q1,&q2);
        if(q1<0||q1>19||q2<0||q2>19){
            sum=n+29;return sum;
        }
        while(a[q2+1][q1+1]==jiqi){n++;fangxiang(d,&q1,&q2);if(q1<0||q1>19||q2<0||q2>19){sum=n+29;return sum;}}
        if(a[q2+1][q1+1]==kong)sum=n+19;     //己空活
        else sum=n+29;     //己空冲
           }break;
        case man:{
            n++;fangxiang(d,&q1,&q2);
            if(q1<0||q1>19||q2<0||q2>19){
                sum=n+129;return sum;
            }
            while(a[q2+1][q1+1]==man){n++;fangxiang(d,&q1,&q2);if(q1<0||q1>19||q2<0||q2>19){sum=n+129;return sum;}}
            if(a[q2+1][q1+1]==kong)sum=n+119;     //对空活
            else sum=n+129;           //对空冲
           }break;
        case kong: sum=-1;break;   //空
       }

    }break;
    }
    return sum;
}
void Mamvscomputer::fangxiang(int d,int *i,int *j){    //八个方向寻找
    switch(d){
    case 1: *i += 1; break;
    case 2: *i += 1; *j += 1; break;
    case 3: *j += 1; break;
    case 4: *i -= 1; *j += 1; break;
    case 5: *i -= 1; break;
    case 6: *i -= 1; *j -= 1; break;
    case 7: *j -= 1; break;
    case 8: *i += 1; *j -= 1; break;
    }
}
