#ifndef CONTROLIMGTHREAD_H
#define CONTROLIMGTHREAD_H

#include <QObject>
#include "imageworker.h"
class controlimgthread : public QObject
{
    Q_OBJECT
public:
    explicit controlimgthread(QObject *parent = 0);
    ~controlimgthread();
    void stopthread();
    void startthread();
    void release();

    bool opened() const;
    void setOpened(bool opened);

private:

    QThread *thread;
    imageworker *worker;
    bool m_opened=false;
    bool m_uicall=false;//true:是dialog调用
};

#endif // CONTROLIMGTHREAD_H
