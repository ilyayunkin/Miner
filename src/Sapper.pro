QT       += core gui

CONFIG   += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

INCLUDEPATH += ../

TARGET = Sapper
TEMPLATE = app

HEADERS += \
    Sapper.h \
    SapperWidget.h \
    SapperPrivate.h \
    SapperGameField.h \
    SapperFieldWidget.h \
    ChampionsTable.h \
    FlagState.h

SOURCES += \
    Sapper.cpp \
    SapperWidget.cpp \
    main.cpp \
    SapperPrivate.cpp \
    SapperGameField.cpp \
    SapperFieldWidget.cpp \
    ChampionsTable.cpp

RESOURCES += \
    icons.qrc
