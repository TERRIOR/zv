#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDesktopWidget>
#include <QMouseEvent>
#include <QAbstractButton>
#include "zvdatabase_g.h"
#include "cvcamera_g.h"
#include "imageparam.h"
#include "zvbaseparam.h"
#include "filtertool_g.h"
#include <iostream>
#include "cvgloble.h"
#include "dialogsignal.h"
#include "toolsstructure.h"
#include "controlimgthread.h"
#include "diaselecttool.h"
using namespace std;
namespace Ui{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void closecam();
    void opencam();
    void refreshmat();
    void setIcon(QAbstractButton *btn, QChar c, quint32 size = 9);
    void loadtool(QTextStream &in);

    void addrow(ToolsStructure structure);
    void refreshtoollist();
private slots:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void on_pushButton_min_clicked();

    void on_pushButton_max_clicked();

    void on_pushButton_close_clicked();

    void on_pushButton_setcam_clicked();
    void on_comboBoxnode_currentIndexChanged(int index);
    void on_pushButtoncamclose_clicked();

    void on_pushButton_pic_clicked();

    void on_pushButton_load_clicked();

    void on_pushButton_save_clicked();

    void on_pushButton_clicked();

    void on_pushButton_signal_clicked();

    void on_pushButton_node_clicked();

    void on_pushButton_run_toggled(bool checked);

    void on_pushButton_addnode_clicked();

    void updatetoollist();
    void on_tableWidgettool_cellDoubleClicked(int row, int column);

public slots:
    void UpdateGUI();
    void receiveparam(ParamStructure Structure);
    void signalset(int where,int how);
    void receivetype(int i);
private:
    void initform();
    bool m_move;
    int m_inodecount=1;
    int m_inodenow;
    int m_iwhere=0;
    int m_ihow=0;
    QPoint m_startPoint;
    QPoint m_windowPoint;
    bool max;
    QRect location;
    Ui::MainWindow *ui;
    Mat imgcam;
    Mat* imgshow=NULL;
    ImageParam *imgcamp;
    //ImageParam *imgparam2;
    Zvdatabase *m_zvdata;
    controlthread* conthread;
    controlimgthread* imgthread=NULL;
    QTimer *tmrTimer;
    vector<toolsbase*> vectool;
    int maxpic=6;
};

#endif // MAINWINDOW_H
