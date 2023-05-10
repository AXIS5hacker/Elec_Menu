#ifndef SQL_SERVER
#define SQL_SERVER


#include "include/mysql.h"
#include "Dish.h"
#include "Order.h"
#include <sstream>
#include "Material.h"
#include <vector>

//#include <wchar.h>
//#include <windows.h>
//此部分所需的mySQL语句由吴挺轩设计
using std::string;

class SQLserver
{
public:
    //构造函数
    SQLserver();
    //析构函数
    virtual ~SQLserver();

    //作者:李旭
    //打开mySQL链接
    int openSQL();

    //作者:李旭
    //关闭mySQL链接
    int closeSQL();

    //作者:李旭
    //插入一个菜品
    int insertDish(Dish &a);

    //作者:苏文韬
    //插入一个材料
    int insertMaterial(Material &a);

    //作者:吴挺轩
    //存入一个订单
    int insertOrder(Order &a);

    //作者:李旭
    //菜品修改
    int reviseDish(Dish &a);

    //作者:李旭
    //菜品删除
    int deleteDish(Dish &a);

    //作者:冯梓轩
    //清除一项表单
    int clearTable(string tablename);

    //作者:吴挺轩
    //删除材料
    int deleteMaterial(Material &a);

    //作者:吴挺轩
    //修改材料
    int reviseMaterial(Material &a);

    //作者:李旭
    //获取错误信息
    string getWrong(){return mysql_error(&mysql);};

    //作者:冯梓轩
    //获取指定参数
    MYSQL* getSqlConnect(){return &mysql;};
protected:


private:
    MYSQL mysql;     //mysql连接
    MYSQL_FIELD *fd; //字段列数组
    MYSQL_RES* res; //查询结果集
    MYSQL_ROW row;  //记录结构体

    //作者:李旭
    //此函数用于将字符串转化为UTF-8格式，测试证明在QT中并不需要（但是在codeblocks中需要
    //string string_To_UTF8(const string & str);     //警告：对于有中文的语句，请务必使用其套一层

    //作者:李旭
    //Float To String
    string FtS(float Num);

    //作者:李旭
    //Int To String
    string ItS(int Num);

    //作者:吴挺轩
    //Time To String
    string Time2String(struct tm time);
};
#endif

