
#include "mainwindow.h"

#include <QApplication>
#include <QTranslator>
#include<fstream>
#include"Dishs.h"
#include"Orders.h"
#include"Materials.h"
using namespace std;


vector<Dish> Dishs::Dishlist={};
//unfinished orders(static,global)
vector<Order> Orders::OrderList={};
//finished orders(static,global)
vector<Order> Orders::FinishedListBuf={};
vector<Material> Materials::materialList={};
int Dishs::MaxID;

/*
 * 说明:连接数据库时提供的用户名和密码在SQLserver.cpp中更改
 * 更改的函数:SQLserver::openSQL()
 */
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
