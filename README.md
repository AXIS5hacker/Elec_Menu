# Elec_Menu
 软件工程团队作业
 
## 编译环境:
 QT套件:QT 6.2.4 (MinGW11.2.0-64bit)或以上版本
 
 c++ 17

 MySQL 8.x
 
## 使用:
1.首先在MySQL中执行以下SQL语句:
 
create database data; 
 
use data; 

create table Dishs
(
    Dish_ID int primary key,
    name char(200),
    price double,
    jpgPath char(200),
    onSell int,
    describes char(200)
);

create table Orders
(
    Order_ID int primary key,
    remark char(200),
    tableNo int,
    sumNo int,
    submitTime char(200),
    cookedTime char(200),
    payTime char(200),
    _count double,
    collectMoney double
);

create table Materials
(
    Material_ID int primary key,
    name char(200),
    remain int
);

create table Dish_Material
(
    Dish_ID int,
    Material_ID int,
    foreign key(Dish_ID) references Dishs(Dish_ID) ON DELETE CASCADE,
    foreign key(Material_ID) references Materials(Material_ID) ON DELETE CASCADE,
    primary key(Dish_ID, Material_ID)
);

create table Order_Dish
(
    Order_ID int,
    Dish_ID int,
    count int,
    foreign key(Dish_ID) references Dishs(Dish_ID) ON DELETE CASCADE,
    foreign key(Order_ID) references Orders(Order_ID) ON DELETE CASCADE,
    primary key(Order_ID, Dish_ID)
);

2.将源码中SQLserver.cpp中的用户名与密码改为你本地数据库相应的
