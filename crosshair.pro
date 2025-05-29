CONFIG -= debug_and_release
CONFIG -= debug_and_release_target

QT += widgets
QT += core
QT += gui

CONFIG += c++2a

debug {
    message("debug build")
    CONFIG += console
}

release {
    message("release build")
    QMAKE_LFLAGS += -mwindows
}

INCLUDEPATH += src/

QMAKE_LFLAGS += \
    -static


SOURCES += \
    src/main.cpp \
    src/crosshair/crosshair.cpp \
    src/crosshair/manager.cpp \
    src/gui/gui.cpp


HEADERS += \
    src/crosshair/crosshair.h \
    src/crosshair/manager.h \
    src/gui/gui.h \
    src/utils/vector2i.h


FORMS += \
    src/gui/gui.ui
