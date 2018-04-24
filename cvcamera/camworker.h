/**
*@projectName   cvcamera
*@documentname  camworker.h
*@author        zzJun
*@date          20180422
*@brief         a worker used in a thread to get the camera picture
**/
#ifndef CAMWORKER_H
#define CAMWORKER_H

#include <QObject>
#include <QMutex>
#include <QThread>
#include "cvcamera.h"
#include <windows.h>
#include <qdebug.h>
#pragma comment(lib, "Gdi32.lib")
#pragma comment(lib,"user32.lib")
class  CamWorker : public QObject
{
    Q_OBJECT
public:
    explicit CamWorker(QObject *parent = 0);
    void requestWork();//请求工作
    void abort();//结束工作
signals:
    void workRequested();//已经请求
    void finished();//已经结束工作
    void imgchange();//通知ui主线程更新显示
public slots:
    void doWork();//do something
private:
    bool _abort;//abort:停止 用于停止程序的运行
    bool _working;//是否工作的判断的变量
    QMutex inmutex;//类里变量的锁
};

#endif // CAMWORKER_H
