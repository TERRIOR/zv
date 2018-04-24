/**
*@projectName   cvcamera
*@documentname  controlthread.h
*@author        zzJun
*@date          20180422
*@brief         control the thread
**/
#ifndef CONTROLTHREAD_H
#define CONTROLTHREAD_H

#include <QObject>
#include "camworker.h"
#include "cvcamera.h"
class CVCAMERASHARED_EXPORT controlthread : public QObject
{
    Q_OBJECT
public:
    explicit controlthread(QObject *parent = 0);
    controlthread(bool uicall);
    ~controlthread();
    void stopthread();
    void startthread();
    void release();
signals:
    void callui();
public slots:
    void refleshmat();

private:


    QThread *thread;
    CamWorker *worker;
    bool m_opened=false;
    bool m_uicall=false;//true:是dialog调用
};

#endif // CONTROLTHREAD_H
