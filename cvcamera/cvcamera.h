/**
*@projectName   cvcamera
*@documentname  cvcamera.h
*@author        zzJun
*@date          20180422
*@brief         the class used to control the camera,as well as save the paramster
**/
#ifndef CVCAMERA_H
#define CVCAMERA_H
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/contrib/contrib.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/video/background_segm.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "cvcamera_global.h"
#include <iostream>
#include <queue>
using namespace cv;
using namespace std;

class CVCAMERASHARED_EXPORT cvcamera
{

public:
    cvcamera();
    ~cvcamera();
    void release();
    //输出Mat
    int refreshCameraImg();
    int queuesize();
    void addcamimg();
    //打开相机
    bool opencamera();
    //设置相机参数
    void setcamera(int id,int width,int hight,int fps,int exposure,int brightness,int constrast,int hub,int saturation);
    //关闭相机
    bool closecamera();
    void clearqueue();
    Mat getmCameraImg() const;
    void setMCameraImg(const Mat &mCameraImg);
    Mat getlastestimg();
    Mat getLastestmat() const;

    int getMax() const;
    void setMax(int value);

private:
    int m_iCameraId=0;//相机的识别码 如“0”（暂定）
    VideoCapture *capture;//VideoCapture
    Mat m_mCameraImg;//输出的Mat
    queue<Mat> camimgque;
    int m_iWidth=-1;//图像宽度
    int m_iHight=-1;//图像高度
    int m_iFps=-1;//图像帧数
    int m_iExposure=-1;//图像曝光值
    int m_iBrightness=-1;//图像亮度
    int m_iContrast=-1;//图像对比度
    int m_iHue=-1;//图像色度
    int m_iSaturation=-1;//图像饱和度
    Mat lastestmat;
    int max;
};
extern "C" CVCAMERASHARED_EXPORT cvcamera *cvcam;
extern QMutex outmutex;

#endif // OPENCVCAMERA_H
