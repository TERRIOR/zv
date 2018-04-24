#ifndef POINTPARAM_H
#define POINTPARAM_H
#include "zvbaseparam.h"

class PointParam:public ZvBaseParam
{
public:
    PointParam();
    ~PointParam();
    PointParam(int x,int y);
    PointParam(int x, int y,int index,int node,string toolname,int id);
    int ix() const;
    void setIx(int ix);

    int iy() const;
    void setIy(int iy);

private:
    int m_ix;
    int m_iy;

};

#endif // POINTPARAM_H
