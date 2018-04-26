#include "camsetdialog.h"
#include "ui_camsetdialog.h"

CamsetDialog::CamsetDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CamsetDialog)
{
    ui->setupUi(this);
    conthreader=new controlthread(true);
    //connect(conthreader,SIGNAL(callui()),this,SLOT(refleshpic()));
    tmrTimer = new QTimer(this);
    connect(tmrTimer,SIGNAL(timeout()),this,SLOT(UpdateGUI()));
    loadData();
    ui->lineEditwid->setText(fromnum(m_iWidth));
    ui->lineEdit_high->setText(fromnum(m_iHight));
    ui->lineEdit_bri->setText(fromnum(m_iBrightness));
    ui->lineEdit_con->setText(fromnum(m_iContrast));
    ui->lineEdit_exp->setText(fromnum(m_iExposure));
    ui->lineEdit_fps->setText(fromnum(m_iFps));
    ui->lineEdit_hue->setText(fromnum(m_iHue));
    ui->lineEdit_sat->setText(fromnum(m_iSaturation));
    ui->id->setText(fromnum(m_iCameraId));

}

CamsetDialog::~CamsetDialog()
{
    delete tmrTimer;
    conthreader->stopthread();
    cvcam->closecamera();
    delete conthreader;
    conthreader=NULL;
    delete ui;
}


void CamsetDialog::on_buttonBox_clicked(QAbstractButton *button)
{
    if(ui->buttonBox->button(QDialogButtonBox::Ok)==button){
       cout<<"ok"<<endl;
       saveData();
       this->close();

    }else if(ui->buttonBox->button(QDialogButtonBox::Cancel)==button){
       cout<<"cancel"<<endl;
       if(cvcam!=NULL)cvcam->setcamera(-1,-1,-1,-1,-1,-1,-1,-1,-1);
       this->close();
    }
}

void CamsetDialog::on_pushButtonstart_clicked()
{
    if(cvcam!=NULL){

        cvcam->setcamera(qtoint(ui->id->text()),qtoint(ui->lineEditwid->text()),qtoint(ui->lineEdit_high->text()),qtoint(ui->lineEdit_fps->text()),qtoint(ui->lineEdit_exp->text()),qtoint(ui->lineEdit_bri->text()),qtoint(ui->lineEdit_con->text()),qtoint(ui->lineEdit_hue->text()),qtoint(ui->lineEdit_sat->text()));
        cvcam->opencamera();
        conthreader->startthread();
    }
    if(tmrTimer->isActive() == false){
        int fps=ui->lineEdit_fps->text().toInt();
        if(fps!=0)
            tmrTimer->start(1000/fps);
        else
            tmrTimer->start(50);
    }
}

void CamsetDialog::on_pushButtonstop_clicked()
{
    if(cvcam!=NULL){
        conthreader->stopthread();
        cvcam->closecamera();
    }
    if(tmrTimer->isActive() == true){
        tmrTimer->stop();
    }
}

void CamsetDialog::refleshpic()
{
    Mat img;
    //cvcam->refreshCameraImg();
    img=cvcam->getLastestmat();
    QImage qimg=Mat2QImage(img);
    ui->lblOriginal->setPixmap(QPixmap::fromImage(qimg));
}

void CamsetDialog::UpdateGUI()
{
    refleshpic();
}

void CamsetDialog::saveData()
{
    QFile ExpandData(SAVE_DATA);
    if(ExpandData.open(QIODevice::WriteOnly))
    {
        /*文本输出流，用于保存数据*/
        QTextStream Out(&ExpandData);
        /*加入空格的好处是以流的形式读取恰好是相反的操作，这样一来方便快速对参数的读取*/
        Out << m_iCameraId;
        Out << ' ';
        Out << cvcam->getCapture()->get(CV_CAP_PROP_FRAME_WIDTH);
        Out << ' ';
        Out << cvcam->getCapture()->get(CV_CAP_PROP_FRAME_HEIGHT);
        Out << ' ';
        Out << cvcam->getCapture()->get(CV_CAP_PROP_FPS);
        Out << ' ';
        Out << cvcam->getCapture()->get(CV_CAP_PROP_BRIGHTNESS);
        Out << ' ';
        Out << cvcam->getCapture()->get(CV_CAP_PROP_CONTRAST);
        Out << ' ';
        Out << cvcam->getCapture()->get(CV_CAP_PROP_SATURATION);
        Out << ' ';
        Out << cvcam->getCapture()->get(CV_CAP_PROP_HUE);
        Out << ' ';
        Out << cvcam->getCapture()->get(CV_CAP_PROP_EXPOSURE);
        ExpandData.close();
    }
}
void CamsetDialog::loadData()
{
    QFile ExpandData(SAVE_DATA);
    if(ExpandData.open(QIODevice::ReadOnly))
    {
        /*文本输出流，用于保存数据*/
        QTextStream In(&ExpandData);
        In >> m_iCameraId;
        In >>m_iWidth;
        In >>m_iHight;
        In >>m_iFps;
        In >>m_iExposure;
        In >>m_iBrightness;
        In >>m_iContrast;
        In >>m_iHue;
        In >>m_iSaturation;
        ExpandData.close();
    }
}
