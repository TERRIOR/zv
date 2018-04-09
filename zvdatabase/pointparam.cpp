#include "pointparam.h"

PointParam::PointParam()
{
    setDbParam("-1",-1,-1,0,-1);
}

PointParam::~PointParam()
{

}

PointParam::PointParam(int x, int y)
{
    //可作为中间变量，则不需要信息
    m_ix=x;
    m_iy=y;
    setDbParam("-1",-1,-1,0-1);
}

PointParam::PointParam(int x, int y,int index,int node,string paramname,int id)
{
    m_ix=x;
    m_iy=y;
    //当数据是重要数据，在工具调用时出入数据信息。
    setDbParam(paramname,index,node,0,id);
}

int PointParam::ix() const
{
    return m_ix;
}

void PointParam::setIx(int ix)
{
    m_ix = ix;
}

int PointParam::iy() const
{
    return m_iy;
}

void PointParam::setIy(int iy)
{
    m_iy = iy;
}
