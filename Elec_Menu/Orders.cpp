#include "Orders.h"
#include <vector>
#include <iostream>
#include"SQLserver.h"
using namespace std;


int Orders::createOrder(const Order& od)
{
//作者：李旭
//在订单集中加入一个订单
//input:od 订单的引用
//output: 返回0，表示被正常加入
    OrderList.push_back(od);

    return 0;
}

Order& Orders::findOrder(int OrderID)
{
//作者：李旭
//用订单号寻找订单
//input:OrderID 订单的ID
//output: 返回此ID的订单
    vector<Order>::size_type i;
    for(i=0;i<OrderList.size();i++)
    {
        if(OrderList[i].getID()  == OrderID)
            return OrderList[i];
    }
    //need a return value
    throw(2);
}

Order& Orders::getOrder(int Index)//通过下标寻找订单
{
//作者：李旭
//用订单在订单集中下标来迭代
//input:Index 订单下标
//output: 返回此下标的订单
    return OrderList[Index];
}

int Orders::completeOrder(int OrderID,float money,SQLserver &sql)
{
//作者：李旭
//令订单完成，让此订单退出订单集，加入结束订单缓冲区，缓冲区达到一定数目时候批量写入订单
//input:OrderID 订单的ID
//input:money 订单金额
//input:sql sql数据库
//output: 0 表示任务正常结束
    findOrder(OrderID).setPaid(money);
    FinishedListBuf.push_back(findOrder(OrderID));
    vector<Order>::size_type i;
    for(i=0;i<OrderList.size();i++)
    {
        if(OrderList[i].getID()  == OrderID)
        {
            OrderList.erase(OrderList.begin() + i);
            break;
        }
    }
    if(FinishedListBuf.size() == 10)
    {
        savetoSQL(sql);
        ;// 此处补充保存函数
    }

    return 0;
}

int Orders::getSize()
{
//作者：李旭
//返回当前订单的数目
//output: 订单的数目
    return OrderList.size();
}

int Orders::savetoSQL(SQLserver &sql)
{
    /**
      *作者:冯梓轩
      *保存到sql
      *input:sql数据库
      *output:0 表示任务正常结束
      */
    while(!FinishedListBuf.empty()){
        Order tmp=FinishedListBuf.front();
        sql.insertOrder(tmp);
        FinishedListBuf.erase(FinishedListBuf.begin());
    }
    return 0;
}
