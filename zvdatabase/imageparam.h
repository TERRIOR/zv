#ifndef IMAGEPARAM_H
#define IMAGEPARAM_H

#include "zvbaseparam.h"
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/contrib/contrib.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/core/core_c.h"
using namespace cv;
class ImageParam:public ZvBaseParam
{
public:
    ImageParam(const Mat &pic,string paramname,int index,int node,int stype,int id);
    ImageParam();
    ~ImageParam();
    Mat pic() const;
    void setPic(const Mat &pic);

private:
    Mat m_pic;
};

#endif // IMAGEPARAM_H
