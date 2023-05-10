#include "modify_order.h"
#include "ui_modify_order.h"

#include<string>
#include<QString>
#include<QStringList>
#include<QValidator>
#include"Orders.h"
#include"Dishs.h"
#include<QMessageBox>
using namespace std;

extern string qstr2str_utf8(const QString qstr);
extern QString str2qstr_utf8(const string str);

mod_order::mod_order(int id,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::mod_order)
{
    /*
    * Auto generated by QT
    * This code is the constructor function of the UI
    * input:id of the target to be modified
    * Constructor Function
    */


    ui->setupUi(this);
    target=NULL;
    modify_id=id;
    try{
    target=&Orders::findOrder(modify_id);
    }catch(int exep){//if failed to find the target order
        target=NULL;
    }

    if(target!=NULL){
        //设置"设置为已付款"按钮状态
        unlock_receive();
        //设置"设置为已上菜"按钮状态
        if(target->cookedStatus()){
            ui->serve->setEnabled(false);
        }else{
            ui->serve->setEnabled(true);
        }
        ui->total->setText(QString("订单金额:")+QString::number(target->getCount())+"元");
    }else{
        QMessageBox::critical(this,"Error","订单查找失败");
        this->close();
    }

    //connects

    //connect to "设置为已付款" button
    connect(ui->lineEdit,SIGNAL(editingFinished()),this,SLOT(unlock_receive()));
    connect(ui->lineEdit,SIGNAL(textChanged(QString)),this,SLOT(unlock_receive()));

}

void mod_order::on__back_clicked(){
    /*
    * Author:冯梓轩
    * "取消" button
    * No input
    * No output
    */
    this->close();
}

void mod_order::on_serve_clicked(){
    /*
    * Author:冯梓轩
    * "设置为已上菜" button
    * No input
    * No output
    */
    target->setCooked();
    emit modifiedOrder(modify_id,true);
    this->close();
}

void mod_order::unlock_receive(){
    /*
    * Author:冯梓轩
    * 设置"设置为已付款"按钮可用状态
    * No input
    * No output
    */
    if((!target->getPaidStatus())&&ui->lineEdit->text()!=""){
        ui->receivedMoney->setEnabled(true);
    }else{
        ui->receivedMoney->setEnabled(false);
    }
}

void mod_order::on_receivedMoney_clicked(){
    /*
    * Author:冯梓轩
    * "设置为已付款" button
    * No input
    * No output
    */
    float money=ui->lineEdit->text().toFloat();
    if(money<target->getCount()){
        QMessageBox::warning(this,"付款小于订单价格","付款小于订单价格");
    }else{
        target->setPaid(money);
        emit modifiedOrder(modify_id,true);
        this->close();
    }
}
mod_order::~mod_order()
{
    delete ui;
}