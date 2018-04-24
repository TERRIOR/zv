#ifndef LINEPARAM_H
#define LINEPARAM_H
#include "zvbaseparam.h"
#include "pointparam.h"
#include "math.h"
class LineParam:public ZvBaseParam
{
public:
    LineParam();
    ~LineParam();
    LineParam(PointParam p1,PointParam p2);
    LineParam(PointParam p1,float angle,float dis);
    LineParam(PointParam p1, PointParam p2, int index, int node, string toolname,int id);
    PointParam p1() const;
    void setP1(const PointParam &p1);
    PointParam p2() const;
    void setP2(const PointParam &p2);
    float fangle() ;
    float fdis() ;
    void setdbparam(string paramname,int index,int node,int stype=1,int id=-1);
private:
    PointParam m_p1;
    PointParam m_p2;
    float m_fangle;
    float m_fdis;
};

#endif // LINEPARAM_H
