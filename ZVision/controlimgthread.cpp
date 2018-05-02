#include "controlimgthread.h"

controlimgthread::controlimgthread(QObject *parent) : QObject(parent)
{
    thread = new QThread();
    worker = new imageworker();

    worker->moveToThread(thread);
    //connect(worker, SIGNAL(imgchange()),this, SLOT(refleshmat()));//与ui结合时用
    connect(worker, SIGNAL(workRequested()), thread, SLOT(start()));//1,worker请求，触发thread的start
    connect(thread, SIGNAL(started()), worker, SLOT(doWork()));//2,start后 dowork(实质工作的地方)
    connect(worker, SIGNAL(finished()), thread, SLOT(quit()), Qt::DirectConnection);
}

controlimgthread::~controlimgthread()
{
    delete thread;
    delete worker;
    thread=NULL;
    worker=NULL;
    cout<<"release control"<<endl;
}

void controlimgthread::stopthread()
{
    if(m_opened){
        worker->abort();
        thread->wait();
        //qDebug()<<"Deleting thread and worker in Thread "<<this->QObject::thread()->currentThreadId();
        m_opened=false;
    }
}

void controlimgthread::startthread()
{
    if(!m_opened){
        worker->abort();
        thread->wait();
        worker->requestWork();
        m_opened=true;
    }
}

void controlimgthread::release()
{
    if(m_opened){
        stopthread();
        delete this;
    }


}

bool controlimgthread::opened() const
{
    return m_opened;
}

void controlimgthread::setOpened(bool opened)
{
    m_opened = opened;
}
