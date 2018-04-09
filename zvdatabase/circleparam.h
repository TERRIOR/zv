#ifndef CIRCLEPARAM_H
#define CIRCLEPARAM_H
#include "zvbaseparam.h"
#include "pointparam.h"
class CircleParam :public ZvBaseParam
{
public:
    CircleParam();
    ~CircleParam();
    CircleParam(PointParam p1,int r);
    CircleParam(PointParam p1,int r,int index,int node,string toolname,int id);
    PointParam pointCenter() const;
    void setPointCenter(const PointParam &pointCenter);

    int iradio() const;
    void setIradio(int iradio);
private:
    int m_iradio;
    PointParam m_pointCenter;
};

#endif // IMAGEPARAM_H
