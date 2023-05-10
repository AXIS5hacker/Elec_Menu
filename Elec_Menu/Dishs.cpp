
#include "Dishs.h"
#include"SQLserver.h"

extern string qstr2str_utf8(const QString qstr);
extern QString str2qstr_utf8(const string str);
extern string ItS(int Num);
using namespace std;
Dishs::Dishs()
//Dishs 的构造函数
//作者:苏文韬
{
    MaxID = 0;
}

Dishs::~Dishs(){;}


int Dishs::AddDish(float price,string name,string describe,string jpgPath,SQLserver &sql){
//添加菜品，返回值表示是否添加成功
//作者:苏文韬
//input: describe菜品描述，jpgPath图片路径(扩展内容)
//output: 添加成功与否
    MaxID++;
    int ID = MaxID;
    Dish d (ID,name, price, jpgPath,false,describe);
    Dishlist.push_back(d);
    addToSQL(sql,d);//database operation
    return 0;
}

int Dishs::DeleteDish(Dish dish,SQLserver &sql){
//删除菜品，返回值表示是否添加成功
//作者:苏文韬
//input: sql与mySQL对接需要 Dish需要被删除的菜品
//output: 删除成功与否
    vector<Dish>::size_type i,m = Dishlist.size();
    for(i = 1;i<m;++i){
        if(CompareDish(Dishlist[i],dish)){
            deleteFromSQL(sql,Dishlist[i]);//database operation
            Dishlist.erase(Dishlist.begin()+i);
            return 0;
        }
    }
    return 1;
}

Dish& Dishs::GetDish(int ID)
//按照菜品id找菜品
//作者:苏文韬
//input: 菜品id
//output: 菜品
{
    vector<Dish>::size_type i,m = Dishlist.size();
    for(i = 1;i<m;++i)
    {
        if(Dishs::Dishlist[i].GetID() == ID)
        {
            return Dishlist[i];
            break;
        }
    }
    //Dish d(0,"",0,"",false,"");
    return Dishlist[0];
}

Dish& Dishs::GetDish(string name){
//按照菜品名称找菜品
//作者:苏文韬
//input: 菜品名称
//output: 菜品
    vector<Dish>::size_type i,m = Dishlist.size();
    for(i = 1;i<m;++i){
        if(Dishlist[i].Getname() == name){
            return Dishlist[i];
        }
    }
    //Dish d(0,"",0,"",false,"");
    return Dishlist[0];
}

int Dishs::GetSize()
//获取当前菜单菜品数量
//作者:苏文韬
//output: 菜品数量
{
    return Dishlist.size();
}

int Dishs::ReviseDish(Dish dish,int ID)
//用新的dish替换原菜单内id == ID的菜品
//作者:冯梓轩
{
    int p = 0;
    vector<Dish>::size_type i,m = Dishlist.size();
    for(i = 1;i<m;++i){
        if(Dishlist[i].GetID() == ID){
            Dishlist.erase(Dishlist.begin()+i);
            p = 1;
        }
    }
    Dishlist.push_back(dish);
    return p;
}

//deprecated

/*
int Dishs::printToFile(string file_name){
     *
     * 作者:冯梓轩
     * print the dishes list to a file
     * input:filename(string)
     * output:0=success,1=fail
     *
    ofstream fout(file_name);
    if (!fout.fail()){
        for(int i=0;i<GetSize();i++){//scan all dishes
            //get current dish
            Dish tmp=GetDish(i+1);
            //printing to file
            if(i==0){
                fout<<tmp.GetID();
            }else{
                fout<<endl<<tmp.GetID();
            }
            fout<<endl<<tmp.Getprice();
            fout<<endl<<tmp.Getname();
            fout<<endl<<tmp.Getdescribe();
            fout<<endl<<tmp.GetjpgPath();
        }
        fout.close();
        //qDebug()<<"WOAH";
        return 0;
    }else{
        return 1;
    }
}

int Dishs::readFormFile(string file_name){
     *
     * 作者:冯梓轩
     * read the dishes list from a file
     * input:filename(string)
     * output:0=success,1=fail
     *
    ifstream fin(file_name);
    if (!fin.fail()){
        int dish_id;//id
        float dish_price;//price
        string dish_name;//name
        string dish_describe;//description
        string dish_jpgPath;//jpgpath
        while(!fin.eof()){//start reading
            fin>>dish_id>>dish_price;
            //qDebug()<<dish_id<<dish_price;
            fin.ignore();
            getline(fin,dish_name);
            getline(fin,dish_describe);
            getline(fin,dish_jpgPath);
            //qDebug()<<str2qstr_utf8(dish_name);
            //add to list
            AddDish(dish_price,dish_name,dish_describe,dish_jpgPath);
        }
        fin.close();
        return 0;
    }else{
        //qDebug()<<"NAHHHH";
        return 1;
    }
}
*/

int Dishs::addToSQL(SQLserver &sql,Dish &d){
    /**
      *作者:冯梓轩
      *向数据库添加菜品
      *input:sql句柄,菜品
      *output:0(成功码)
      */
    sql.insertDish(d);
    return 0;
}

int Dishs::deleteFromSQL(SQLserver &sql,Dish &d){
    /**
      *作者:冯梓轩
      *向数据库删除菜品
      *input:sql句柄,菜品
      *output:0(成功码)
      */
    sql.deleteDish(d);
    return 0;
}

int Dishs::loadFromSQL(SQLserver &sql)
{
    //从数据库读入菜品
    //作者:苏文韬、冯梓轩
    //input: sql句柄
    //output: 成功码(0为成功)
    //MYSQL *mysql=sql.getSqlConnect();    //数据库句柄
    MYSQL_RES* res; //查询结果集
    MYSQL_ROW row;  //记录结构体
    Dishlist.clear();
    int ret = mysql_query(sql.getSqlConnect(), "SELECT * FROM dishs");
    res = mysql_store_result(sql.getSqlConnect());

    while (row = mysql_fetch_row(res))
    {
        Dish D(stoi(row[0]), row[1], stof(row[2]), row[3], bool(stoi(row[4])), row[5]);
        Dishlist.push_back(D);
        MaxID = max(MaxID, stoi(row[0]));
    }
    Dish D(0,"",0,"",false,"");
    Dishlist.insert(Dishlist.begin(), D);
    int DID;
    string sen;
    for(int i = 0; i < Dishlist.size(); i++){
        DID = Dishlist[i].GetID();
        sen = "select * from dish_material where Dish_ID = " + ItS(DID) ;
        ret = mysql_query(sql.getSqlConnect(), sen.c_str());
        res = mysql_store_result(sql.getSqlConnect());
        while (row = mysql_fetch_row(res)){
            Dishlist[i].addMaterial(row[1]);
        }
    }

    mysql_free_result(res);

    return 0;
}

//deprecated
/*int Dishs::saveToSQL(SQLserver &sql)
//菜品保存到数据库
//作者:黄志宏
//input: sql句柄
//output: 成功码
{
    //sql.clearTable("dishs");
    Dishlist.erase(Dishlist.begin());
    while(!Dishlist.empty()){
        Dish tmp = Dishlist.front();
        sql.insertDish(tmp);
        Dishlist.erase(Dishlist.begin());
    }
    return 0;
}*/
