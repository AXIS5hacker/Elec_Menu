#include<QString>
#include<string>
#include<sstream>
#include<vector>
#include"Order.h"
#include"Dishs.h"
using namespace std;

string qstr2str_utf8(const QString qstr){
    /*
     * 作者:冯梓轩
     * QString->string
     * input:QString
     * output:string(utf8)
     */
    QByteArray cdata=qstr.toUtf8();
    return string(cdata);
}
QString str2qstr_utf8(const string str){
    /*
     * 作者:冯梓轩
     * string->QString
     * input:string(utf8)
     * output:QString
     */
    return QString::fromUtf8(str.data());
}

QString generate_content(const Order &od){
    /*
     * 作者:冯梓轩
     * 将order信息保存为QString
     * input:Order
     * output:QString
     */
    ostringstream os;
    vector<pair<int,int> > dlist=od.getDLS();
    for(int i=0;i<dlist.size();i++){
        string tpname=Dishs::GetDish(dlist[i].first).Getname();
        int tpcount=dlist[i].second;
        if(i==0){
            os<<tpname<<"\t数量:"<<tpcount;
        }else{
            os<<"\n"<<tpname<<"\t数量:"<<tpcount;
        }
    }
    return str2qstr_utf8(os.str());
}

string ItS(int Num)
{
    std::ostringstream oss;
    oss<<Num;
    std::string str(oss.str());
    return str;
}
