/**
*@projectName
*@documentname  zvbaseparam.h
*@author        zzJun
*@date          20180422
*@brief         the base class of param class
**/
#ifndef ZVPARAM_H
#define ZVPARAM_H
#include <string>
#include "paramstructure.h"
using namespace std;
//ZV数据结构基类
class ZvBaseParam
{
public:
    ZvBaseParam();
    ZvBaseParam(string paramname,int index,int node,int stype,int id);
    virtual ~ZvBaseParam();
    void setDbParam(string paramname="-1", int index=-1, int node=-1, int stype=-1,int id=-1);
    ParamStructure getDbParam() const;


private:
    ParamStructure m_dbParam;

};

#endif // ZVPARAM_H
