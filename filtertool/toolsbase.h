#ifndef TOOLS_H
#define TOOLS_H
#include <iostream>
#include <Qstring>
#include "toolsstructure.h"
#include <QFile>
#include <QTextStream>
#include <QDataStream>
//TODO:define the type
#define filtertooltype 0

using namespace std;

class toolsbase
{
public:
    virtual ~toolsbase()=0;//纯虚析构函数
    virtual bool work()=0;//工具执行
    virtual void showui()=0;//显示界面获取数据
    virtual bool save(QTextStream &out)=0;//保存参数
    virtual bool load(QTextStream &in)=0;//加载参数
    virtual bool savetool(QTextStream &out)=0;//保存工具
    virtual bool loadtool(QTextStream &in)=0;//加载工具
    virtual bool copyto(toolsbase &toolb)=0;//复制参数
    virtual void getToolparam(ToolsStructure& toolstruct)=0;
    virtual void connectdb()=0;//连接数据库
    virtual void unconnect()=0;//断开数据库
    virtual void release()=0;//释放
    virtual void creatconfirm()=0;//确认创建
};

#endif // TOOLS_H
