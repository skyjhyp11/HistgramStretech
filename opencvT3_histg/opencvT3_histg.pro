QT += core
QT -= gui

TARGET = opencvT3_histg
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    histogram1d.cpp \
    colorhistogram.cpp \
    contentfinder.cpp \
    imagecomparator.cpp

INCLUDEPATH += /usr/local/include \
               /usr/local/include/opencv \
               /usr/local/include/opencv2

LIBS += /usr/local/lib/libopencv_video.so  \
  /usr/local/lib/libopencv_objdetect.so \
  /usr/local/lib/libopencv_ml.so  \
  /usr/local/lib/libopencv_core.so \
  /usr/local/lib/libopencv_features2d.so  \
  /usr/local/lib/libopencv_imgproc.so \
  /usr/local/lib/libopencv_highgui.so \
  /usr/local/lib/libopencv_flann.so   \
  /usr/local/lib/libopencv_calib3d.so \
  /usr/local/lib/libopencv_imgcodecs.so

HEADERS += \
    histogram1d.h \
    colorhistogram.h \
    contentfinder.h \
    imagecomparator.h
