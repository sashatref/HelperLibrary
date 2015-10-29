INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

HEADERS += \
    $$PWD/functions.h \
    $$PWD/singleton.hpp \
    $$PWD/cmdlineparser.h \
    $$PWD/textformatter.h \
    $$PWD/cmdlineitem.h


SOURCES += \
    $$PWD/functions.cpp \
    $$PWD/cmdlineparser.cpp \
    $$PWD/textformatter.cpp \
    $$PWD/cmdlineitem.cpp




contains(QT, network) {
    HEADERS += $$PWD/filedownloader.h
    SOURCES += $$PWD/filedownloader.cpp
}

contains(QT, widgets) {
    HEADERS += $$PWD/infowindow.h
    SOURCES += $$PWD/infowindow.cpp
    FORMS += $$PWD/infowindow.ui
}
