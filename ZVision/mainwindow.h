#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDesktopWidget>
#include <QMouseEvent>
#include <QAbstractButton>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void setIcon(QAbstractButton *btn, QChar c, quint32 size = 9);
private slots:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void on_pushButton_min_clicked();

    void on_pushButton_max_clicked();

    void on_pushButton_close_clicked();

private:
    void initform();
    bool m_move;
    QPoint m_startPoint;
    QPoint m_windowPoint;

    bool max;
    QRect location;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
