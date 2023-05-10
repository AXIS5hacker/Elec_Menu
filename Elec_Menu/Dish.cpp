#include "Dish.h"
#include"Materials.h"
Dish::Dish(int DishID,string name,float price,string jpgPath,bool onSell,string describe)
//Dish的构造函数
//input: describe菜品描述，jpgPath图片路径(扩展内容)
//output: void
//作者：苏文韬
{
    this->DishID = DishID;
    this->price = price;
    this->name = name;
    this->describe = describe;
    this->jpgPath = jpgPath;
    this->onSell=onSell;
}

Dish::~Dish(){;}

void Dish::Unsell()
//菜品下架
//作者:苏文韬
{
    onSell = false;
}

void Dish::Onsell(){
//菜品上架
//作者:苏文韬
    onSell = true;
}

bool Dish::getsell(){
//添加原料
//作者:苏文韬
    return onSell;
}

int Dish::addMaterial(string m_name)
{
    //添加原料
    //作者:苏文韬
    int m_id = Materials::findMaterialID(m_name);
    vector<int>::size_type i, m = materials.size();
    bool flag = true;
    for(i=0;i<m;++i)
    {
        if(materials[i] == m_id)
        {
            flag = false;
            break;
        }
    }
    if(flag)//新的原料插入
    {
        materials.push_back(m_id);
        return 0;
    }
    else//重复插入要阻止
    {
        return 1;
    }
}
int Dish::removeMaterial(string m_name)
{
    //删除原料
    //作者:苏文韬
    int m_id = Materials::findMaterialID(m_name);
    vector<int>::size_type i, m = materials.size();
    vector<int>::iterator iter;
    bool flag = true;
    for(i=0;i<m;++i)
    {
        if(materials[i] == m_id)
        {
            flag = false;
            iter = materials.begin() + i;
            break;
        }
    }
    if(flag)//有当前原料
    {
        materials.erase(iter);
        return 0;
    }
    else//没有当前原料
    {
        return 1;
    }
}

vector<int> Dish::getMaterial()
//获取原料列表
//作者:苏文韬
{
    return materials;
}

ostream& Dish::operator<<(ostream &os)
{
//测试用函数
//作者:吴挺轩
    os<<"()";//用输出内容替换掉引号内
    return os;
}
