#ifndef WIDGET_H
#define WIDGET_H      //菜单选择页面

#include <QWidget>


namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
private slots:
    void on_pushButton_mm_clicked();   //人人对战按钮
    void on_pushButton_mc_clicked();

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H

