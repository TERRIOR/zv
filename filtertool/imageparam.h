/**
*@projectName
*@documentname  imageparam.h
*@author        zzJun
*@date          20180422
*@brief         img data type used in zvdatabase
**/
#ifndef IMAGEPARAM_H
#define IMAGEPARAM_H

#include "zvbaseparam.h"
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/contrib/contrib.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

using namespace cv;
class ImageParam:public ZvBaseParam
{
public:
    ImageParam(Mat *pic,string paramname,int index,int node,int stype,int id);
    ImageParam();
    ~ImageParam();
    Mat* pic() const;
    void setPic(Mat *pic);

private:
    Mat *m_pic;
};

#endif // IMAGEPARAM_H
