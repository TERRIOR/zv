#include "diaselecttool.h"
#include "ui_diaselecttool.h"

Diaselecttool::Diaselecttool(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Diaselecttool)
{
    ui->setupUi(this);

    initform();
    refreshrow();
}

Diaselecttool::~Diaselecttool()
{
    delete ui;
}
void Diaselecttool::initform()
{
    //this->location = this->geometry();
    this->setProperty("form", true);
    this->setProperty("canMove", true);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinMaxButtonsHint);
    //ui->mainToolBar->hide();
    QString qssFile=":/qss/flatwhite.css";
    QFile file(qssFile);
    if (file.open(QFile::ReadOnly)) {
        QString qss = file.readAll();
        QString paletteColor = qss.mid(20, 7);
        this->setPalette(QPalette(QColor(paletteColor)));
        this->setStyleSheet(qss);
        file.close();
    }
    ui->tableWidget->setColumnCount(1);
    QStringList header;
    header<<tr("Name");
    ui->tableWidget->setHorizontalHeaderLabels(header);
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
    //ui->tableWidgettool->horizontalHeader()->setDefaultSectionSize(220/3);
    ui->tableWidget->setFrameShape(QFrame::NoFrame); //设置无边框
    ui->tableWidget->setShowGrid(true); //显示格子线
    ui->tableWidget->verticalHeader()->setVisible(false); //设置垂直头不可见
    ui->tableWidget->setSelectionMode(QAbstractItemView::ExtendedSelection);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void Diaselecttool::on_tableWidget_cellDoubleClicked(int row, int column)
{
    cout<<row<<" "<<column<<endl;
    emit sendcol(column);
    this->close();
}
void Diaselecttool::refreshrow(){
    while (1) {
        int row_count = ui->tableWidget->rowCount(); //获取表单行数
        if(strzu[row_count].size()<4){
            break;
        }
        ui->tableWidget->insertRow(row_count); //插入新行
        QTableWidgetItem *item = new QTableWidgetItem();
        //设置对应的图标、文件名称、最后更新时间、对应的类型、文件大小
        item->setText(QString::fromStdString(strzu[row_count]));
        ui->tableWidget->setItem(row_count, 0, item);
    }

}
