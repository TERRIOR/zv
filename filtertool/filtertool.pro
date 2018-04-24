#-------------------------------------------------
#
# Project created by QtCreator 2018-04-21T22:02:12
#
#-------------------------------------------------

TARGET = filtertool
TEMPLATE = lib
QT += widgets
QT += core gui
CONFIG += dll
DEFINES += FILTERTOOL_LIBRARY

SOURCES += filtertool.cpp \
    cvgloble.cpp \
    fftfilter.cpp \
    imageparam.cpp \
    paramstructure.cpp \
    qgloble.cpp \
    zvbaseparam.cpp \
    filterdialog.cpp \
    filtertool_g.cpp \
    toolsbase.cpp \
    toolsstructure.cpp

HEADERS += filtertool.h\
        filtertool_global.h \
    cvgloble.h \
    fftfilter.h \
    imageparam.h \
    paramstructure.h \
    qgloble.h \
    zvbaseparam.h \
    filterdialog.h \
    filtertool_g.h \
    toolsbase.h \
    toolsstructure.h \

unix {
    target.path = /usr/lib
    INSTALLS += target
}

INCLUDEPATH += E:\QTPROJECT\zv\zvdatabase
INCLUDEPATH += E:\opencv\opencv\build\include\opencv2
INCLUDEPATH += E:\opencv\opencv\build\include\opencv
INCLUDEPATH += E:\opencv\opencv\build\include

LIBS += -Lopencv_ffmpeg2412_64.dll
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

LIBS += -LE:\QTPROJECT\build-zvdatabase-Desktop_Qt_5_7_0_MSVC2013_64bit-Debug\debug
LIBS += -lzvdatabase

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

LIBS += -LE:\QTPROJECT\build-zvdatabase-Desktop_Qt_5_7_0_MSVC2013_64bit-Release\release
LIBS += -lzvdatabase

}
FORMS += \
    filterdialog.ui
