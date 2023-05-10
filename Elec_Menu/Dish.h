#ifndef DISH_H
#define DISH_H

#include<iostream>
#include<string>
#include<vector>
#include"Material.h"
using std::vector;
using std::string;
using std::ifstream;
using std::ofstream;
using std::ostream;


class Dish
{
    public:
            //作者:苏文韬
            //菜品构造函数
            //input: describe菜品描述，jpgPath图片路径(扩展内容)
            //output: void
            Dish(){;}
            Dish(int DishID,string name,float price,string jpgPath,bool onSell,string describe);

            //菜品析构函数
            virtual ~Dish();

            //作者:李旭
            //获取菜品id
            int GetID() { return DishID; }
            //作者:李旭
            //设置菜品id
            void SetID(int val) { DishID = val; }
            //作者:李旭
            //获取菜品名
            string Getname() { return name; }
            //作者:李旭
            //设置菜品名
            void Setname(string val) { name = val; }
            //作者:李旭
            //获取价格
            float Getprice() { return price; }
            //作者:李旭
            //设置价格
            void Setprice(float val) { price = val; }
            //作者:李旭
            //获取菜品描述
            string Getdescribe() { return describe; }
            //作者:李旭
            //设置菜品描述
            void Setdescribe(string val) { describe = val; }
            //作者:李旭
            //获取菜品图片路径
            string GetjpgPath() { return jpgPath; }
            //作者:李旭
            //设置菜品图片路径
            void SetjpgPath(string val) { jpgPath = val; }
            //作者:苏文韬
            //菜品下架
            void Unsell();
            //作者:苏文韬
            //菜品上架
            void Onsell();
            //作者:苏文韬
            //获取是否上架
            bool getsell();
            //作者:苏文韬
            //添加原料
            int addMaterial(string m_name);
            //作者:苏文韬
            //删除原料
            int removeMaterial(string m_name);
            //作者:苏文韬
            //获取原料列表
            vector<int> getMaterial();

        //string print();
        //作者:吴挺轩
        //重载<<运算符，方便直接cout
        //
        ostream& operator << (ostream &os);


    //protected:

private:
        int DishID; //菜品ID
        string name; //菜品名称
        float price; //菜品价格
        string describe; //菜品描述
        string jpgPath; //菜品图片的文件路径（实际未实现）
        vector<int> materials;//菜品所关联的材料集
        bool onSell;//是否上架
};

#endif // DISH_H
