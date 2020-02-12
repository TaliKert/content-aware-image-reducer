#-------------------------------------------------
#
# Project created by QtCreator 2019-05-22T15:47:36
#
#-------------------------------------------------

#QT       += core gui

#greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QT += core gui

greaterThan(QT_MAJOR_VERSION, 4) {
    QT += widgets
    CONFIG += c++11                 #C++11 for Qt5
} else {
    QMAKE_CXXFLAGS += -std=c++11    #C++11 for Qt4.8 and earlier
    #QMAKE_CXXFLAGS += -std=c++0x   #if you have gcc4.6 (comment previous line)
}

#if you have mac os x 10.6 or earlier then either use gcc4.7 or don't use c++11 features
macx {
    QMAKE_CXXFLAGS += -mmacosx-version-min=10.7 -stdlib=libc++
    QMAKE_LFLAGS += -mmacosx-version-min=10.7 -stdlib=libc++
}



TARGET = ContentAwareResizer
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        mainwindow.cpp \
    displayerwidget.cpp \
    scaler.cpp \
    scalewindow.cpp

HEADERS  += mainwindow.h \
    displayerwidget.h \
    scaler.h \
    scalewindow.h

FORMS    +=
