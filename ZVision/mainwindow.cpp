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
}

MainWindow::~MainWindow()
{
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
    qDebug()<<QChar(0xF067).unicode();
    //setIcon(ui->pushButton_min, QChar('-'),15);
    //setIcon(ui->pushButton_max, QChar(61590));
    //setIcon(ui->pushButton_close,QChar('x'),11);
}
void MainWindow::setIcon(QAbstractButton *btn, QChar c, quint32 size)
{
    QFont iconFont;
    iconFont.setPointSize(size);
    btn->setFont(iconFont);
    btn->setText(c);
}
