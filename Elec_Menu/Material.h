#ifndef MATERIAL_H
#define MATERIAL_H
#include<iostream>
#include<string>
#include<time.h>


using std::string;
//受限于时间紧张和此部分设计的复杂度，此部分已被放弃使用，但是我们依然保留了所写的相关代码
class Material
{
    public:
        //作者:李旭
        //构造函数
        Material(string name);

        virtual ~Material();

        //作者:李旭
        //取得ID
        int GetID() { return ID; }

        //作者:李旭
        //取得名字
        string GetName() { return name; }

        //作者:李旭
        //获取当前是否有存量
        bool GetRemain() { return remain; }

        //作者:李旭
        //修改名字
        int reviseName(string name);

        //作者:李旭
        //设置存量不足
        int unRemain();

        //作者:李旭
        //设置存量充足
        int setRemain();


    protected:

    private:
        //作者:李旭
        //生成ID
        int setID();
        int ID; //材料的ID
        string name; //材料的名字
        bool remain; //是否有存量
};

#endif // MATERIAL_H
