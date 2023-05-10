﻿#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "modify_dish.h"

#include<QDebug>
#include<QMessageBox>
//将order信息保存为QString
extern QString generate_content(const Order &od);
//string和QString转换函数
extern string qstr2str_utf8(const QString qstr);
extern QString str2qstr_utf8(const string str);

MainWindow::MainWindow(QWidget* parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
    /**
	* Auto generated by QT
	* This code is the constructor function of the UI
	* Auto input
	* Constructor Function
	*/
{
	//setup the ui
    ui->setupUi(this);

    //connect to sql
    if(sql.openSQL()!=0){
        QMessageBox::critical(this,"连接错误","无法连接到SQL数据库");
        exit(0);
    }
    //set background
    QPixmap bkgnd(":/images/rc/bk.jpg");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette paletteb;
    paletteb.setBrush(QPalette::Window, bkgnd);
    this->setPalette(paletteb);

    //Dishs::readFormFile("input.txt");//specify an input file

    //Dishs::AddDish(19.99,"咖喱饭","无论老人还是小孩都非常喜欢的常规菜肴。是简单而又不会吃腻的一道菜。","null");
    //Dishs::AddDish(29.99,"蟹肉蛋炒饭","满满都是新鲜蟹肉的豪华炒饭。与松软鸡蛋的组合真是美味无穷。","null");
    //Dishs::AddDish(39.99,"海陆煎烤","将新鲜的鱼和肉混在一起烧烤，是充满营养的菜肴。","null");
    Dishs::loadFromSQL(sql);
    info_show();

    ui->modify_order->setEnabled(false);
    //connects
    connect(ui->order_visual,SIGNAL(currentItemChanged(QTableWidgetItem*,QTableWidgetItem*)),this,SLOT(unlock_modify()));

    //set table header
    QStringList order_header;
    order_header<<"订单号"<<"订单内容"<<"备注"<<"应付金额"<<"订单状态"<<"";
    ui->order_visual->setHorizontalHeaderLabels(order_header);
    //set table width:order_visual
    ui->order_visual->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->order_visual->horizontalHeader()->setSectionResizeMode(1,QHeaderView::Stretch);
    ui->order_visual->horizontalHeader()->setSectionResizeMode(2,QHeaderView::Stretch);
    ui->order_visual->setColumnWidth(0,100);
    ui->order_visual->setColumnWidth(3,100);
    ui->order_visual->setColumnWidth(4,150);
    ui->order_visual->setColumnWidth(5,100);
    ui->order_visual->horizontalHeader()->setVisible(true);
    //set table width:infoTab
    ui->infoTab->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->infoTab->horizontalHeader()->setSectionResizeMode(1,QHeaderView::Stretch);
    ui->infoTab->horizontalHeader()->setSectionResizeMode(4,QHeaderView::Stretch);
    ui->infoTab->setColumnWidth(0,70);
    ui->infoTab->setColumnWidth(2,160);
    ui->infoTab->setColumnWidth(3,100);
    ui->infoTab->setColumnWidth(5,100);
    ui->infoTab->setColumnWidth(6,100);
    ui->infoTab->setColumnWidth(7,70);
    ui->infoTab->horizontalHeader()->setVisible(true);

}

void MainWindow::info_show() {
    /**
      *作者:黄志宏
      *刷新菜单列表
      *No input
      *No output
      */
    ui->infoTab->setRowCount(0);
    int flag = 0;
    for(int i = 1;i < Dishs::GetSize();i++){
        int row = ui->infoTab->rowCount();
        ui->infoTab->insertRow(row);
        //skip the empty dishes
        while (Dishs::GetDish(i + flag).GetID()==0)
            flag ++;
        QTableWidgetItem* prototype=new QTableWidgetItem;
        //set the table widget items to read-only mode
        prototype->setTextAlignment(Qt::AlignLeft|Qt::AlignVCenter);
        prototype->setFlags(prototype->flags()^Qt::ItemIsEditable);
        //ID
        QTableWidgetItem* tmp=prototype->clone();
        tmp->setText(QString::number(Dishs::GetDish(i + flag).GetID()));
        ui->infoTab->setItem(row, 0, tmp);
        //jpgpath
        tmp=prototype->clone();
        tmp->setText(QString::fromStdString(Dishs::GetDish(i + flag).GetjpgPath()));
        ui->infoTab->setItem(row, 1, tmp);
        //name
        tmp=prototype->clone();
        tmp->setText(QString::fromStdString(Dishs::GetDish(i + flag).Getname()));
        ui->infoTab->setItem(row, 2, tmp);
        //price
        tmp=prototype->clone();
        tmp->setText(QString::number(Dishs::GetDish(i + flag).Getprice()));
        ui->infoTab->setItem(row, 3, tmp);
        //description
        tmp=prototype->clone();
        tmp->setText(QString::fromStdString(Dishs::GetDish(i + flag).Getdescribe()));
        ui->infoTab->setItem(row, 4, tmp);
        //ui->infoTab->setItem(row, 3, new QTableWidgetItem(QString::number(row)));
        //set status
        tmp=prototype->clone();
        bool stat=Dishs::GetDish(i + flag).getsell();
        if(stat){
            tmp->setText("已上架");
        }else{
            tmp->setText("未上架");
        }
        ui->infoTab->setItem(row, 5, tmp);
        //set button
        QPushButton *btn = new QPushButton();
        btn->setText(tr("修改"));
        connect(btn, &QPushButton::clicked, this, [=] {modify_item(ui->infoTab->item(i - 1, 0)->text().toInt()); });
        ui->infoTab->setCellWidget(row, 6, btn);
        //checkbox
        QTableWidgetItem* p_check = new QTableWidgetItem();
        p_check->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        p_check->setCheckState(Qt::Unchecked);
        p_check->setFlags(p_check->flags()^Qt::ItemIsEditable);
        ui->infoTab->setItem(row, 7, p_check);
        //resize
        ui->infoTab->resizeRowsToContents();
    }
}

void MainWindow::modify_item(int ID) {
    modify_dish *p = new modify_dish(sql,nullptr, ID);
    connect(p, &modify_dish::complete, this, &MainWindow::info_show);
    p->setWindowModality(Qt::ApplicationModal);
    p->show();
}

void MainWindow::on_add_button_clicked()
{
    add_dish *p = new add_dish(sql);
    connect(p, &add_dish::complete, this, &MainWindow::info_show);
    p->setWindowModality(Qt::ApplicationModal);
    p->show();
}

void MainWindow::on_remove_button_clicked()
{
    for(int i = 0; i < ui->infoTab->rowCount(); i++) {
        if (ui->infoTab->item(i, 7)->checkState() == Qt::Checked) {
            Dishs::DeleteDish(Dishs::GetDish(ui->infoTab->item(i, 0)->text().toInt()),sql);
        }
    }
    info_show();
}

void MainWindow::on_new_order_clicked(){
    /*
    * Author:冯梓轩
    * "创建订单" button
    * No input
    * No output
    */
    nwnd=new create_order;
    nwnd->setWindowModality(Qt::ApplicationModal);//block other windows
    connect(nwnd,SIGNAL(insertedOrder(int,bool)),this,SLOT(changedOrder(int,bool)));
    nwnd->show();

}


void MainWindow::changedOrder(int id,bool find){
    /*
    * Author:冯梓轩
    * 订单显示发生插入或更改时插入订单
    * input:订单id,是否查找已有订单
    * No output
    */
    bool insert_flag=true;
    Order *target=NULL;

    try{
    target=&Orders::findOrder(id);
    }catch(int exep){//if failed to find the target order
        target=NULL;
    }

    if(target!=NULL){
    int tid=target->getID();
    if(find){
    for(int i=0;i<ui->order_visual->rowCount();i++){

        if(ui->order_visual->item(i,0)->text().toInt()==id){
            ui->order_visual->setCurrentCell(i,0);
            //set ordercontent
            QString content=generate_content(*target);
            ui->order_visual->item(i,1)->setText(content);
            //set remark
            ui->order_visual->item(i,2)->setText(str2qstr_utf8(target->getRemark()));
            //set total bill
            ui->order_visual->item(i,3)->setText(QString::number(target->getCount())+QString("元"));
            //set status
            if(target->getPaidStatus()&&target->cookedStatus()){
                ui->order_visual->item(i,4)->setText("已付款");
                ui->order_visual->cellWidget(i,5)->setEnabled(true);
            }else if(target->getPaidStatus()&&(!target->cookedStatus())){
                ui->order_visual->item(i,4)->setText("已付款,未上菜");
            }else if(target->cookedStatus()&&(!target->getPaidStatus())){
                ui->order_visual->item(i,4)->setText("已上菜,未付款");
            }else{
                ui->order_visual->item(i,4)->setText("已下单");
            }
            insert_flag=false;
            break;
        }
    }
    }
    if(insert_flag){
        //insert a new row
        ui->order_visual->insertRow(0);
        //fill cells
        QTableWidgetItem* prototype=new QTableWidgetItem();
        prototype->setTextAlignment(Qt::AlignLeft|Qt::AlignVCenter);
        prototype->setFlags(prototype->flags()^Qt::ItemIsEditable);
        //set orderID
        QTableWidgetItem* neworder_id=prototype->clone();
        neworder_id->setText(QString::number(tid));
        ui->order_visual->setItem(0,0,neworder_id);
        //set ordercontent
        QString content=generate_content(*target);
        QTableWidgetItem* neworder_content=prototype->clone();
        neworder_content->setText(content);
        ui->order_visual->setItem(0,1,neworder_content);
        //set remark
        QTableWidgetItem* neworder_remark=prototype->clone();
        neworder_remark->setText(str2qstr_utf8(target->getRemark()));
        ui->order_visual->setItem(0,2,neworder_remark);
        //set total bill
        QTableWidgetItem* neworder_bill=prototype->clone();
        neworder_bill->setText(QString::number(target->getCount())+QString("元"));
        ui->order_visual->setItem(0,3,neworder_bill);

        //set status
        QTableWidgetItem* neworder_status=prototype->clone();
        neworder_status->setText("已下单");
        ui->order_visual->setItem(0,4,neworder_status);
        //set button
        QPushButton *newbtn=new QPushButton(tr("完成订单"));
        ui->order_visual->setCellWidget(0,5,newbtn);

        //resize
        ui->order_visual->resizeRowsToContents();
        //connect button to order
        connect(newbtn,&QPushButton::clicked,this,[=] (){finish_order(tid);});
        newbtn->setEnabled(false);
        newbtn->setVisible(true);
        buttons.push_back(newbtn);
    }
    }
}

void MainWindow::on_modify_order_clicked(){
    /*
    * Author:冯梓轩
    * "修改订单" button
    * No input
    * No output
    */
    //get current selected row
    int crow=ui->order_visual->currentRow();
    //get current selected order id
    int modifyId=ui->order_visual->item(crow,0)->text().toInt();
    mnwnd=new mod_order(modifyId);
    mnwnd->setWindowModality(Qt::ApplicationModal);//block other windows
    connect(mnwnd,SIGNAL(modifiedOrder(int,bool)),this,SLOT(changedOrder(int,bool)));
    mnwnd->show();
}


void MainWindow::finish_order(int id){
    /*
    * Author:冯梓轩
    * "完成订单" button
    * No input
    * No output
    */
    //qDebug()<<id;
    Order *target=NULL;

    try{
    target=&Orders::findOrder(id);
    }catch(int exep){//if failed to find the target order
        target=NULL;
    }
    if(target!=NULL){
        Orders::completeOrder(id,target->getCount(),sql);
        for(int i=0;i<ui->order_visual->rowCount();i++){

            if(ui->order_visual->item(i,0)->text().toInt()==id){
                ui->order_visual->removeRow(i);

            }
        }
    }
}

void MainWindow::unlock_modify(){
    /*
    * Author:冯梓轩
    * 解锁"修改订单"按钮
    * No input
    * No output
    */
    if(ui->order_visual->currentRow()!=-1&&ui->order_visual->currentColumn()!=-1){
        ui->modify_order->setEnabled(true);
    }else{
        ui->modify_order->setEnabled(false);
    }

}
MainWindow::~MainWindow()
/**
* Auto generated by QT
* This code is the destructor function of the UI
* No input
* Destructor Function
*/
{
    //Dishs::printToFile("input.txt");
    //Dishs::saveToSQL(sql);
    Orders::savetoSQL(sql);
    sql.closeSQL();
	delete ui;
}

