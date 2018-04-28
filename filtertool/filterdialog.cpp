#include "filterdialog.h"
#include "ui_filterdialog.h"

FilterDialog::FilterDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FilterDialog)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags()|Qt::FramelessWindowHint|Qt::WindowTitleHint);
    btngroup = new QButtonGroup(this);
    btngroup->addButton(ui->radioButtonhigh,0);
    btngroup->addButton(ui->radioButtonlow,1);
    ui->buttonBox->setEnabled(false);
    ui->pushButtonshow->setEnabled(false);
}


FilterDialog::~FilterDialog()
{
    delete ui;
}

void FilterDialog::receivemat(Mat m)
{
    cout<<m.channels()<<" "<<m.type()<<" "<<endl;
    QImage qimg=Mat2QImage(m);
    ui->lblOriginal->setPixmap(QPixmap::fromImage(qimg));
}

void FilterDialog::on_pushButtonselect_clicked()
{
    ui->buttonBox->setEnabled(true);
    ui->pushButtonshow->setEnabled(true);
    QDialog* dia=showdbDialog();
    connect(dia,SIGNAL(sendparam(ParamStructure)),this,SLOT(receiveparam(ParamStructure)));
    dia->show();
}

void FilterDialog::on_pushButtonshow_clicked()
{
    int type;
    int high;
    int low;
    int stage;
    int size;

    if(ui->radioButtonlow->isChecked()){
        type=lowpasstype;
    }else if(ui->radioButtonhigh->isChecked()){
        type=bandpasstype;
    }
    high=ui->lineEdithigh->text().toInt();
    low=ui->lineEditlow->text().toInt();
    stage=ui->lineEditstage->text().toInt();
    size=ui->lineEditsize->text().toInt();
    cout<<"save"<<endl;
    emit sendwork(type,high,low,stage,size);
}

void FilterDialog::on_buttonBox_clicked(QAbstractButton *button)
{
    if(ui->buttonBox->button(QDialogButtonBox::Ok)==button){
        emit sendconfirm();
        this->close();
    }else if(ui->buttonBox->button(QDialogButtonBox::Cancel)==button){
        emit sendrefuse();
        this->close();
    }
}

void FilterDialog::receiveparam(ParamStructure structure)
{
    cout<<"receiveparam"<<endl;
    emit sendstruct(structure);
}

