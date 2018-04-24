#include "controlthread.h"

controlthread::controlthread(QObject *parent) : QObject(parent)
{
    thread = new QThread();
    worker = new CamWorker();

    worker->moveToThread(thread);
    connect(worker, SIGNAL(imgchange()),this, SLOT(refleshmat()));//与ui结合时用
    connect(worker, SIGNAL(workRequested()), thread, SLOT(start()));//1,worker请求，触发thread的start
    connect(thread, SIGNAL(started()), worker, SLOT(doWork()));//2,start后 dowork(实质工作的地方)
    connect(worker, SIGNAL(finished()), thread, SLOT(quit()), Qt::DirectConnection);
}
controlthread::controlthread(bool uicall)
:m_uicall(uicall)
{
    thread = new QThread();
    worker = new CamWorker();

    worker->moveToThread(thread);
    //connect(worker, SIGNAL(imgchange()),this, SLOT(refleshmat()));//与ui结合时用
    connect(worker, SIGNAL(workRequested()), thread, SLOT(start()));//1,worker请求，触发thread的start
    connect(thread, SIGNAL(started()), worker, SLOT(doWork()));//2,start后 dowork(实质工作的地方)
    connect(worker, SIGNAL(finished()), thread, SLOT(quit()), Qt::DirectConnection);
}

controlthread::~controlthread()
{
    cout<<"release control"<<endl;
}

void controlthread::refleshmat()//做监控
{
    int size;
    size= cvcam->queuesize();
    //cout<<"reflesh: "<<size<<endl;
}
void controlthread::stopthread()
{
    if(m_opened){
        worker->abort();
        thread->wait();
        //qDebug()<<"Deleting thread and worker in Thread "<<this->QObject::thread()->currentThreadId();
        m_opened=false;
    }
}

void controlthread::startthread()
{
    if(!m_opened){
        worker->abort();
        thread->wait();
        worker->requestWork();
        m_opened=true;
    }
}

void controlthread::release()
{
    stopthread();
    delete thread;
    delete worker;
    delete this;
    thread=NULL;
    worker=NULL;
}
