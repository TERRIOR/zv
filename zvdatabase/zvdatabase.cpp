#include "zvdatabase.h"
//#define ZVDATABASE_LIBRARY
//dll接口 以c形式创建对象，返回对象（唯一）
Zvdatabase *zvdata=NULL;
Zvdatabase::Zvdatabase()
{
    cout<<"data base"<<endl;
    memset(indexcount, 0, 10);
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

void Zvdatabase::savetool(toolsbase *toolb)
{
//    toolcount++;
    toolvect.push_back(toolb);
}

void  Zvdatabase::deltool()
{
//    toolcount--;
    toolvect.pop_back();
}

void Zvdatabase::releasetool()
{
    vector<toolsbase*>::iterator it=toolvect.begin();
    while (it!=toolvect.end()) {
        (*it)->release();
        it++;
    }
}

int Zvdatabase::getindex(int node)
{
    return indexcount[node];
}

void Zvdatabase::addindex(int node)
{
    int temp=indexcount[node];
    temp++;
    indexcount[node]=temp;
}

void Zvdatabase::minusindex(int node)
{
    cout<<node<<endl;
    int temp=indexcount[node];
    temp--;
    indexcount[node]=temp;
}

void Zvdatabase::setindex(int node, int index)
{
    indexcount[node]=index;
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

void Zvdatabase::clearallvec()
{
    toolvect.clear();
}

bool Zvdatabase::isempty()
{
    return zvmap->empty();
}

void Zvdatabase::getparam(ZvBaseParam *param)
{
    param=zvmap->at(param->getDbParam());
}

ZvBaseParam *Zvdatabase::getparamster(ParamStructure Structure)
{
    return zvmap->at(Structure);
}

map<ParamStructure, ZvBaseParam *> *Zvdatabase::getZvmap() const
{
    return zvmap;
}

int Zvdatabase::getToolvectsize() const
{
    return toolvect.size();
}

toolsbase *Zvdatabase::gettool(int i)
{
    return toolvect[i];
}

int Zvdatabase::getToolcount() const
{
    return toolcount;
}

void Zvdatabase::setToolcount(int value)
{
    toolcount = value;
}

void Zvdatabase::addtoolcount()
{
    toolcount++;
}

void Zvdatabase::minustoolcount()
{
    toolcount--;
}



Zvdatabase::~Zvdatabase()
{
    releasetool();
    clearall();
    clearallvec();
    delete zvmap;
    zvmap=NULL;
    cout<<"~data base"<<endl;
}


