#include "rectparam.h"

RectParam::RectParam()
{
    setDbParam("-1",-1,-1,3,-1);
}

RectParam::~RectParam()
{

}

RectParam::RectParam(PointParam p1, int x, int y, float angle,int index, int node, string paramname,int id)
{
    m_pointleftup=p1;
    m_iWidth=x;
    m_iHight=y;
    m_fangle=angle;
    setDbParam(paramname,index,node,3,id);
}

RectParam::RectParam(PointParam p1, int x, int y,float angle)
{
    m_pointleftup=p1;
    m_iWidth=x;
    m_iHight=y;
    m_fangle=angle;
    setDbParam("-1",-1,-1,3,-1);
}

PointParam RectParam::pointleftup() const
{
    return m_pointleftup;
}

void RectParam::setPointleftup(const PointParam &pointleftup)
{
    m_pointleftup = pointleftup;
}

int RectParam::iWidth() const
{
    return m_iWidth;
}

void RectParam::setIWidth(int iWidth)
{
    m_iWidth = iWidth;
}

int RectParam::iHight() const
{
    return m_iHight;
}

void RectParam::setIHight(int iHight)
{
    m_iHight = iHight;
}

float RectParam::fangle() const
{
    return m_fangle;
}

void RectParam::setFangle(float fangle)
{
    m_fangle = fangle;
}
