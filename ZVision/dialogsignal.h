#ifndef DIALOGSIGNAL_H
#define DIALOGSIGNAL_H

#include <QDialog>
#include <qfile.h>

#include <QtWidgets>
namespace Ui {
class Dialogsignal;
}

class Dialogsignal : public QDialog
{
    Q_OBJECT

public:
    explicit Dialogsignal(QWidget *parent = 0);
    ~Dialogsignal();

    void initform();
private slots:
    void on_buttonBox_clicked(QAbstractButton *button);
signals:
    void sendsignalset(int where,int how);
private:
    Ui::Dialogsignal *ui;
    QButtonGroup *btngroup1;
    QButtonGroup *btngroup2;
    int m_iwhere=0;
    int m_ihow=0;
};

#endif // DIALOGSIGNAL_H
