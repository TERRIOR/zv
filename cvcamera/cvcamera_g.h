#ifndef CVCAMERA_G_H
#define CVCAMERA_G_H
#include "cvcamera_global.h"
#include "cvcamera.h"
#include "qdialog.h"
#include "camsetdialog.h"
#include "camworker.h"
#include "controlthread.h"
extern "C" CVCAMERASHARED_EXPORT  void __stdcall creatcvcam();
extern "C" CVCAMERASHARED_EXPORT cvcamera* __stdcall destroycvcam();
extern "C" CVCAMERASHARED_EXPORT  cvcamera* __stdcall getcvcam();
extern "C" CVCAMERASHARED_EXPORT QDialog* __stdcall showcamDialog();

extern "C" CVCAMERASHARED_EXPORT controlthread* __stdcall creatimgthread();
//extern "C" CVCAMERASHARED_EXPORT void __stdcall destroyimgthread(controlthread* con);
#endif // CVCAMERA_G_H
