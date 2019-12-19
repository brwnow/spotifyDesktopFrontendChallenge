QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

CPPFLAGS = -Wall -Wextra -Werror

CONFIG(release, debug|release) {
    CPPFLAGS += -O3
}

CONFIG(debug, debug|release) {
    CPPFLAGS += -O0
}

QMAKE_CXXFLAGS = $$CPPFLAGS

DEFINES += QT_DEPRECATED_WARNINGS

SOURCEPATH = ../source

INCLUDEPATH += \
    $$SOURCEPATH/view/include

SOURCES += \
    $$SOURCEPATH/main.cpp \
    $$SOURCEPATH/view/mainwindow.cpp \
    $$SOURCEPATH/view/deletablelistview.cpp \
    $$SOURCEPATH/view/deletableitem.cpp \
    $$SOURCEPATH/view/playerview.cpp

HEADERS += \
    $$SOURCEPATH/view/include/mainwindow.hpp \
    $$SOURCEPATH/view/include/deletablelistview.hpp \
    $$SOURCEPATH/view/include/deletableitem.hpp \
    $$SOURCEPATH/view/include/playerview.hpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
