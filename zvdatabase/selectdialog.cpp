#include "selectdialog.h"
#include "ui_selectdialog.h"

SelectDialog::SelectDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SelectDialog)
{
    ui->setupUi(this);
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

SelectDialog::~SelectDialog()
{
    delete ui;
}
