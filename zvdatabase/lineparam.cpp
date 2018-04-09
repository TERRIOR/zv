#include "lineparam.h"

LineParam::LineParam()
{
    setDbParam("-1",-1,-1,1,-1);
}

LineParam::~LineParam()
{

}

LineParam::LineParam(PointParam p1, PointParam p2,int index,int node,string paramname,int id)
{
    m_p1=p1;
    m_p2=p2;
    m_fangle=-1;
    m_fdis=-1;
    setDbParam(paramname,index,node,1,id);
    m_p1.setDbParam(paramname+"p1",index,node,0,id);
    m_p2.setDbParam(paramname+"p2",index,node,0,id);
}
LineParam::LineParam(PointParam p1, PointParam p2)
{
    m_p1=p1;
    m_p2=p2;
    m_fangle=-1;
    m_fdis=-1;
    setDbParam("-1",-1,-1,1,-1);
}

LineParam::LineParam(PointParam p1, float angle, float dis)
{
    m_p1=p1;
    m_p2.setIx(p1.ix()+dis*cos(angle));
    m_p2.setIy(p1.iy()+dis*sin(angle));
    setDbParam("-1",-1,-1,1,-1);
}

PointParam LineParam::p1() const
{
    return m_p1;
}

void LineParam::setP1(const PointParam &p1)
{
    m_p1 = p1;
}

PointParam LineParam::p2() const
{
    return m_p2;
}

void LineParam::setP2(const PointParam &p2)
{
    m_p2 = p2;
}

float LineParam::fangle()
{
    m_fangle=atan( (m_p1.iy()-m_p2.iy())/(m_p1.ix()-m_p2.ix()) );
    return m_fangle;
}

float LineParam::fdis()
{
    m_fdis=sqrt((m_p1.iy()-m_p2.iy())*(m_p1.iy()-m_p2.iy())
                +(m_p1.ix()-m_p2.ix())*(m_p1.ix()-m_p2.ix()));
    return m_fdis;
}

void LineParam::setdbparam(string paramname, int index, int node, int stype,int id)
{

    setDbParam(paramname,index,node,1,id);
    m_p1.setDbParam(paramname+"p1",index,node,0,id);
    m_p2.setDbParam(paramname+"p2",index,node,0,id);
}


