#include "imageparam.h"

ImageParam::ImageParam(Mat *pic, string paramname, int index, int node, int stype,int id)

{
    m_pic=pic;
    setDbParam(paramname,index,node,4,id);
}

ImageParam::ImageParam()
{

}

ImageParam::~ImageParam()
{

}

Mat* ImageParam::pic() const
{
    return m_pic;
}

void ImageParam::setPic(Mat *pic)
{
    m_pic = pic;
}
