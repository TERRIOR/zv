#include "zvbaseparam.h"
#include <string>
ZvBaseParam::ZvBaseParam()
{
    m_dbParam.setStructure("-1",-1, -1,-1,-1);
}

ZvBaseParam::ZvBaseParam(string paramname, int index, int node, int stype,int id)
{
    m_dbParam.setStructure(paramname,index, node,stype,id);
}

void ZvBaseParam::setDbParam(string paramname, int index, int node, int stype,int id)
{
    m_dbParam.setStructure(paramname,index, node,stype,id);
}

ZvBaseParam::~ZvBaseParam()
{

}


ParamStructure ZvBaseParam::getDbParam() const
{
    return m_dbParam;
}

