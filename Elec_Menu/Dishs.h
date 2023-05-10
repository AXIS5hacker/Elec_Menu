#ifndef DISHS_H
#define DISHS_H

#include "Dish.h"
#include "SQLserver.h"

#include<fstream>
#include<QDebug>
#define _HAS_STD_BYTE 0
using std::vector;
using std::string;
using std::ifstream;
using std::ofstream;

class Dishs
{
    public:
        Dishs();
        virtual ~Dishs();

        static bool CompareDish(Dish A, Dish B){
            return (A.GetID()==B.GetID())&&(A.Getname()==B.Getname())&&(A.Getprice()==B.Getprice())&&(A.Getdescribe()==B.Getdescribe())&&(A.GetjpgPath()==B.GetjpgPath());
        }

        //作者:苏文韬
        //添加菜品，返回值表示是否添加成功
        //input: describe菜品描述，jpgPath图片路径(扩展内容)
        //output: 添加成功与否
        static int AddDish(float price,string name,string describe,string jpgPath,SQLserver &sql);

        //作者:苏文韬
        //删除菜品，返回值表示是否添加成功
        //input: 如下
        //output: 删除成功与否
        static int DeleteDish(Dish dish,SQLserver &sql);

        //作者:苏文韬
        //按照菜品id找菜品
        //input: 菜品id
        //output: 菜品
        static Dish& GetDish(int ID);

        //作者:苏文韬
        //按照菜品名称找菜品
        //input: 菜品名称
        //output: 菜品
        static Dish& GetDish(string name);

        //作者:苏文韬
        //获取当前菜单菜品数量
        //output: 菜品数量
        static int GetSize();

        //作者:冯梓轩
        //用新的dish替换原菜单内id == ID的菜品
        static int ReviseDish(Dish dish,int ID);

        //一阶段使用
        //static int printToFile(string file_name);
        //static int readFormFile(string file_name);

        //sql部分

        //作者:苏文韬、冯梓轩
        //从数据库读入菜品
        //input: sql句柄
        //output: 成功码(0为成功)
        static int loadFromSQL(SQLserver &sql);

        //作者:黄志宏
        //菜品保存到数据库
        //input: sql句柄
        //output: 成功码
        //已放弃使用(因为会导致很多问题)
        //static int saveToSQL(SQLserver &sql);

        //作者:冯梓轩
        //添加菜品到数据库
        //input: sql句柄,菜品
        //output: 成功码
        static int addToSQL(SQLserver &sql,Dish &d);

        //作者:冯梓轩
        //从数据库删除菜品
        //input: sql句柄,菜品
        //output: 成功码
        static int deleteFromSQL(SQLserver &sql,Dish &d);
    private:
        static vector<Dish> Dishlist;
        static int MaxID;
        friend class Dish;
};

//vector<Dish> Dishs::Dishlist = vector<Dish>();

#endif // DISHS_H
