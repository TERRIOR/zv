#-------------------------------------------------
#
# Project created by QtCreator 2018-04-15T21:37:43
#
#-------------------------------------------------

TARGET = cvcamera
TEMPLATE = lib
QT += widgets
DEFINES += CVCAMERA_LIBRARY

SOURCES += \
    cvcamera.cpp \
    cvcamera_g.cpp \
    camsetdialog.cpp \
    camworker.cpp \
    cvgloble.cpp \
    qgloble.cpp \
    controlthread.cpp

HEADERS += \
    cvcamera_global.h \
    cvcamera.h \
    cvcamera_g.h \
    camsetdialog.h \
    camworker.h \
    cvgloble.h \
    qgloble.h \
    controlthread.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

LIBS += -Lopencv_ffmpeg2412_64.dll
INCLUDEPATH += E:\opencv\opencv\build\include\opencv2
INCLUDEPATH += E:\opencv\opencv\build\include\opencv
INCLUDEPATH += E:\opencv\opencv\build\include
win32:CONFIG(debug, debug|release): {
LIBS += -LE:\opencv\opencv\build\x64\vc12\lib \
-lopencv_objdetect2412d\
-lopencv_ts2412d\
-lopencv_video2412d\
-lopencv_nonfree2412d\
-lopencv_ocl2412d\
-lopencv_photo2412d\
-lopencv_stitching2412d\
-lopencv_superres2412d\
-lopencv_videostab2412d\
-lopencv_calib3d2412d\
-lopencv_contrib2412d\
-lopencv_core2412d\
-lopencv_features2d2412d\
-lopencv_flann2412d\
-lopencv_gpu2412d\
-lopencv_highgui2412d\
-lopencv_imgproc2412d\
-lopencv_legacy2412d\
-lopencv_ml2412


} else:win32:CONFIG(release, debug|release): {
LIBS += -LE:\opencv\opencv\build\x64\vc12\lib \
-lopencv_objdetect2412 \
-lopencv_ts2412 \
-lopencv_video2412 \
-lopencv_nonfree2412 \
-lopencv_ocl2412 \
-lopencv_photo2412 \
-lopencv_stitching2412 \
-lopencv_superres2412 \
-lopencv_videostab2412 \
-lopencv_calib3d2412 \
-lopencv_contrib2412 \
-lopencv_core2412 \
-lopencv_features2d2412 \
-lopencv_flann2412 \
-lopencv_gpu2412 \
-lopencv_highgui2412 \
-lopencv_imgproc2412 \
-lopencv_legacy2412 \
-lopencv_ml2412


}

FORMS += \
    camsetdialog.ui
