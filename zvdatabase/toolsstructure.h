#ifndef TOOLSSTRUCTURE_H
#define TOOLSSTRUCTURE_H
#include "String"
#include <iostream>
using namespace std;
//工具类所需要的基本数据结构
static string strzu[20]={"Filtertool","Binarytool","Matchtool","Ruletool"};
class ToolsStructure
{
public:
    ToolsStructure();
    ToolsStructure(int index,int node,int runid,int idofstype);
    void setallparam(int index,int node,int runid,int idofstype);//设置所有的数据库参数
    void getallparam(int *param);//以数组的形式获取数据库参数
    int iNode() const;
    void setINode(int iNode);
    int iIndex() const;
    void setIIndex(int iIndex);
    int iRunId() const;
    void setIRunId(int iRunId);
    int iIdOfStype() const;
    void setIIdOfStype(int iIdOfStype);
    bool operator<(const ToolsStructure& ts) const;
private:
    int m_iNode;//流程序号
    int m_iIndex;//步骤序号
    int m_iRunId;//执行序号
    int m_iIdOfStype;//类型序号
    /*
    *类型列表：
    *
    */
};

#endif // TOOLSSTRUCTURE_H
