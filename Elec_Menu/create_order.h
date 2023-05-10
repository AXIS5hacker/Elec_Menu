#ifndef CREATE_ORDER_H
#define CREATE_ORDER_H

#include <QWidget>
#include "Dishs.h"
namespace Ui {
class create_order;
}

class create_order : public QWidget
{
    Q_OBJECT

public:
    explicit create_order(QWidget *parent = nullptr);
    ~create_order();
signals:
    void insertedOrder(int,bool);
private slots:
    /*
     * Here are the slot functions, they are used for buttons and other components of the window.
     */
    //作者:冯梓轩
    //按钮"确认"
    void on_confirm_clicked();

    //作者:冯梓轩
    //按钮"添加菜品"
    void on_add_to_order_clicked();

    //作者:冯梓轩
    //按钮"删除菜品"
    void on_remove_from_order_clicked();

    //作者:冯梓轩
    //解锁按钮"添加菜品"
    void unlock_add();

    //作者:冯梓轩
    //解锁按钮"删除菜品"
    void unlock_del();

    //作者:冯梓轩
    //解锁按钮"确认"
    void unlock_confirm();
private:
    Ui::create_order *ui;

};

#endif // CREATE_ORDER_H
