#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtCore>
#include <QtGui>
#include <iostream>
#include <qdebug.h>
using namespace std;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_move = false;
    initform();
    tmrTimer = new QTimer(this);
    connect(tmrTimer,SIGNAL(timeout()),this,SLOT(UpdateGUI()));
    creatzvdata();
    m_zvdata=getzvdata();
    imgcamp=new ImageParam(&imgcam,"cam",0,m_zvdata->getindex(0),imagetype,m_zvdata->getToolcount());
    m_zvdata->addindex(0);
    m_zvdata->addtoolcount();
    m_zvdata->saveparam(imgcamp);
    creatcvcam();
    cvcam->setMax(maxpic);
}

MainWindow::~MainWindow()
{
    imgthread->release();
    imgthread=NULL;
    conthread->release();
    conthread=NULL;
    delete tmrTimer;
    tmrTimer=NULL;
    delete imgcamp;
    imgcamp=NULL;
    delete m_zvdata;
    m_zvdata=NULL;
    delete ui;

}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    //当鼠标左键点击时.
    if (event->button() == Qt::LeftButton)
    {
        m_move = true;
        //记录鼠标的世界坐标.
        m_startPoint = event->globalPos();
        //记录窗体的世界坐标.
        m_windowPoint = this->frameGeometry().topLeft();
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton&&(!max))
    {
        //移动中的鼠标位置相对于初始位置的相对位置.
        QPoint relativePos = event->globalPos() - m_startPoint;
        //然后移动窗体即可.
        this->move(m_windowPoint + relativePos );
    }
}
void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        //改变移动状态.
        m_move = false;
    }
}
void MainWindow::on_pushButton_min_clicked()
{
    showMinimized();
}

void MainWindow::on_pushButton_max_clicked()
{
    if (max) {
        this->setGeometry(location);
        this->setProperty("canMove", true);
    } else {
        location = this->geometry();
        //ui->centralWidget->showFullScreen();
        this->setGeometry(QApplication::desktop()->availableGeometry());
        this->setProperty("canMove", false);
    }

    max = !max;
}

void MainWindow::on_pushButton_close_clicked()
{
    close();
}

void MainWindow::initform()
{
    this->location = this->geometry();
    this->setProperty("form", true);
    this->setProperty("canMove", true);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinMaxButtonsHint);
    ui->mainToolBar->hide();
    QString qssFile=":/qss/flatwhite.css";
    QFile file(qssFile);
    if (file.open(QFile::ReadOnly)) {
        QString qss = file.readAll();
        QString paletteColor = qss.mid(20, 7);
        this->setPalette(QPalette(QColor(paletteColor)));
        this->setStyleSheet(qss);
        file.close();
    }
    ui->tableWidgettool->setColumnCount(3);
    QStringList header;
    header<<tr("Name")<<tr("Index")<<tr("Id");
    ui->tableWidgettool->setHorizontalHeaderLabels(header);
    ui->tableWidgettool->horizontalHeader()->setDefaultSectionSize(220/3);
    ui->tableWidgettool->setFrameShape(QFrame::NoFrame); //设置无边框
    ui->tableWidgettool->setShowGrid(true); //显示格子线
    ui->tableWidgettool->verticalHeader()->setVisible(false); //设置垂直头不可见
    ui->tableWidgettool->setSelectionMode(QAbstractItemView::ExtendedSelection);
    ui->tableWidgettool->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //ui->tableWidgettool->horizontalHeader()->setStretchLastSection(true); //设置充满表宽度
    showMaximized();
}
void MainWindow::setIcon(QAbstractButton *btn, QChar c, quint32 size)
{
    QFont iconFont;
    iconFont.setPointSize(size);
    btn->setFont(iconFont);
    btn->setText(c);
}

void MainWindow::on_pushButton_setcam_clicked()
{
    showcamDialog();
}
void MainWindow::UpdateGUI()
{
    //更新显示
    //refreshmat();//test
    Mat temp;
    if(imgshow!=NULL&&!imgshow->empty()){//先判断指针
        imgshow->copyTo(temp);
        if(!temp.empty()){
            float scale;
            int matrows=temp.rows;
            int lablerows=ui->lblOriginal->height();
            scale=(float)lablerows/matrows;
            scalemat(temp,scale);
            QImage qimg=Mat2QImage(temp);
            ui->lblOriginal->setPixmap(QPixmap::fromImage(qimg));
        }

    }

}
void MainWindow::on_comboBoxnode_currentIndexChanged(int index)
{
    //node0是信号源
    m_inodenow=index+1;
    cout<<m_inodenow<<endl;
    //TODO:更新工具列表的显示
    //ui->tableWidgettool->clear();
    ui->tableWidgettool->clearContents();
    ui->tableWidgettool->setRowCount(0);
    int size=m_zvdata->getToolvectsize();
    int i;
    //first save the num of tools
    for(i=0;i<size;i++){
        ToolsStructure toolstruct;
        toolsbase* tool=m_zvdata->gettool(i);
        tool->getToolparam(toolstruct);
        if(toolstruct.iNode()==m_inodenow){
            addrow(toolstruct);
        }
    }
}
void MainWindow::opencam(){

    if(!cvcam->opencamed()){
        cvcam->opencamera();
        conthread=creatimgthread();
        conthread->startthread();

    }
}

void MainWindow::refreshmat()
{
    //更新从相机获取的画面 需要加锁
    cvcam->refreshCameraImg();
    //当缓冲小于最大值的一半，说明图像处理的速度比读取快，可以获取队列的最早图像
    //当大于一半时，图像算法慢，需要优化，取最新的图像处理，会有失真
    if(cvcam->queuesize()<maxpic/2){
        imgcam=cvcam->getmCameraImg();
    }else{
        imgcam=cvcam->getlastestimg();
        cout<<"over load"<<endl;
    }

}
void MainWindow::closecam(){
    if(cvcam->opencamed()){
        imgthread->stopthread();
        imgthread->release();
        conthread->stopthread();
        conthread->release();
        cvcam->closecamera();
    }
}


void MainWindow::on_pushButtoncamclose_clicked()
{
    closecam();

}

void MainWindow::on_pushButton_pic_clicked()
{
    //更新一次
    opencam();
    UpdateGUI();
}


void MainWindow::loadtool(QTextStream &in)
{
    int type;
    in>>type;
    toolsbase* tool;
    switch (type) {
    case 0:
        tool=CreatFilterTool();
        break;
    case 1:
        //TODO:creat...tool
        //such as tool=CreatFilterTool();

        break;

    default:
        break;
    }
    tool->loadtool(in);
    tool->creatconfirm();
    tool->load(in);
}
void MainWindow::on_pushButton_load_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this,
            tr("Load"),"",tr("*.zv")); //选择路径
    cout<<filename.toStdString()<<endl;
    QFile ExpandData(filename);
    if(ExpandData.open(QIODevice::ReadWrite))
    {
        /*文本输出流，用于保存数据*/
        int i;
        int size;
        QTextStream in(&ExpandData);
        in>>size;
        for(i=0;i<size;i++){
            loadtool(in);
        }
        ExpandData.close();
    }
}

void MainWindow::on_pushButton_save_clicked()
{
    QString filename = QFileDialog::getSaveFileName(this,
            tr("Save"),"",tr("*.zv")); //选择路径
    QFile ExpandData(filename);
    if(ExpandData.open(QIODevice::WriteOnly))
    {
        /*文本输出流，用于保存数据*/
        QTextStream out(&ExpandData);
        int i;
        int size=m_zvdata->getToolvectsize();
        //first save the num of tools
        out<<size;
        out<<' ';
        for(i=0;i<size;i++){
            toolsbase* tool=m_zvdata->gettool(i);
            tool->savetool(out);
            tool->save(out);
        }
        ExpandData.close();
    }
}

void MainWindow::on_pushButton_clicked()
{
    QDialog* dia=showdbDialog();
    connect(dia,SIGNAL(sendparam(ParamStructure)),this,SLOT(receiveparam(ParamStructure)));
    dia->show();
}
void MainWindow::receiveparam(ParamStructure Structure)
{
    ImageParam *imgparam1=dynamic_cast<ImageParam*>(m_zvdata->getparamster(Structure)) ;
    imgshow=imgparam1->pic();
    //imshow("result",*imgparam1->pic());
}

void MainWindow::signalset(int where, int how)
{
    m_iwhere=where;
    m_ihow=how;
}

void MainWindow::on_pushButton_signal_clicked()
{
    QDialog* diasignal=new Dialogsignal();
    connect(diasignal,SIGNAL(sendsignalset(int,int)),this,SLOT(signalset(int, int)));
    diasignal->show();
}

void MainWindow::on_pushButton_node_clicked()
{
    ui->comboBoxnode->addItem(fromnum(m_inodecount));
    m_inodecount++;
}

void MainWindow::addrow(ToolsStructure structure){
    int row_count = ui->tableWidgettool->rowCount(); //获取表单行数
    ui->tableWidgettool->insertRow(row_count); //插入新行
    QTableWidgetItem *item = new QTableWidgetItem();
    QTableWidgetItem *item1 = new QTableWidgetItem();
    QTableWidgetItem *item2 = new QTableWidgetItem();

    //设置对应的图标、文件名称、最后更新时间、对应的类型、文件大小
    item->setText(QString::fromStdString(strzu[structure.iIdOfStype()]));
    item2->setText(QString::number(structure.iRunId())); //type为调用系统的类型，以后缀来区分
    item1->setText(QString::number(structure.iIndex()));
    ui->tableWidgettool->setItem(row_count, 0, item);
    ui->tableWidgettool->setItem(row_count, 1, item1);
    ui->tableWidgettool->setItem(row_count, 2, item2);

    //设置样式为灰色

}





void MainWindow::on_pushButton_run_toggled(bool checked)
{

    if(checked){
        //打开定时器定时更新
        opencam();
        cvcam->clearqueue();
        if(m_ihow==0&&imgthread==NULL){
            imgthread=new controlimgthread();
            imgthread->startthread();
            ui->pushButton_run->setText(QString::fromLocal8Bit("运行中"));
        }
        if(tmrTimer->isActive() == false){
            tmrTimer->start(50);
        }
    }else{
        closecam();
        if(imgthread!=NULL){
            imgthread->release();
            imgthread=NULL;
            ui->pushButton_run->setText(QString::fromLocal8Bit("开始运行"));
        }
        if(tmrTimer->isActive() == true){
            tmrTimer->stop();
        }
    }


}
