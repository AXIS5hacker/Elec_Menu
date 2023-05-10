#ifndef ORDERS_H_INCLUDED
#define ORDERS_H_INCLUDED

#include "Order.h"
#include "SQLserver.h"
class Orders
{
public:

    Orders(){;}

    //作者:李旭
    //在订单集中加入一个订单
    static int createOrder(const Order& od);

    //作者:李旭
    //用订单号寻找订单
    static Order& findOrder(int OrderID);

    //作者:李旭
    //通过下标寻找订单
    static Order& getOrder(int Index);

    //作者:李旭
    //令订单完成，让此订单退出订单集，加入结束订单缓冲区，缓冲区达到一定数目时候批量写入订单
    static int completeOrder(int OrderID,float money,SQLserver &sql);

    //作者:李旭
    //取得订单数目
    static int getSize();

    //作者:冯梓轩
    //保存到sql
    static int savetoSQL(SQLserver &sql);

private:
    static vector<Order> OrderList; //订单集
    static vector<Order> FinishedListBuf; //已完成的订单集
};


#endif // ORDERS_H_INCLUDED
