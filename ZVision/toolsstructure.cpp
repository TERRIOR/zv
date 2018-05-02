#include "toolsstructure.h"

ToolsStructure::ToolsStructure()
{

}

ToolsStructure::ToolsStructure(int index, int node, int runid, int idofstype)
    :m_iIndex(index),m_iNode(node),m_iRunId(runid),m_iIdOfStype(idofstype)
{

}

void ToolsStructure::setallparam(int index, int node, int runid, int idofstype)
{
    m_iIndex=index;
    m_iNode=node;
    m_iRunId=runid;
    m_iIdOfStype=idofstype;
}

void ToolsStructure::getallparam(int *param)
{
    param[0]=m_iIndex;
    param[1]=m_iNode;
    param[2]=m_iRunId;
    param[3]=m_iIdOfStype;
}

int ToolsStructure::iNode() const
{
    return m_iNode;
}

void ToolsStructure::setINode(int iNode)
{
    m_iNode = iNode;
}

int ToolsStructure::iIndex() const
{
    return m_iIndex;
}

void ToolsStructure::setIIndex(int iIndex)
{
    m_iIndex = iIndex;
}

int ToolsStructure::iRunId() const
{
    return m_iRunId;
}

void ToolsStructure::setIRunId(int iRunId)
{
    m_iRunId = iRunId;
}

int ToolsStructure::iIdOfStype() const
{
    return m_iIdOfStype;
}

void ToolsStructure::setIIdOfStype(int iIdOfStype)
{
    m_iIdOfStype = iIdOfStype;
}

bool ToolsStructure::operator<(const ToolsStructure &ts) const
{
    if(m_iRunId==ts.iRunId()){
        return false;
    }else{
        return m_iRunId<ts.iRunId();
    }
}


