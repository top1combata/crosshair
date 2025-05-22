CONFIG -= debug_and_release
CONFIG -= debug_and_release_target

QT += widgets
QT += core
QT += gui

CONFIG += c++2a

INCLUDEPATH += src/

QMAKE_LFLAGS += -static
QMAKE_LFLAGS += -mwindows


SOURCES += \
    src/gui/gui.cpp \
    src/main.cpp 


HEADERS += \
    src/gui/gui.h


FORMS += \
    src/gui/gui.ui

