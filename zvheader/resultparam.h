#ifndef RESULTPARAM_H
#define RESULTPARAM_H
#include "zvdatabase.h"

class resultparam:public ZvBaseParam
{
public:
    resultparam();
    resultparam(int res,string paramname,int index,int node,int stype,int id);
    ~resultparam();
    int getIresult() const;
    void setIresult(int value);

    int getOffsetx() const;
    void setOffsetx(int value);

    int getOffsety() const;
    void setOffsety(int value);

    float getOffsetang() const;
    void setOffsetang(float value);

    int getBresult() const;
    void setBresult(int value);

private:
    int iresult;//数值类型的结果值
    int offsetx;//偏移量x
    int offsety;//偏移量y
    float offsetang;//偏移量角度
    int bresult;//分类 如：判断NG或OK 或其他不同类型。

};

#endif // RESULTPARAM_H
