#include "filtertool.h"


Filtertool::Filtertool()
{
    //do nothing
}

Filtertool::Filtertool(int node)
{   
    //设置创建 自动获取参数
    //设置工具的参数
    //更新数据库的计数
    zvdata->addindex(node);
    zvdata->addtoolcount();
    setToolparam(zvdata->getindex(node),node,zvdata->getToolcount(),filtertooltype);
    //TODO:把需要输出的成员与数据类的数据结构绑定 此处为滤波后的图像
    imgparamout.setDbParam("outimg",zvdata->getindex(node),node,imagetype,zvdata->getToolcount());
    imgparamout.setPic(&m_outpic);
}

Filtertool::Filtertool(int index,int node,int id)
{
    //读取创建 按照保存文件设置参数
    //设置工具的参数
    setToolparam(index,node,id,filtertooltype);
    //更新数据库的计数
    zvdata->setindex(node,index);
    zvdata->setToolcount(id);
    //TODO:把需要输出的参数与数据库绑定
    imgparamout.setDbParam("outimg",index,node,imagetype,id);
    imgparamout.setPic(&m_outpic);
}
void Filtertool::getToolparam(ToolsStructure& toolstruct)
{
    toolstruct=toolparam;
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

bool Filtertool::lowblur()
{
    blur(m_inpic,m_outpic,Size(m_isize,m_isize));
    return true;
}

bool Filtertool::bandpassfilter()
{
    Mat gray;
    cvtColor(m_inpic,gray,CV_BGR2GRAY);

    bandpass(gray,m_outpic,m_ihigh,m_ilow,m_istage);
    return true;
}

Filtertool::~Filtertool()
{
    //TODO:删除存入数据库的参数
    zvdata->delparam(&imgparamout.getDbParam());
}


bool Filtertool::work()
{
    //TODO:次数添加图像处理的运算
    imgparamin->pic()->copyTo(m_inpic);
    if(!m_inpic.empty()){
        switch(m_ipasstype){
            case lowpasstype:
                worksuccess=lowblur();
            break;
            case bandpasstype:
                worksuccess=bandpassfilter();
            break;
            default:
            break;
        }
        return worksuccess;
    }
    return false;

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

bool Filtertool::savetool(QTextStream &Out)
{
    Out<<toolparam.iIdOfStype();
    Out<<' ';
    Out<<toolparam.iIndex();
    Out<<' ';
    Out<<toolparam.iNode();
    Out<<' ';
    Out<<toolparam.iRunId();
    Out<<' ';
    return true;
}

bool Filtertool::loadtool(QTextStream &In)
{
    int id;
    int index;
    int node;

    In>>index;
    In>>node;
    In>>id;
    //读取创建 按照保存文件设置参数
    //设置工具的参数
    setToolparam(index,node,id,filtertooltype);
    //更新数据库的计数
    zvdata->setindex(node,index);
    zvdata->setToolcount(id);
    //TODO:把需要输出的参数与数据库绑定
    imgparamout.setDbParam("outimg",index,node,imagetype,id);
    imgparamout.setPic(&m_outpic);
    return true;
}
bool Filtertool::save(QTextStream &Out)
{
    //TODO:此处保存运算参数
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
    //TODO:此处读取运算数据
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
        //TODO:保存输出参数进数据库 确认创建

        zvdata->saveparam(&imgparamout);
        zvdata->savetool(this);
        emit sendconfirm();
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

bool Filtertool::getWorksuccess() const
{
    return worksuccess;
}
