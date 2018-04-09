﻿#ifndef ZVDATABASE_G_H
#define ZVDATABASE_G_H

#include "zvdatabase.h"
#include "selectdialog.h"
#include "qdialog.h"
extern ZVDATABASESHARED_EXPORT Zvdatabase *zvdata;
//返回数据类指针
extern "C" ZVDATABASESHARED_EXPORT Zvdatabase* __stdcall getzvdata();
//数据类实例化
extern "C" ZVDATABASESHARED_EXPORT void __stdcall creatzvdata();
//销毁数据类的申请的空间，并返回NULL
extern "C" ZVDATABASESHARED_EXPORT Zvdatabase* __stdcall destroyzvdata();
extern "C" ZVDATABASESHARED_EXPORT QDialog *showDialog();

#endif // ZVDATABASE_G_H
