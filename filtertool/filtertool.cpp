#include "filtertool.h"



//Filtertool::Filtertool()
//{

//}

Filtertool::Filtertool(QObject *parent)
{

}

Filtertool::Filtertool(int node)
{   
    imgparamout.setDbParam("outimg",zvdata->getindex(node),node,imagetype,zvdata->getToolcount());
    setToolparam(zvdata->getindex(node),node,imagetype,zvdata->getToolcount());
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
    Mat gray;
    cvtColor(m_inpic,gray,CV_BGR2GRAY);
    bandpass(gray,m_outpic,m_ihigh,m_ilow,m_istage);
}

Filtertool::~Filtertool()
{
    //TODO:删除存入数据库的参数
    zvdata->delparam(&imgparamout.getDbParam());
}


void Filtertool::work()
{
    //TODO:次数添加图像处理的运算
    imgparamin->pic()->copyTo(m_inpic);
    if(!m_inpic.empty()){
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


}

void Filtertool::showui()
{
    //TODO:此处添加界面的创建，显示，绑定
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

bool Filtertool::save(QTextStream &Out)
{
    //TODO:此处保存参数
    //QTextStream Out(Datafile);
    Out<<m_ipasstype;
    Out<<' ';
    Out<<m_ihigh;
    Out<<' ';
    Out<<m_ilow;
    Out<<' ';
    Out<<m_istage;
    Out<<' ';
    Out<<m_isize;
    Out<<' ';
    Out<<imgparamin->getDbParam().getIId();
    Out<<' ';
    Out<<imgparamin->getDbParam().getIIndex();
    Out<<' ';
    Out<<imgparamin->getDbParam().getINode();
    Out<<' ';
    Out<<imgparamin->getDbParam().getIstype();
    Out<<' ';
    Out<<fromstdstring(imgparamin->getDbParam().getSparamName());
    Out<<' ';
    return true;
}

bool Filtertool::load(QTextStream &In)
{
    //TODO:此处读取数据
    int id;
    int index;
    int node;
    int type;
    QString name;
    In>>m_ipasstype;
    In>>m_ihigh;
    In>>m_ilow;
    In>>m_istage;
    In>>m_isize;
    In>>id;
    In>>index;
    In>>node;
    In>>type;
    In>>name;
    //pos=*In.pos();
    imgparamin=dynamic_cast<ImageParam*>(
                zvdata->getparamster(
                    ParamStructure(name.toStdString(),index,node,type,id)));
    imgparamin->pic()->copyTo(m_inpic);

    cout<<"load"<<endl;
    return true;
}

bool Filtertool::copyto(toolsbase &toolb)
{
    //TODO:添加复制代码
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

void Filtertool::creatconfirm()
{
    if(zvdata!=NULL){
        //TODO:保存参数进数据库
        zvdata->saveparam(&imgparamout);
        zvdata->savetool(this);
    }
}

void Filtertool::refusecreate()
{
    if(zvdata!=NULL){
        zvdata->minusindex(toolparam.iNode());
        zvdata->minustoolcount();
    }
    release();
}

void Filtertool::confirmcreat()
{
    creatconfirm();
}

void Filtertool::receivework(int type,int high,int low,int stage,int size)
{
    settool(type,high,low,stage,size);
    work();
    emit sendmat(m_outpic);
}

void Filtertool::receivestruct(ParamStructure structure)
{

    imgparamin=dynamic_cast<ImageParam*>(zvdata->getparamster(structure));
    imgparamin->pic()->copyTo(m_inpic);
}
