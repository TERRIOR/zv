#include "resultparam.h"

resultparam::resultparam()
{

}

resultparam::resultparam(int res, string paramname, int index, int node, int stype, int id)
{
    setDbParam(paramname,index,node,5,id);
    iresult=res;
}

resultparam::~resultparam()
{

}

int resultparam::getIresult() const
{
    return iresult;
}

void resultparam::setIresult(int value)
{
    iresult = value;
}

int resultparam::getOffsetx() const
{
    return offsetx;
}

void resultparam::setOffsetx(int value)
{
    offsetx = value;
}

int resultparam::getOffsety() const
{
    return offsety;
}

void resultparam::setOffsety(int value)
{
    offsety = value;
}

float resultparam::getOffsetang() const
{
    return offsetang;
}

void resultparam::setOffsetang(float value)
{
    offsetang = value;
}

int resultparam::getBresult() const
{
    return bresult;
}

void resultparam::setBresult(int value)
{
    bresult = value;
}
