#ifndef MODIFY_ORDER_H
#define MODIFY_ORDER_H

#include <QWidget>
#include "Dishs.h"
#include"Orders.h"
namespace Ui {
class mod_order;
}

class mod_order : public QWidget
{
    Q_OBJECT

public:
    //作者:冯梓轩
    //获取要更改的订单id
    explicit mod_order(int id,QWidget *parent = nullptr);
    ~mod_order();


signals:
    /*
     * Here are the signal functions.
     */
    void modifiedOrder(int,bool);
private slots:
    /*
     * Here are the slot functions, they are used for buttons and other components of the window.
     */
    //作者:冯梓轩
    //按钮"取消"
    void on__back_clicked();

    //作者:冯梓轩
    //按钮"设置为已上菜"
    void on_serve_clicked();

    //作者:冯梓轩
    //按钮"设置为已付款"
    void on_receivedMoney_clicked();

    //作者:冯梓轩
    //解锁按钮"设置为已付款"
    void unlock_receive();

private:
    Ui::mod_order *ui;
    int modify_id;//要更改的订单ID号
    Order *target;//要更改的订单指针
};

#endif // CREATE_ORDER_H
