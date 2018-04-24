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
    void sendrefuse();//撤回创建
    void sendconfirm();//确认
    void sendwork(int type,int high,int low,int stage,int size);//运行
    void sendstruct(ParamStructure structure);
private slots:
    void receivemat(Mat m);//接收mat 并显示
    void on_pushButtonselect_clicked();

    void on_pushButtonshow_clicked();

    void on_buttonBox_clicked(QAbstractButton *button);
    void receiveparam(ParamStructure structure);


private:
    Ui::FilterDialog *ui;
    QButtonGroup *btngroup;
};

#endif // FILTERDIALOG_H
