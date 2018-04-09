#ifndef RECTPARAM_H
#define RECTPARAM_H
#include "zvbaseparam.h"
#include "pointparam.h"
class RectParam:public ZvBaseParam
{
public:
    RectParam();
    ~RectParam();
    RectParam(PointParam p1,int x,int y,float angle,int index, int node, string toolname,int id);
    RectParam(PointParam p1,int x,int y,float angle);
    PointParam pointleftup() const;
    void setPointleftup(const PointParam &pointleftup);

    int iWidth() const;
    void setIWidth(int iWidth);

    int iHight() const;
    void setIHight(int iHight);

    float fangle() const;
    void setFangle(float fangle);

private:
    PointParam m_pointleftup;
    int m_iWidth;
    int m_iHight;
    float m_fangle;
};

#endif // RECTPARAM_H
