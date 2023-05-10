#include "SQLserver.h"

using std::cout;
using std::endl;
using std::cin;

SQLserver::SQLserver()
//构造函数
{
    //ctor
}

SQLserver::~SQLserver()
//析构函数
{
    //dtor
}

int SQLserver::openSQL()
//打开mySQL链接
//作者:李旭
{
    /**
     *
     *更改说明:
     *host[]:数据库服务器所在ip(localhost为本地)
     *user[]:用户名
     *psw[]:数据库密码
     *table[]:数据库名
     *
     */

    mysql_init(&mysql);  //连接mysql，数据库
	const char host[] = "localhost";
	const char user[] = "root";
    	const char psw[] = "";
	const char table[] = "data";
	const int port = 3306;
	if (!(mysql_real_connect(&mysql, host, user, psw, table, port, NULL, 0)) )
	{
        //cout<<"LOSE:"<<mysql_error(&mysql)<<endl;
		return -1;
	}
	else
	{
        //cout<<"WIN！"<<endl;
		return 0;
	}
}

int SQLserver::closeSQL()
//关闭mySQL链接
//作者:李旭
{
    mysql_close(&mysql);
    return 0;
}

int SQLserver::insertDish(Dish &a)
//插入一个菜品
//作者:李旭
{
    string s = "INSERT INTO Dishs VALUES(";
    s += ItS(a.GetID()) + ",'";
    s += a.Getname() + "'," ;
    s += FtS(a.Getprice()) + ",'" ;
    s += a.GetjpgPath() + "',";
    s += ItS(a.getsell()) + ",'";                         //此处为bool形，需处理   已处理
    s += a.Getdescribe()  +"');";


    //cout<<s<<endl;
    //s = string_To_UTF8(s);
    mysql_query(&mysql, s.c_str());
    cout<<mysql_error(&mysql)<<endl;

    vector<int> material = a.getMaterial();
    for(int i = 0;i < material.size(); i++)
    {
        string s = "INSERT INTO Dish_Material VALUES(";       //此处是为了插入键值对
        s += ItS(a.GetID()) + ",";
        s += ItS(material[i]) + ");";

        //s = string_To_UTF8(s);//the whole string is already utf-8
        mysql_query(&mysql, s.c_str());
    }

    return 0;
}

int SQLserver::insertMaterial(Material &a)
//插入一个材料
//作者:苏文韬
{
    string s = "INSERT INTO Materials VALUES(";
    s += ItS(a.GetID()) + ",";
    s += "'" + a.GetName() + "'," ;
    s += ItS(a.GetRemain()) + ");" ;        //此处有bool形需要处理 已处理

    //s = string_To_UTF8(s);
    mysql_query(&mysql, s.c_str());

    return 0;
}

int SQLserver::insertOrder(Order &a)
//存入一个订单
//作者:吴挺轩
{

    string s = "INSERT INTO Orders VALUES(";
    s += ItS(a.getID()) + ",";
    s += "'" + a.getRemark() + "'," ;
    s += ItS(a.getTableNo()) + "," ;
    s += ItS(a.getSumNo()) + ",'" ;
    s += Time2String(a.getSubmitTime()) + "','";
    s += Time2String(a.getCookedTime()) + "','";
    s += Time2String(a.getPayTime()) + "',";
    s += FtS(a.getCount()) + ",";
    s += FtS(a.getCollectMoney()) + ");";

    //s = string_To_UTF8(s);
    mysql_query(&mysql, s.c_str());

    vector<pair<int,int>> dishListandSum = a.getDLS();
    for(int i = 0;i < dishListandSum.size(); i++)
    {
        string s = "INSERT INTO Order_Dish VALUES(";
        s += ItS(a.getID()) + ",";
        s += ItS(dishListandSum[i].first) + ",";
        s += ItS(dishListandSum[i].second) + ");";

        //s = string_To_UTF8(s);
        mysql_query(&mysql, s.c_str());
    }

    return 0;
}

int SQLserver::reviseDish(Dish &a)
//菜品修改
//作者:李旭
{
    string s = "DELETE FROM Dish_Material WHERE Dish_ID =" + ItS(a.GetID()) + ";";        //删除键值对
    //s = string_To_UTF8(s);
    mysql_query(&mysql, s.c_str());

    s = "UPDATE Dishs SET "; //修改本体属性
    s += " name = '" + a.Getname() + "'," ;
    s += " price = " + FtS(a.Getprice()) + "," ;
    s += " describes= '" + a.Getdescribe()  +"',";
    s += " jpgPath = '" + a.GetjpgPath() + "',";
    s += " onSell = " + ItS(a.getsell()) + " ";        //此行为bool形，可能需要修改   已修改
    s += "where Dish_ID = " + ItS(a.GetID()) + ";";
    //s = string_To_UTF8(s);
    mysql_query(&mysql, s.c_str());

    vector<int> material = a.getMaterial();
    for(int i = 0;i < material.size(); i++)
    {
        string s = "INSERT INTO Dish_Material VALUES(";       //插入（放回）键值对
        s += ItS(a.GetID()) + ",";
        s += ItS(material[i]) + ");";

        //s = string_To_UTF8(s);
        mysql_query(&mysql, s.c_str());
    }

    return 0;
}

int SQLserver::reviseMaterial(Material &a)
//材料修改
//作者:吴挺轩
{
    string s = "UPDATE Materials SET "; //修改本体属性
    s += " name = '" + a.GetName() + "'," ;
    s += " remain = " + ItS(a.GetRemain()) + " ";
    s += "where Material_ID = " + ItS(a.GetID()) + ";";

    //s = string_To_UTF8(s);
    mysql_query(&mysql, s.c_str());
    return 0;
}

int SQLserver::deleteMaterial(Material &a)
//材料删除
//作者:吴挺轩
{
    string s = "DELETE FROM Materials WHERE Material_ID=" + ItS(a.GetID()) + ";";        //根据ID删除
    //s = string_To_UTF8(s);
    mysql_query(&mysql, s.c_str());
    return 0;
}

int SQLserver::deleteDish(Dish &a)
//菜品删除
//作者:李旭
{
    string s = "DELETE FROM Dishs WHERE Dish_ID = " + ItS(a.GetID()) + ";";
    //s = string_To_UTF8(s);
    mysql_query(&mysql, s.c_str());
    return 0;
}

int SQLserver::clearTable(string tablename)
//清除一项表单
//作者:冯梓轩
{
    string s = "DELETE FROM " + tablename;
    mysql_query(&mysql, s.c_str());
    return 0;
}

/*string SQLserver::string_To_UTF8(const std::string & str)
//此函数用于将字符串转化为UTF-8格式，测试证明在QT中并不需要（但是在codeblocks中需要
//作者:李旭
{
    int nwLen = ::MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, NULL, 0);
    wchar_t * pwBuf = new wchar_t[nwLen + 1];
    ZeroMemory(pwBuf, nwLen * 2 + 2);
    ::MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.length(), pwBuf, nwLen);
    int nLen = ::WideCharToMultiByte(CP_UTF8, 0, pwBuf, -1, NULL, NULL, NULL, NULL);
    char * pBuf = new char[nLen + 1];
    ZeroMemory(pBuf, nLen + 1);
    ::WideCharToMultiByte(CP_UTF8, 0, pwBuf, nwLen, pBuf, nLen, NULL, NULL);
    std::string retStr(pBuf);
    delete []pwBuf;
    delete []pBuf;
    pwBuf = NULL;
    pBuf = NULL;
    return retStr;
}*/



string SQLserver::FtS(float Num)
//Float To String
//作者:李旭
{
    std::ostringstream oss;
    oss<<Num;
    std::string str(oss.str());
    return str;
}

string SQLserver::ItS(int Num)
//Int To String
//作者:李旭
{
    std::ostringstream oss;
    oss<<Num;
    std::string str(oss.str());
    return str;
}

string SQLserver::Time2String(struct tm time)
//Time To String
//作者:吴挺轩
{
    string s = "";
    s += ItS(time.tm_wday) + ',';
    s += ItS(time.tm_year+1900) + '/';
    s += ItS(time.tm_mon+1) + '/';
    s += ItS(time.tm_mday) + ',';
    s += ItS(time.tm_hour) + ':';
    s += ItS(time.tm_min) + ':';
    s += ItS(time.tm_sec);
    return s;
}


