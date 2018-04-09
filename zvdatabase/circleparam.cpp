#include "circleparam.h"

CircleParam::CircleParam()
{
    setDbParam("-1",-1,-1,2,-1);
}

CircleParam::~CircleParam()
{

}

CircleParam::CircleParam(PointParam p1, int r)
{
    m_pointCenter=p1; 
    m_iradio=r;
}

CircleParam::CircleParam(PointParam p1, int r, int index, int node, string paramname,int id)
{
    m_pointCenter=p1;
    m_iradio=r;
    /*
    setIStype(2);//circle
    setIIndex(index);
    setINode(node);
    setSParamName(paramname);
    */
    this->setDbParam(paramname,index,node,2,id);
    m_pointCenter.setDbParam(paramname+"center",index,node,0,id);
}

PointParam CircleParam::pointCenter() const
{
    return m_pointCenter;
}

void CircleParam::setPointCenter(const PointParam &pointCenter)
{
    m_pointCenter = pointCenter;
}

int CircleParam::iradio() const
{
    return m_iradio;
}

void CircleParam::setIradio(int iradio)
{
    m_iradio = iradio;
}
