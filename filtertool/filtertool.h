/**
*@projectName   filtertool
*@documentname  filtertool.h
*@author        zzJun
*@date          20180422
*@brief
**/
#ifndef FILTERTOOL_H
#define FILTERTOOL_H
#include "toolsbase.h"

#include "imageparam.h"
#include "zvdatabase_g.h"
#include "filtertool_global.h"
#include "fftfilter.h"
#include "filterdialog.h"
#include <QObject>
#define lowpasstype 0
#define bandpasstype 1


class Filtertool :public QDialog,public toolsbase
{
    Q_OBJECT
public:
    explicit Filtertool(QObject *parent = 0);
    //Filtertool();
    Filtertool(int index,int node,int runid,int idofstype);
     Filtertool(int node);
    ToolsStructure getToolparam() const;//获取数据库形式参数
    void setToolparam(int index,int node,int runid,int idofstype);//设置数据库形式参数
    void settool(int type,int high,int low,int stage,int size);
    void lowblur();
    void bandpassfilter();
    // toolsbase interface
    ~Filtertool();
    void work();
    void showui();
    bool save(QString str);
    bool load(QString str);
    bool copyto(toolsbase &toolb);
    void connectdb();
    void unconnect();
    void release();

    int getPasstype() const;
    void setPasstype(int value);
public slots:
    void refusecreate();//取消创建
    void confirmcreat();//确认创建
    void receivework(int type,int high,int low,int stage,int size);//处理图像
    void receivestruct(ParamStructure structure);//接收参数的结构
signals:
    void sendmat(Mat m);//发送图像给dialog
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
    /**
     * convert size
     */
    int m_isize;
    ImageParam *imgparamin;
    ImageParam imgparamout;
    ToolsStructure toolparam;//数据库参数

};


#endif // FILTERTOOL_H
