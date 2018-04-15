#ifndef SELECTDIALOG_H
#define SELECTDIALOG_H

#include <QDialog>
#include <QtWidgets>
#include <map>
#include "paramheader.h"
namespace Ui {
class SelectDialog;
}

class SelectDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SelectDialog(QWidget *parent = 0);
    ~SelectDialog();
    void settable();
    void loadtable();
    //创建对象时，由数据类db传递map给dialog调用
    void setmap(map<ParamStructure,ZvBaseParam*> *map);
    //客户端被返回对象指针后，把待获取的数据变量指针传过来
    void setreparam(ZvBaseParam* param);
    void addrow(ParamStructure structure);
private:
    Ui::SelectDialog *ui;
    QTableWidget *tablew;
    ZvBaseParam* m_param=NULL;
    map<ParamStructure,ZvBaseParam*> *m_zvmap=NULL;
};

#endif // SELECTDIALOG_H
