#ifndef DIASELECTTOOL_H
#define DIASELECTTOOL_H
#include "toolsstructure.h"
#include <QDialog>
#include <qfile.h>

namespace Ui {
class Diaselecttool;
}

class Diaselecttool : public QDialog
{
    Q_OBJECT

public:
    explicit Diaselecttool(QWidget *parent = 0);
    ~Diaselecttool();

    void initform();
    void refreshrow();
signals:
    void sendcol(int i);
private slots:


    void on_tableWidget_cellDoubleClicked(int row, int column);

private:
    Ui::Diaselecttool *ui;
};

#endif // DIASELECTTOOL_H
