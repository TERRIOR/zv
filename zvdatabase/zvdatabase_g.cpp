#include "zvdatabase_g.h"

//全局静态变量，标志数据类是否被实例化，防止重复操作
static bool bbuilded=false;

void creatzvdata()
{
    if(!bbuilded){
        zvdata=new Zvdatabase();
        //return zvdata;
        cout<<"creat"<<endl;
        bbuilded=true;
    }
}

Zvdatabase *getzvdata()
{
    return zvdata;
}

Zvdatabase* destroyzvdata()
{
    if(bbuilded){
        zvdata->release();
        zvdata=NULL;
        cout<<"destroy"<<endl;
        bbuilded=false;
    }
    return zvdata;
}

QDialog* showdbDialog(){
    SelectDialog *seldia=new SelectDialog();
    return seldia;
}
