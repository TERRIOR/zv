#include "dialogsignal.h"
#include "ui_dialogsignal.h"

Dialogsignal::Dialogsignal(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialogsignal)
{
    ui->setupUi(this);
    initform();
    btngroup1 = new QButtonGroup(this);
    btngroup1->addButton(ui->radioButton_cam,0);
    btngroup1->addButton(ui->radioButton_file,1);
    btngroup2 = new QButtonGroup(this);
    btngroup2->addButton(ui->radioButton_con,0);
    btngroup2->addButton(ui->radioButtonout,1);
    ui->radioButton_cam->click();
    ui->radioButton_con->click();
}

Dialogsignal::~Dialogsignal()
{
    delete ui;
}
void Dialogsignal::initform()
{
    //this->location = this->geometry();
    this->setProperty("form", true);
    this->setProperty("canMove", true);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinMaxButtonsHint);
    //ui->mainToolBar->hide();
    QString qssFile=":/qss/flatwhite.css";
    QFile file(qssFile);
    if (file.open(QFile::ReadOnly)) {
        QString qss = file.readAll();
        QString paletteColor = qss.mid(20, 7);
        this->setPalette(QPalette(QColor(paletteColor)));
        this->setStyleSheet(qss);
        file.close();
    }

}

void Dialogsignal::on_buttonBox_clicked(QAbstractButton *button)
{
    if(ui->buttonBox->button(QDialogButtonBox::Ok)==button){
        if(ui->radioButton_file->isChecked()){
            m_iwhere=1;
        }else{
            m_iwhere=0;
        }
        if(ui->radioButtonout->isChecked()){
            m_ihow=1;
        }else{
            m_ihow=0;
        }
        emit sendsignalset(m_iwhere,m_ihow);
        this->close();
    }else if(ui->buttonBox->button(QDialogButtonBox::Cancel)==button){
        this->close();
    }
}
