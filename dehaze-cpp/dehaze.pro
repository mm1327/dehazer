#-------------------------------------------------
#
# Project created by QtCreator 2020-08-05T10:34:38
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = dehaze
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    haze.cpp

HEADERS += \
        mainwindow.h \
    haze.h

FORMS += \
        mainwindow.ui

QMAKE_CXXFLAGS += -std=c++11


INCLUDEPATH += /usr/include/opencv4/

LIBS += -L/usr/lib/aarch64-linux-gnu/ \
-lopencv_dnn -lopencv_ml -lopencv_objdetect -lopencv_features2d \
-lopencv_core -lopencv_stitching -lopencv_calib3d -lopencv_highgui -lopencv_photo \
-lopencv_gapi -lopencv_video -lopencv_flann -lopencv_imgproc -lopencv_imgcodecs -lopencv_videoio


