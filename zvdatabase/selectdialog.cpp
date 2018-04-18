#include "selectdialog.h"
#include "ui_selectdialog.h"

SelectDialog::SelectDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SelectDialog)
{
    ui->setupUi(this);
    //设置表格的属性
    settable();
    //TODO 加载表格内容

}

SelectDialog::~SelectDialog()
{
    m_zvmap=NULL;
    m_param=NULL;
    delete ui;
}

void SelectDialog::settable()
{
    tablew=ui->tableWidget;
    tablew->setColumnCount(5);
    QStringList header;
    header<<tr("Name")<<tr("Type")<<tr("Node")<<tr("Index")<<tr("Id");
    tablew->setHorizontalHeaderLabels(header);
    QFont font = tablew->horizontalHeader()->font();
    font.setBold(true);
    tablew->horizontalHeader()->setFont(font);
    tablew->horizontalHeader()->setStretchLastSection(true); //设置充满表宽度
    //tablew->verticalHeader()->setResizeContentsPrecision();
    //tablew->verticalHeader()->setResizeMode(QHeaderView::ResizeToContents);
    tablew->verticalHeader()->setDefaultSectionSize(10); //设置行高
    tablew->setFrameShape(QFrame::NoFrame); //设置无边框
    tablew->setShowGrid(true); //显示格子线
    tablew->verticalHeader()->setVisible(false); //设置垂直头不可见
    tablew->setSelectionMode(QAbstractItemView::ExtendedSelection);  //可多选（Ctrl、Shift、  Ctrl+A都可以）
    tablew->setSelectionBehavior(QAbstractItemView::SelectRows);  //设置选择行为时每次选择一行
    tablew->setEditTriggers(QAbstractItemView::NoEditTriggers); //设置不可编辑
    //tablew->horizontalHeader()->resizeSection(0,150); //设置表头第一列的宽度为150
    tablew->horizontalHeader()->setFixedHeight(25); //设置表头的高度
    //tablew->setStyleSheet("selection-background-color:lightblue;"); //设置选中背景色
    //tablew->horizontalHeader()->setStyleSheet("QHeaderView::section{background:skyblue;}"); //设置表头背景色
    //设置水平、垂直滚动条样式
    tablew->horizontalScrollBar()->setStyleSheet("QScrollBar{background:transparent; height:10px;}"
    "QScrollBar::handle{background:lightgray; border:2px solid transparent; border-radius:5px;}"
    "QScrollBar::handle:hover{background:gray;}"
    "QScrollBar::sub-line{background:transparent;}"
    "QScrollBar::add-line{background:transparent;}");
    tablew->verticalScrollBar()->setStyleSheet("QScrollBar{background:transparent; width: 10px;}"
    "QScrollBar::handle{background:lightgray; border:2px solid transparent; border-radius:5px;}"
    "QScrollBar::handle:hover{background:gray;}"
    "QScrollBar::sub-line{background:transparent;}"
                                               "QScrollBar::add-line{background:transparent;}");
}
void SelectDialog::addrow(ParamStructure structure){
    int row_count = tablew->rowCount(); //获取表单行数
    tablew->insertRow(row_count); //插入新行
    QTableWidgetItem *item = new QTableWidgetItem();
    QTableWidgetItem *item1 = new QTableWidgetItem();
    QTableWidgetItem *item2 = new QTableWidgetItem();
    QTableWidgetItem *item3 = new QTableWidgetItem();
    QTableWidgetItem *item4 = new QTableWidgetItem();
    //设置对应的图标、文件名称、最后更新时间、对应的类型、文件大小
    item->setText(QString::fromStdString(structure.getSparamName()));
    item1->setText(QString::number(structure.getIstype()));
    item2->setText(QString::number(structure.getINode())); //type为调用系统的类型，以后缀来区分
    item3->setText(QString::number(structure.getIIndex()));
    item3->setText(QString::number(structure.getIId()));
    tablew->setItem(row_count, 0, item);
    tablew->setItem(row_count, 1, item1);
    tablew->setItem(row_count, 2, item2);
    tablew->setItem(row_count, 3, item3);
    tablew->setItem(row_count, 4, item4);
    //设置样式为灰色
    QColor color("gray");
    item1->setTextColor(color);
    item2->setTextColor(color);
    item3->setTextColor(color);
    item4->setTextColor(color);
}
void SelectDialog::loadtable()
{
    map<ParamStructure,ZvBaseParam*>::iterator it;
    for(it=m_zvmap->begin();it!=m_zvmap->end();++it)
    {
        ZvBaseParam *zb=it->second;
        addrow(zb->getDbParam());
    }
}

void SelectDialog::setmap(map<ParamStructure, ZvBaseParam *> *map)
{
    m_zvmap=map;
}

void SelectDialog::setreparam(ZvBaseParam *param)
{
    m_param=param;
}

void SelectDialog::on_pushButton_clicked()
{

}
