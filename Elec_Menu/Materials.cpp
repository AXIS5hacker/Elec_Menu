#include "Materials.h"


Materials::Materials()
//构造函数
{
    //ctor
}

Materials::~Materials()
//析构函数
{
    //dtor
}

int Materials::addMaterial(string name)
//添加材料
//作者：李旭
{
    Material a(name);
    materialList.push_back(a);
    return 0;
}

string Materials::findMaterialName(int ID)
//通过ID获取材料名称
//作者:李旭
{
    vector<Material>::size_type i, m = materialList.size();
    for(i=0;i<m;i++)
        if(materialList[i].GetID() == ID)
            return (materialList[i]).GetName();
    return "not found!";
}

int Materials::findMaterialID(string name)
//通过名称获取材料ID
//作者:李旭
{
    vector<Material>::size_type i, m = materialList.size();
    for(i=0;i<m;i++)
        if(materialList[i].GetName() == name)
            return (materialList[i]).GetID();
    return -1;
}

string Materials::getMaterialName(int index)
//通过下标获取材料名称
//作者:李旭
{
    return (materialList[index]).GetName();
}

int Materials::removeMaterial(string name)
//删除材料
//作者:李旭
{
    vector<Material>::size_type i, m = materialList.size();
    for(i=0;i<m;i++)
        if(materialList[i].GetName() == name)
        {
            materialList.erase(materialList.begin() + i);
            return 0;
        }
    return -1;
}

int Materials::reviseMaterialName(string oldName,string newName)
//修改材料名称
//作者:李旭
//input:oldname原名称，newname更改之后的名称
{
    vector<Material>::size_type i, m = materialList.size();
    for(i=0;i<m;i++)
        if(materialList[i].GetName() == oldName)
        {
            materialList[i].reviseName(newName);
            return 0;
        }
    return 1;
}

int Materials::getSize()
//取得材料总量
//作者:李旭
{
    return materialList.size();
}
