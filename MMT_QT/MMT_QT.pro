#-------------------------------------------------
#
# Project created by QtCreator 2015-06-21T20:01:09
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MMT_QT
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    vfpsearch.cpp \
    vfpsearchind.cpp \
    ffmpegfileinfo.cpp \
    ffmpegreader.cpp \
    vfpimagehelper.cpp \
    videofingerprint.cpp

HEADERS  += mainwindow.h \
    vfpcmp.h \
    vfpsearch.h \
    vfpsearchind.h \
    VisioForge_VFP_Types.h \
    VisioForge_VFP.h \
    ffmpegfileinfo.h \
    ffmpegreader.h \
    vfpimagehelper.h \
    vfptypes.hr \
    videofingerprint.h

FORMS    += mainwindow.ui


INCLUDEPATH += $$PWD/
DEPENDPATH += $$PWD/

#LIBS += -ldl -lz -zlib

QMAKE_LFLAGS += $$(LDFLAGS)
QMAKE_LFLAGS += -lz

LIBS += -L/usr/lib/x86_64-linux-gnu
LIBS += -L/home/elsa/Desktop/vfp/MMT_QT/lib_linux64
LIBS += -lavutil -lavformat -lavcodec -lswscale -lz -lbz2

INCLUDEPATH += /usr/include/x86_64-linux-gnu/libavformat
INCLUDEPATH += /usr/include/x86_64-linux-gnu/libavutil
INCLUDEPATH += /usr/include/x86_64-linux-gnu/libavcodec

HEADERS += \
    ffmpegreader.h

unix:!macx: LIBS += -L$$PWD/../SDK/QT/Debug64/

INCLUDEPATH += $$PWD/../SDK/QT/Debug64
DEPENDPATH += $$PWD/../SDK/QT/Debug64

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../../../../home/elsa/Desktop/vfp/MMT_QT/lib_linux64/release/ -lVisioForge_VFP_QT
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../../../../home/elsa/Desktop/vfp/MMT_QT/lib_linux64/debug/ -lVisioForge_VFP_QT
else:unix: LIBS += -L$$PWD/../../../../../../../home/elsa/Desktop/vfp/MMT_QT/lib_linux64/ -lVisioForge_VFP_QT

INCLUDEPATH += $$PWD/../../../../../../../home/elsa/Desktop/vfp/MMT_QT/lib_linux64
DEPENDPATH += $$PWD/../../../../../../../home/elsa/Desktop/vfp/MMT_QT/lib_linux64
