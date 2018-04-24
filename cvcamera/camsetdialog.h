/**
*@projectName   cvcamera
*@documentname  camsetdialog.h
*@author        zzJun
*@date          20180422
*@brief         the dialog class used to set the camera paramster for user
**/
#ifndef CAMSETDIALOG_H
#define CAMSETDIALOG_H

#include <QDialog>
#include "cvcamera.h"
#include <QAbstractButton>
#include "camworker.h"
#include "qglobal.h"
#include "qgloble.h"
#include "cvgloble.h"
#include "controlthread.h"
#include <QTimer>
namespace Ui {
class CamsetDialog;
}


class  CamsetDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CamsetDialog(QWidget *parent = 0);
    ~CamsetDialog();

private slots:
    void on_buttonBox_clicked(QAbstractButton *button);

    void on_pushButtonstart_clicked();

    void on_pushButtonstop_clicked();

    void refleshpic();
    void UpdateGUI();

private:
    QTimer *tmrTimer;
    Ui::CamsetDialog *ui;
    controlthread *conthreader;
};

#endif // CAMSETDIALOG_H
