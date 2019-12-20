QT += core gui widgets sql

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
    $$SOURCEPATH/include \
    $$SOURCEPATH/view/include \
    $$SOURCEPATH/model/database/include \
    $$SOURCEPATH/controller/include

SOURCES += \
    $$SOURCEPATH/main.cpp \
    $$SOURCEPATH/core.cpp \
    $$SOURCEPATH/view/mainwindow.cpp \
    $$SOURCEPATH/view/deletablelistview.cpp \
    $$SOURCEPATH/view/deletableitem.cpp \
    $$SOURCEPATH/view/playerview.cpp \
    $$SOURCEPATH/model/database/playlisttable.cpp \
    $$SOURCEPATH/model/database/songtable.cpp \
    $$SOURCEPATH/controller/playlistcontroller.cpp \
    $$SOURCEPATH/controller/songlistcontroller.cpp \

HEADERS += \
    $$SOURCEPATH/include/core.hpp \
    $$SOURCEPATH/view/include/mainwindow.hpp \
    $$SOURCEPATH/view/include/deletablelistview.hpp \
    $$SOURCEPATH/view/include/deletableitem.hpp \
    $$SOURCEPATH/view/include/playerview.hpp \
    $$SOURCEPATH/model/database/include/playlisttable.hpp \
    $$SOURCEPATH/model/database/include/songtable.hpp \
    $$SOURCEPATH/controller/include/playlistcontroller.hpp \
    $$SOURCEPATH/controller/include/songlistcontroller.hpp \

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
