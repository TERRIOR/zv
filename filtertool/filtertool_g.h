/**
*@projectName   filtertool
*@documentname  filtertool_g.h
*@author        zzJun
*@date          20180425
*@brief         Providing interface
**/
#ifndef FILTERTOOL_G_H
#define FILTERTOOL_G_H
#include "filtertool_global.h"
#include "filtertool.h"
#include "toolsbase.h"
extern "C" FILTERTOOLSHARED_EXPORT toolsbase* __stdcall creatfiltertool(int node);
extern "C" FILTERTOOLSHARED_EXPORT toolsbase* __stdcall CreatFilterTool();
extern "C" FILTERTOOLSHARED_EXPORT void  __stdcall destroytool();

#endif // FILTERTOOL_G_H
