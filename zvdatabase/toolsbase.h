#ifndef TOOLS_H
#define TOOLS_H
#include <iostream>
#include <Qstring>
#include "toolsstructure.h"

using namespace std;

class toolsbase
{
public:
    virtual ~toolsbase()=0;//纯虚析构函数
    virtual void work()=0;//工具执行
    virtual void showui()=0;//显示界面获取数据
    virtual bool save(QString str)=0;//保存参数
    virtual bool load(QString str)=0;//加载参数
    virtual bool copyto(toolsbase &toolb)=0;//复制参数
    virtual void connectdb()=0;//连接数据库
    virtual void unconnect()=0;//断开数据库
    virtual void release()=0;//释放

};

#endif // TOOLS_H
