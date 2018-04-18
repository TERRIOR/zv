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
}

CamsetDialog::~CamsetDialog()
{
    delete tmrTimer;
    conthreader->stopthread();
    delete conthreader;
    conthreader=NULL;
    delete ui;
}


void CamsetDialog::on_buttonBox_clicked(QAbstractButton *button)
{
    if(ui->buttonBox->button(QDialogButtonBox::Ok)==button){
       cout<<"ok"<<endl;
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
