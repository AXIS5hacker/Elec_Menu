#ifndef MATERIALS_H
#define MATERIALS_H

#include <vector>
#include "Material.h"
using std::string;
using std::vector;
//受限于时间紧张和此部分设计的复杂度，此部分已被放弃使用，但是我们依然保留了所写的相关代码
class Materials
{
    public:
        //构造函数
        Materials();
        //析构函数
        virtual ~Materials();

        //作者:李旭
        //添加材料
        static int addMaterial(string name);

        //作者:李旭
        //删除材料
        static int removeMaterial(string name);

        //作者:李旭
        //通过ID获取材料名称
        static string findMaterialName(int ID);

        //作者:李旭
        //通过名称获取材料ID
        static int findMaterialID(string name);

        //作者:李旭
        //通过数组下标获取材料名称
        static string getMaterialName(int index);

        //作者:李旭
        //修改材料名称
        //input:oldname原名称，newname更改之后的名称
        static int reviseMaterialName(string oldName,string newName);

        //作者:李旭
        //取得材料总量
        static int getSize();

        /*
        static int saveToSQL();
        static int loadFromSQL();
        */
    protected:

    private:
        static vector<Material> materialList; //材料的集合
};

#endif // MATERIALS_H
