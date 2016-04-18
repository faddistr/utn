QT += core
QT -= gui

TARGET = testqt
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    toxtransport.cpp \
    tuntransport.cpp \
    transportfact.cpp \
    iproxyconnector.cpp \
    filetransport.cpp \
    chandler.cpp \
    handlerfact.cpp \
    transportthreader.cpp \
    chandlerprinter.cpp

HEADERS += \
    toxtransport.h \
    tuntransport.h \
    transportfact.h \
    itransport.h \
    iproxyconnector.h \
    filetransport.h \
    chandler.h \
    handlerfact.h \
    chandlercontroller.h \
    pktstr.h \
    transportcontroller.h \
    iconnector.h \
    transportthreader.h \
    chandlerprinter.h

