QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

QMAKE_CXXFLAGS += -Wall -Werror

DEFINES += QT_DEPRECATED_WARNINGS

SOURCEPATH = ../source
INCLUDEPATH = $$SOURCEPATH/include

SOURCES += \
    $$SOURCEPATH/main.cpp \
    $$SOURCEPATH/mainwindow.cpp

HEADERS += \
    $$INCLUDEPATH/mainwindow.hpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
