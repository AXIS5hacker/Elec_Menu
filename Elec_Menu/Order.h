#ifndef ORDER_H
#define ORDER_H
#include <vector>
#include <time.h>
#include <string>
#include <iostream>
#include "Dish.h"

using std::pair;
using std::vector;
using std::string;

class Order
{
    public:
        //作者:吴挺轩
        //构造函数
        Order(int tableNo, int sumNo);

        virtual ~Order();
        //作者:吴挺轩
        //获取ID
        int getID();

        int addDish(int DishId);
        //作者:吴挺轩
        //加一按钮

        //作者:吴挺轩
        //减一按钮
        int deleteDish(int DishId);

        //作者:吴挺轩
        //直接给出数目
        int setDish(int DishId,int dnumber);

        //作者:吴挺轩
        //设置评论
        int setRemark(string remark);

        //作者:吴挺轩
        //获取备注
        string getRemark();

         //作者:吴挺轩
        //设置已下单
        int setOrdered();


        //作者:吴挺轩
        //设置已上菜
        int setCooked();

        //作者:吴挺轩
        //获取是否已付款
        bool getPaidStatus(){return isPaid;};

        //作者:吴挺轩
        //获取是否上菜
        bool cookedStatus(){return isCooked;};

        //作者:吴挺轩
        //获取菜品-订单之间的信息
        vector<pair<int,int> > getDLS() const{return dishListandSum;};

        //作者:李旭
        //设置已收款和实收金额
        int setPaid(float collectMoney);

        //作者:李旭
        //获取应收金额
        float getCount();

        //作者:李旭
        //获取订单提交时间
        struct tm getSubmitTime(){return submitTime;};

        //作者:李旭
        //获取上菜时间
        struct tm getCookedTime(){return cookedTime;};

        //作者:李旭
        //获取支付时间
        struct tm getPayTime(){return payTime;};

        //作者:冯梓轩
        //获取桌号
        int getTableNo(){return tableNo;};

        //作者:冯梓轩
        //获取人数
        int getSumNo(){return sumNo;};

        //作者:冯梓轩
        //获取实收金额
        float getCollectMoney(){return collectMoney;};//获取实收金额
    protected:

    private:
        int OrderID;//订单ID
        vector<pair<int,int> > dishListandSum;//菜品ID和数量
        string remark;//备注
        int tableNo;//桌号
        int sumNo;//人数
        struct tm submitTime;//下单时间
        struct tm cookedTime;//上菜时间
        struct tm payTime;//结算时间
        bool isOrdered;//是否已下单
        bool isCooked;//是否上菜
        bool isPaid;//是否已支付
        float _count;//应收金额
        float collectMoney;//实收金额
        //friend class Dish;
};


#endif // ORDER_H
