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
#include <QFile>
#include <QTextStream>
#include <QDataStream>
#define  SAVE_DATA          "CAM_SAVE.zv"
namespace Ui {
class CamsetDialog;
}


class  CamsetDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CamsetDialog(QWidget *parent = 0);
    ~CamsetDialog();

    void loadData();
    void saveData();
private slots:
    void on_buttonBox_clicked(QAbstractButton *button);

    void on_pushButtonstart_clicked();

    void on_pushButtonstop_clicked();

    void refleshpic();
    void UpdateGUI();

private:
    int m_iCameraId=0;//相机的识别码 如“0”（暂定）
    int m_iWidth=-1;//图像宽度
    int m_iHight=-1;//图像高度
    int m_iFps=-1;//图像帧数
    int m_iExposure=-1;//图像曝光值
    int m_iBrightness=-1;//图像亮度
    int m_iContrast=-1;//图像对比度
    int m_iHue=-1;//图像色度
    int m_iSaturation=-1;//图像饱和度
    QTimer *tmrTimer;
    Ui::CamsetDialog *ui;
    controlthread *conthreader;
};

#endif // CAMSETDIALOG_H
