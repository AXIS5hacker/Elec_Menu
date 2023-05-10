#ifndef MODIFY_DISH_H
#define MODIFY_DISH_H

#include <QDialog>

#include"SQLserver.h"

namespace Ui {
class modify_dish;
}

class modify_dish : public QDialog
{
    Q_OBJECT
signals:
    void complete();

public:
    explicit modify_dish(SQLserver &sql,QWidget *parent = nullptr, int ID = 1);
    ~modify_dish();

private slots:
    void unlock_mod();//解锁"确定"按钮
    void on_confirm_clicked();
    void on_exit_button_clicked();


private:
    Ui::modify_dish *ui;
    SQLserver *db;
    int ID;
};

#endif // MODIFY_DISH_H
