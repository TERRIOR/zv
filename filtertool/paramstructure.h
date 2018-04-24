/**
*@projectName
*@documentname  paramstructure.h
*@author        zzJun
*@date          20180422
*@brief         the structure of param
**/
#ifndef PARAMSTRUCTURE_H
#define PARAMSTRUCTURE_H
#include <string>
//类型的宏定义
#define pointtype 0
#define linetype 1
#define circletype 2
#define recttype 3
#define imagetype 4
#define resulttype 5

using namespace std;
class ParamStructure
{
public:
    ParamStructure();
    ParamStructure(string paramname, int index, int node, int stype,int id);
    //数据所在的工具名称
    void setStructure(string paramname, int index, int node, int stype,int id);//paramname, index, node, stype
    string getSparamName() const;
    void setSparamName(const string &value);

    int getIstype() const;
    void setIstype(int value);

    int getINode() const;
    void setINode(int value);

    int getIIndex() const;
    void setIIndex(int value);

    int getIId() const;
    void setIId(int value);
    //用于map的判断
    bool operator<(const ParamStructure& Param) const;
private:
    string sparamName="-1";
    /*
    * 数据的类型
    * 0:point
    * 1:line
    * 2:circle
    * 3:rect
    * 4:image
    * 5:result
    */
    int istype=-1;
    //数据所在的流程序号
    int iNode=-1;
    //数据在该流程中的顺序排名
    int iIndex=-1;
    int iId=-1;
};

#endif // PARAMSTRUCTURE_H
