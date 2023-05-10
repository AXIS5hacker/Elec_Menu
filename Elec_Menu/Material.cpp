#include "Material.h"

Material::Material(string name)
//构造函数
//作者:李旭
{
    this->name = name;
    this->ID = setID();
    this->remain = true;
}

Material::~Material()
{
    //dtor
}

int Material::setID()
//生成ID
//作者:李旭
{
    struct tm *tblock;
    time_t timer = time(NULL);
    tblock = localtime(&timer);
    int ID;
    ID = (tblock->tm_year-100) * 38400000 + tblock->tm_mon * 3200000 +
            tblock->tm_mday*100000 + tblock->tm_hour*3600 +
            tblock->tm_min*60+ tblock->tm_sec*1 + 0;
    return 0;
}

int Material::reviseName(string name)
//修改名字
//作者:李旭
{
    this->name = name;
    return 0;
}

int Material::unRemain()
//设置存量不足
//作者:李旭
{
    this->remain = false;
    return 0;
}

int Material::setRemain()
//设置存量充足
//作者:李旭
{
    this->remain = true;
    return 0;
}
