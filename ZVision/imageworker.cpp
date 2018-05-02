#include "imageworker.h"


imageworker::imageworker(QObject *parent) : QObject(parent)
{
    _working =false;
    _abort = false;

}

void imageworker::requestWork()
{
    inmutex.lock();
    _working = true;
    _abort = false;
    qDebug()<<"Request worker start in Thread "<<thread()->currentThreadId();
    imgcamp=dynamic_cast<ImageParam*>( zvdata->getparamster(ParamStructure("cam",0,0,imagetype,0)));
    imgcam=imgcamp->pic();
    inmutex.unlock();
    emit workRequested();
}

void imageworker::abort()
{
    inmutex.lock();
    if (_working) {
        _abort = true;
        qDebug()<<"Request worker aborting in Thread "<<thread()->currentThreadId();
    }
    inmutex.unlock();
}

void imageworker::doWork()
{
    while(1){
        inmutex.lock();
        bool abort = _abort;
        inmutex.unlock();
        if (abort) {
            qDebug()<<"Aborting worker process in Thread "<<thread()->currentThreadId();
            break;
        }
        QTime time;
        time.start();
        outmutex.lock();
        refreshmat();
        outmutex.unlock();
        cout<<"refreshmat: "<<time.elapsed()<<"ms"<<endl;
        int i;
        int size=zvdata->getToolvectsize();
        for(i=0;i<size;i++){
            time.start();
            toolsbase* tool=zvdata->gettool(i);
            if(!tool->work()){
                break;
            }
            cout<<"tool "<<i<<": "<<time.elapsed()<<"ms"<<endl;
        }

        Sleep(0);
    }
    emit finished();
}
void imageworker::refreshmat()
{
    //更新从相机获取的画面
    //*imgcam=cvcam->getLastestmat();
    cvcam->refreshCameraImg();
    //当缓冲小于最大值的一半，说明图像处理的速度比读取快，可以获取队列的最早图像
    //当大于一半时，图像算法慢，需要优化，取最新的图像处理，会有失真
    if(cvcam->queuesize()<cvcam->getMax()/2){
        *imgcam=cvcam->getmCameraImg();
    }else{
        *imgcam=cvcam->getLastestmat();
        cout<<"over load"<<endl;
    }

}
