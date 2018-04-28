/**
*@projectName   filtertool
*@documentname  filtertool.h
*@author        zzJun
*@date          20180422
*@brief         a tool used to filter Image
*slots,signals函数,以及重载函数声明几乎不变，不过要重新实现
*setToolparam getToolparam一定要实现，其他函数根据需求定义
**/
#ifndef FILTERTOOL_H
#define FILTERTOOL_H
#include "toolsbase.h"
#include "imageparam.h"
#include "zvdatabase_g.h"
#include "fftfilter.h"
#include "filterdialog.h"
#include <QObject>
#include "qgloble.h"
#define lowpasstype 0
#define bandpasstype 1

//QDialog的继承要放第一位
class Filtertool :public QDialog,public toolsbase
{
    Q_OBJECT
public:
    explicit Filtertool(QObject *parent = 0);
    Filtertool(int node);
    //获取数据库形式参数
    ToolsStructure getToolparam() const;
    //设置数据库形式参数
    void setToolparam(int index,int node,int runid,int idofstype);
    //设置work时所需要的参数
    void settool(int type,int high,int low,int stage,int size);
    //低通滤波
    void lowblur();
    //带通滤波
    void bandpassfilter();
    int getPasstype() const;
    void setPasstype(int value);

    // toolsbase interface
    ~Filtertool();
    void work();
    void showui();
    bool save(QTextStream &out);//保存参数
    bool load(QTextStream &In);//加载参数
    bool copyto(toolsbase &toolb);
    void connectdb();
    void unconnect();
    void release();
    void creatconfirm();
public slots:
    //取消创建
    void refusecreate();
    //确认创建
    void confirmcreat();
    //处理图像，接收参数(不同工具需要重新写形参)
    void receivework(int type,int high,int low,int stage,int size);
    //接收参数的结构
    void receivestruct(ParamStructure structure);
signals:
    //发送图像给dialog
    void sendmat(Mat m);

private:
    bool showed=false;
    Mat m_inpic;
    Mat m_outpic;
    /**
     * 0:lowpass
     * 1:bandpass
     */
    int m_ipasstype=-1;
    /**
     * bandpass param
     */
    int m_ihigh;
    int m_ilow;
    int m_istage;
    // convert size
    int m_isize;
    //输入是引入，所以以指针形式
    ImageParam *imgparamin;
    ImageParam imgparamout;
    ToolsStructure toolparam;//数据库参数
};


#endif // FILTERTOOL_H
