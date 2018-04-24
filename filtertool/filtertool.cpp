#include "filtertool.h"



//Filtertool::Filtertool()
//{

//}

Filtertool::Filtertool(QObject *parent)
{

}

Filtertool::Filtertool(int index, int node, int runid, int idofstype)
{


}

Filtertool::Filtertool(int node)
{   
    //setToolparam(index,node,runid,idofstype);
    //imgparamin.setDbParam("inimg",index,node,imagetype,runid);
    imgparamout.setDbParam("outimg",zvdata->getindex(node),node,imagetype,zvdata->getToolcount());
    zvdata->addindex(node);
    zvdata->addtoolcount();
    //imgparamin.setPic(&m_inpic);
    imgparamout.setPic(&m_outpic);
}

ToolsStructure Filtertool::getToolparam() const
{
    return toolparam;
}

void Filtertool::setToolparam(int index, int node, int runid, int idofstype)
{
    toolparam.setallparam(index, node, runid, idofstype);
}

void Filtertool::settool(int type, int high, int low, int stage, int size)
{
    m_ipasstype=type;
    m_ihigh=high;
    m_ilow=low;
    m_istage=stage;
    m_isize=size;
}

void Filtertool::lowblur()
{
    blur(m_inpic,m_outpic,Size(m_isize,m_isize));
}

void Filtertool::bandpassfilter()
{
    bandpass(m_inpic,m_outpic,m_ihigh,m_ilow,m_istage);
}

Filtertool::~Filtertool()
{
    //TODO:删除存入数据库的参数
    zvdata->delparam(&imgparamout.getDbParam());
}


void Filtertool::work()
{

    switch(m_ipasstype){
        case lowpasstype:
            lowblur();
        break;
        case bandpasstype:
            bandpassfilter();
        break;
        default:
        break;
    }

}

void Filtertool::showui()
{
    showed=true;
    FilterDialog *filterdia=new FilterDialog();
    connect(filterdia,SIGNAL(sendrefuse()),this,SLOT(refusecreate()));
    connect(filterdia,SIGNAL(sendconfirm()),this,SLOT(confirmcreat()));
    connect(this,SIGNAL(sendmat(Mat)),filterdia,SLOT(receivemat(Mat)));
    connect(filterdia,SIGNAL(sendstruct(ParamStructure)),this,SLOT(receivestruct(ParamStructure)));
    connect(filterdia,SIGNAL(sendwork(int,int,int,int,int)),
            this,SLOT(receivework(int,int,int,int,int)));
    filterdia->show();
}

bool Filtertool::save(QString str)
{
    return true;
}

bool Filtertool::load(QString str)
{
    return false;
}

bool Filtertool::copyto(toolsbase &toolb)
{
    return true;
}



void Filtertool::connectdb()
{

}

void Filtertool::unconnect()
{

}

void Filtertool::release()
{
    delete this;
}

int Filtertool::getPasstype() const
{
    return m_ipasstype;
}

void Filtertool::setPasstype(int value)
{
    m_ipasstype = value;
}

void Filtertool::refusecreate()
{
    zvdata->minusindex(toolparam.iNode());
    zvdata->minustoolcount();
    release();
}

void Filtertool::confirmcreat()
{
    if(zvdata!=NULL){
        //TODO:保存参数进数据库
        zvdata->saveparam(&imgparamout);
        zvdata->savetool(this);
    }
}

void Filtertool::receivework(int type,int high,int low,int stage,int size)
{
    settool(type,high,low,stage,size);
    cout<<"work save"<<endl;
    work();
    emit sendmat(m_outpic);
}

void Filtertool::receivestruct(ParamStructure structure)
{
    cout<<"receivestruct"<<endl;
    //imgparamin->setDbParam(structure);
    //zvdata->getparam(imgparamin);
    imgparamin=dynamic_cast<ImageParam*>(zvdata->getparamster(structure));
    m_inpic=*imgparamin->pic();
}
