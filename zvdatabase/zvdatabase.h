#ifndef ZVDATABASE_H
#define ZVDATABASE_H
#include<iostream>
#include "zvdatabase_global.h"
#include "paramheader.h"
#include <map>
using namespace std;

class ZVDATABASESHARED_EXPORT Zvdatabase
{

public:
    Zvdatabase();
    ~Zvdatabase();
    //释放
    void release();
    //在tools工具中调用，用于储存数据到数据库类
    bool saveparam(ZvBaseParam* param);
    //更新变量的值
    void refreshparam(ZvBaseParam* param);
    //删除变量的值
    bool delparam(ParamStructure *params);
    //弹出界面选择变量
    void selectparam(ZvBaseParam* param);
    //清除数据库所有数据
    void clearall();
    //判断是否存在数据
    bool isempty();
    //在tools工具work时，需要从数据库类取出数据，实现运行
    void getparam(ZvBaseParam* param);
private:
    map<ParamStructure,ZvBaseParam*> *zvmap;
};

#endif // ZVDATABASE_H
