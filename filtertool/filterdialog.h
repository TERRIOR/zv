/**
*@projectName   filtertool
*@documentname  filterdialog.h
*@author        zzJun
*@date          20180425
*@brief         a dialog used to set the paramster for filtertool
**/
#ifndef FILTERDIALOG_H
#define FILTERDIALOG_H

#include <QDialog>
#include <QtWidgets>

#include "filtertool.h"
#include "cvgloble.h"
namespace Ui {
class FilterDialog;
}

class FilterDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FilterDialog(QWidget *parent = 0);
    ~FilterDialog();
signals:
    //发送撤回创建信号 receiver:filtertool
    void sendrefuse();
    //发送确认信号 receiver:filtertool
    void sendconfirm();
    //发送运行信号 receiver:filtertool
    void sendwork(int type,int high,int low,int stage,int size);
    //发送数据信号 receiver:filtertool
    void sendstruct(ParamStructure structure);
private slots:
    //接收mat并显示 sender：filtertool
    void receivemat(Mat m);
    //接收数据信号 sender:数据库的dialog
    void receiveparam(ParamStructure structure);
    void on_pushButtonselect_clicked();
    void on_pushButtonshow_clicked();
    void on_buttonBox_clicked(QAbstractButton *button);

private:
    Ui::FilterDialog *ui;
    QButtonGroup *btngroup;
};

#endif // FILTERDIALOG_H
