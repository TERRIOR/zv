#include "zvdatabase.h"
//#define ZVDATABASE_LIBRARY

Zvdatabase::Zvdatabase()
{
    cout<<"data base"<<endl;
    zvmap=new map<ParamStructure,ZvBaseParam*>();
}

void Zvdatabase::release()
{
    delete this;
}

bool Zvdatabase::saveparam(ZvBaseParam *param)
{
    std::pair<std::map<ParamStructure,ZvBaseParam*>::iterator, bool> ret;
    ret=zvmap->insert(pair<ParamStructure,ZvBaseParam*>(param->getDbParam(),param));
    return ret.second;
}

void Zvdatabase::refreshparam(ZvBaseParam *param)
{
    zvmap->at(param->getDbParam())=param;
}

bool Zvdatabase::delparam(ParamStructure *params)
{
    map<ParamStructure,ZvBaseParam*>::iterator it;
    it = zvmap->find(*params);
    if (it != zvmap->end())
        zvmap->erase (it); // b被成功删除
    return it != zvmap->end();
}

void Zvdatabase::clearall()
{
    zvmap->clear();
}

bool Zvdatabase::isempty()
{
    return zvmap->empty();
}

void Zvdatabase::getparam(ZvBaseParam *param)
{
    param=zvmap->at(param->getDbParam());
}

Zvdatabase::~Zvdatabase()
{
    delete zvmap;
    zvmap=NULL;
    cout<<"~data base"<<endl;
}


