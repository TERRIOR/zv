#include "cvcamera.h"

cvcamera *cvcam=NULL;
QMutex outmutex;
cvcamera::cvcamera()
{
    capture=new VideoCapture();
    loadData();
}

cvcamera::~cvcamera()
{
    delete capture;
    capture=NULL;
    cout<<"release cvcam"<<endl;
}

void cvcamera::release()
{
    delete this;
}

int cvcamera::refreshCameraImg()
{
    int size=camimgque.size();
    if(size>0){
        //img=camimgque.front();
        m_mCameraImg=camimgque.front();
        camimgque.pop();
    }else{
        //cout<<"queue is empty"<<endl;
    }

    return size;
}

int cvcamera::queuesize()
{
    return camimgque.size();
}

void cvcamera::addcamimg()
{

    if(capture->isOpened()){
        *capture >> lastestmat;
        if(camimgque.size()>max){
            camimgque.pop();
        }
        camimgque.push(lastestmat);
    }

}

bool cvcamera::opencamera()
{

    if(m_iWidth!=-1)
        capture->set(CV_CAP_PROP_FRAME_WIDTH, m_iWidth);//宽度
    if(m_iHight!=-1)
        capture->set(CV_CAP_PROP_FRAME_HEIGHT, m_iHight);//高度
    if(m_iFps!=-1)
        capture->set(CV_CAP_PROP_FPS, m_iFps);//帧数
        cout<<m_iFps<<endl;
    if(m_iBrightness!=-1)
        capture->set(CV_CAP_PROP_BRIGHTNESS, m_iBrightness);//亮度
    if(m_iContrast!=-1)
        capture->set(CV_CAP_PROP_CONTRAST,m_iContrast);//对比度
    if(m_iSaturation!=-1)
        capture->set(CV_CAP_PROP_SATURATION, m_iSaturation);//饱和度
    if(m_iHue!=-1)
        capture->set(CV_CAP_PROP_HUE, m_iHue);//色调
    if(m_iExposure!=-1)
        capture->set(CV_CAP_PROP_EXPOSURE, m_iExposure);//曝光
    if(!capture->isOpened())
        return capture->open(m_iCameraId);
    else return false;
}

void cvcamera::setcamera(int id, int width, int hight, int fps, int exposure, int brightness, int contrast, int hue, int saturation)
{
    m_iCameraId=id;
    m_iWidth=width;
    m_iHight=hight;
    m_iFps=fps;
    m_iExposure=exposure;
    m_iBrightness=brightness;
    m_iContrast=contrast;
    m_iHue=hue;
    m_iSaturation=saturation;
}

bool cvcamera::closecamera()
{
    if(capture->isOpened()){
        capture->release();
    }else
        return false;
}

void cvcamera::clearqueue()
{
    while (camimgque.size()>10) {
        camimgque.pop();

    }
    cout<<"cleared:  "<<camimgque.size()<<endl;
}

Mat cvcamera::getmCameraImg() const
{
    return m_mCameraImg;
}

void cvcamera::setMCameraImg(const Mat &mCameraImg)
{
    m_mCameraImg = mCameraImg;
}

Mat cvcamera::getlastestimg()
{
    int size=camimgque.size();
    if(size>0){
        return camimgque.back();
    }

}

Mat cvcamera::getLastestmat() const
{
    return lastestmat;
}

int cvcamera::getMax() const
{
    return max;
}

void cvcamera::setMax(int value)
{
    max = value;
}

VideoCapture *cvcamera::getCapture() const
{
    return capture;
}
void cvcamera::loadData()
{
    QFile ExpandData(SAVE_DATA);
    if(ExpandData.open(QIODevice::ReadOnly))
    {
        /*文本输出流，用于保存数据*/
        QTextStream In(&ExpandData);
        In >> m_iCameraId;
        In >>m_iWidth;
        In >>m_iHight;
        In >>m_iFps;
        In >>m_iExposure;
        In >>m_iBrightness;
        In >>m_iContrast;
        In >>m_iHue;
        In >>m_iSaturation;
        ExpandData.close();
    }
}

