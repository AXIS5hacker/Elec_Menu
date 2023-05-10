#include "Order.h"
#include "Dishs.h"

Order::Order(int tableNo, int sumNo)
//构造函数
//作者:吴挺轩
{
    struct tm *tblock;
    time_t timer = time(NULL);
    tblock = localtime(&timer);
    this->OrderID = (tblock->tm_year-100) * 38400000 + tblock->tm_mon * 3200000 +
            tblock->tm_mday*100000 + tblock->tm_hour*3600 +
            tblock->tm_min*60+ tblock->tm_sec*1 + 0;
    this->tableNo = tableNo;
    this->sumNo = sumNo;
    this->isOrdered = false;
    this->isCooked = false;
    this->isPaid = false;
    //ctor
}

Order::~Order()
{
    ;//dtor
}

int Order::getID()
//获取订单号
//作者:吴挺轩
{
    return OrderID;
}

int Order::addDish(int DishId)
//设置菜品数量加一
//作者:吴挺轩
{
    int i,m = this->dishListandSum.size();
    for(i=0;i<m;++i)
    {
        if(DishId == this->dishListandSum[i].first)
        {
            ++(this->dishListandSum[i].second);
            return 0;//当前已有
        }
    }
    dishListandSum.push_back( pair<int,int>(DishId,1) );//当前没有

    return 0;
}

int Order::deleteDish(int DishId)
//设置菜品数量减一
//作者:吴挺轩
{
    int i,m = this->dishListandSum.size();
    for(i=0;i<m;++i)
    {
        if(DishId == this->dishListandSum[i].first)
        {
            --(this->dishListandSum[i].second);
            if( (this->dishListandSum[i].second) <= 0 )
            {
                dishListandSum.erase( dishListandSum.begin() + i );
            }
            return 0;
        }
    }
    return 1;
}

int Order::setDish(int DishId,int dnumber)
//设置菜品数量
//作者:吴挺轩
{
    int i,m = this->dishListandSum.size();
    for(i=0;i<m;++i)
    {
        if(DishId == this->dishListandSum[i].first)
        {
            this->dishListandSum[i].second=dnumber;
            if( (this->dishListandSum[i].second) <= 0 )
            {
                dishListandSum.erase( dishListandSum.begin() + i );
            }
            return 0;
        }
    }
    dishListandSum.push_back( pair<int,int>(DishId,dnumber) );//当前没有

    return 0;
}


int Order::setRemark(string remark)
//设置备注
//作者:吴挺轩
{
    this->remark = remark;
    return 0;
}

string Order::getRemark()
//获取备注
//作者:吴挺轩
{
    return this->remark;
}

int Order::setOrdered()
//设置已下单
//作者:吴挺轩
{
    time_t timer = time(NULL);
    this->submitTime = *localtime(&timer);
    this->isOrdered = true;
    return 0;
}

int Order::setCooked()
//设置已上菜
//作者:吴挺轩
{
    time_t timer = time(NULL);
    this->cookedTime = *localtime(&timer);
    this->isCooked = true;
    return 0;
}

int Order::setPaid(float collectMoney)
//设置已收款和实收金额
//作者:李旭
{
    time_t timer = time(NULL);
    this->payTime = *localtime(&timer);
    isPaid = true;
    this->collectMoney = collectMoney;
    _count = getCount();
    return 0;
}

float Order::getCount()
//获取应收金额
//作者:李旭
{
    float sum = 0;
    vector<pair<int,int>>::size_type i;
    for(i=0;i< this->dishListandSum.size();i++)
    {
        sum += (Dishs::GetDish(this->dishListandSum[i].first)).Getprice() * this->dishListandSum[i].second;
    }

    return sum;
}
