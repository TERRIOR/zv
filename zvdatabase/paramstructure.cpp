#include "paramstructure.h"

ParamStructure::ParamStructure()
{

}

ParamStructure::ParamStructure(string paramname, int index, int node, int stype,int id)
    : sparamName(paramname),iIndex(index),iNode(node),istype(stype),iId(id)
{

}

void ParamStructure::setStructure(string paramname, int index, int node, int stype,int id)
{
    sparamName=paramname;
    iIndex=index;
    iNode=node;
    istype=stype;
    iId=id;
}

string ParamStructure::getSparamName() const
{
    return sparamName;
}

void ParamStructure::setSparamName(const string &value)
{
    sparamName = value;
}

int ParamStructure::getIstype() const
{
    return istype;
}

void ParamStructure::setIstype(int value)
{
    istype = value;
}

int ParamStructure::getINode() const
{
    return iNode;
}

void ParamStructure::setINode(int value)
{
    iNode = value;
}

int ParamStructure::getIIndex() const
{
    return iIndex;
}

void ParamStructure::setIIndex(int value)
{
    iIndex = value;
}

int ParamStructure::getIId() const
{
    return iId;
}

void ParamStructure::setIId(int value)
{
    iId = value;
}

bool ParamStructure::operator<(const ParamStructure &Param) const
{
    if(iId==Param.getIId()){
        if(sparamName==Param.getSparamName()){
            if(istype==Param.getIstype()){
                return true;
            }else{
                return istype>Param.getIstype();
            }
        }else{
            return sparamName>Param.getSparamName();
        }
    }else{
        return iId>Param.getIId();
    }
}
