#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF8"));
    QTextCodec *codec = QTextCodec::codecForName("GB18030");//情况2

    QTextCodec::setCodecForLocale(codec);

    a.setFont(QFont("Microsoft Yahei", 9));
    a.setWindowIcon(QIcon(":/main2.ico"));
    MainWindow w;
    w.show();

    return a.exec();
}
