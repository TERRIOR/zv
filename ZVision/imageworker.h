#ifndef IMAGEWORKER_H
#define IMAGEWORKER_H

#include <QObject>
#include <QTime>
#include "cvcamera_g.h"
#include "zvdatabase.h"
class imageworker : public QObject
{
    Q_OBJECT
public:
    explicit imageworker(QObject *parent = 0);
    void requestWork();//请求工作
    void abort();//结束工作
    void refreshmat();
signals:
    void workRequested();//已经请求
    void finished();//已经结束工作
    //void imgchange();//通知ui主线程更新显示
public slots:
    void doWork();//do something
private:
    bool _abort;//abort:停止 用于停止程序的运行
    bool _working;//是否工作的判断的变量
    QMutex inmutex;//类里变量的锁
    ImageParam *imgcamp;
    Mat *imgcam;
};

#endif // IMAGEWORKER_H
