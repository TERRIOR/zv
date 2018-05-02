#include "camworker.h"
CamWorker::CamWorker(QObject *parent) : QObject(parent)
{
    _working =false;
    _abort = false;
    cvcam->setMax(10);
}

void CamWorker::requestWork()
{
    inmutex.lock();
    _working = true;
    _abort = false;
    qDebug()<<"Request worker start in Thread "<<thread()->currentThreadId();
    inmutex.unlock();
    emit workRequested();
}

void CamWorker::abort()
{
    inmutex.lock();
    if (_working) {
        _abort = true;
        qDebug()<<"Request worker aborting in Thread "<<thread()->currentThreadId();
    }
    inmutex.unlock();
}

void CamWorker::doWork()
{
    while(1){
        inmutex.lock();
        bool abort = _abort;
        inmutex.unlock();
        if (abort) {
            qDebug()<<"Aborting worker process in Thread "<<thread()->currentThreadId();
            break;
        }
        cvcam->cap();//这是耗时操作，不能放在锁里！
        outmutex.lock();
        cvcam->addcamimg();//更新缓冲
        outmutex.unlock();
        emit imgchange();
        Sleep(0);
    }
    emit finished();
}
