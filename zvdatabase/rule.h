#ifndef RULE_H
#define RULE_H
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/contrib/contrib.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/video/background_segm.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "math.h"
#include <iostream>
#include <qdebug.h>
#define PI 3.1415926
#define FILTER_N 3
using namespace std;
using namespace cv;
class rule{
public:
    rule();
    ~rule();
    rule(Point p1,Point p2,const Mat &img,int width);
    void caledealmat(Point p1,Point p2,const Mat &img,int width);//计算出待处理区域的mat
    void calgrayhis();//根据mat算出沿位置分布的灰度xy函数
    void calgradhis();//根据mat算出沿位置分布的灰度梯度xy函数
    void calgray();//计算灰度数组
    void calhis();//同时计算数组，没滤波
    void calgrad();//计算梯度数组
    Point calpoint(int x, int length);
    void imrotate(const Mat& img, Mat& newIm, double angle,Point2f pt);
    Point pointResult() const;
    void setPointResult(const Point &pointResult);
    Point PointEnd() const;
    void setPointEnd(const Point &PointEnd);
    Point pointStart() const;
    void setPointStart(const Point &pointStart);
    void filter(int *func,int size,int num);
    void showHistogram();
    int *getGrayHistogram() const;
    void setGrayHistogram(int *value);

    int *getGradientHis() const;
    void setGradientHis(int *value);

    Mat getDealmat() const;
    void setDealmat(const Mat &value);

    double getAngle() const;
    void setAngle(double value);

    Mat *getGrayhisMat() const;
    void setGrayhisMat(Mat *value);

    Mat *getGradhisMat() const;
    void setGradhisMat(Mat *value);

    int getMax() const;
    void setMax(int value);

    int getMin() const;
    void setMin(int value);

    void calminmax();
    void calminmax(int zero_up, int zero_down);

    int getMinxa() const;
    void setMinxa(int value);

    int getMinxb() const;
    void setMinxb(int value);

    int getMaxxc() const;
    void setMaxxc(int value);

    int getMaxxd() const;
    void setMaxxd(int value);

    int getGrayhislength() const;
    void setGrayhislength(int value);

    int getGradhislength() const;
    void setGradhislength(int value);

    int getMaxindex() const;
    void setMaxindex(int value);

    int getMinindex() const;
    void setMinindex(int value);

private:
    bool binver=false;
    Mat dealmat;
    int m_width;
    double angle;
    int max=0,min=0;
    int maxindex=0,minindex=0;
    Point m_pointStart;//开始的坐标
    Point m_PointEnd;//结束的坐标
    Point m_pointResult;//边界结果的坐标
    int *GrayHistogram=NULL;//灰度的柱状图
    Mat *GrayhisMat=NULL;//灰度的显示mat
    int *GradientHis=NULL;//梯度柱状图
    Mat *GradhisMat=NULL;//梯度的显示mat
    int minxa,minxb,maxxc,maxxd;
    int grayhislength;
    int gradhislength;
};
void circleLeastFit(const std::vector<cv::Point> points, cv::Point &center, double &radius);
#endif // RULE_H
