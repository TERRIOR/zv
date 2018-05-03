/**
*@projectName   zvdatabase
*@documentname  zvdatabase.h
*@author        zzJun
*@date          20180422
*@brief         define the database class
**/
#ifndef ZVDATABASE_H
#define ZVDATABASE_H
#include<iostream>
#include "zvdatabase_global.h"
#include "paramheader.h"
#include "toolsbase.h"
#include <vector>
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
    //在主工程中调用，用于储存工具到数据库类

    //更新变量的值
    void refreshparam(ZvBaseParam* param);
    //删除变量的值
    bool delparam(ParamStructure *params);
    //弹出界面选择变量
    void selectparam(ZvBaseParam* param);
    //清除数据库所有数据
    void clearall();
    //判断是否存在数据
    void clearallvec();
    bool isempty();
    //在tools工具work时，需要从数据库类取出数据，实现运行
    void getparam(ZvBaseParam* param);
    ZvBaseParam *getparamster(ParamStructure Structure);
    map<ParamStructure, ZvBaseParam *> *getZvmap() const;
    int getToolvectsize() const;
    toolsbase* gettool(int i);
    int getToolcount() const;
    void setToolcount(int value);
    void addtoolcount();
    void minustoolcount();
    void savetool(toolsbase *toolb);
    void deltool();
    void releasetool();
    int getindex(int node);
    void addindex(int node);
    void minusindex(int node);
    void setindex(int node,int index);
    toolsbase* findtool(int id);
private:
    map<ParamStructure,ZvBaseParam*> *zvmap;
    vector<toolsbase*> toolvect;
    int toolcount=0;
    int indexcount[10];//最多是个流程，每个索引下的数指该node下拥有的index数

};
extern ZVDATABASESHARED_EXPORT Zvdatabase *zvdata;
#endif // ZVDATABASE_H
