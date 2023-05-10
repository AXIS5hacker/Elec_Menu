# ----------------------------------------------------
# This file is generated by the Qt Visual Studio Tools.
# ------------------------------------------------------
QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = app
TARGET = Elec_Menu
DESTDIR = ./debug
CONFIG += debug
CONFIG += c++17
DEFINES += _WINDOWS _UNICODE _ENABLE_EXTENDED_ALIGNED_STORAGE WIN64
LIBS += -L"." \
    -lshell32
LIBS += -L./Elec_Menu/libs/ -llibmysql
DEPENDPATH += .
MOC_DIR += .
OBJECTS_DIR += debug
UI_DIR += .
RCC_DIR += .
TRANSLATIONS += Elec_Menu/Elec_Menu_zh_CN.ts
HEADERS += ./Elec_Menu/Dish.h \
    ./Elec_Menu/Dishs.h \
    ./Elec_Menu/Order.h \
    ./Elec_Menu/Orders.h \
    ./Elec_Menu/mainwindow.h \
    Elec_Menu/Material.h \
    Elec_Menu/Materials.h \
    Elec_Menu/SQLserver.h \
    Elec_Menu/add_dish.h \
    Elec_Menu/create_order.h \
    Elec_Menu/modify_dish.h \
    Elec_Menu/modify_order.h
SOURCES += ./Elec_Menu/main.cpp \
    ./Elec_Menu/mainwindow.cpp \
    Elec_Menu/Dish.cpp \
    Elec_Menu/Dishs.cpp \
    Elec_Menu/Material.cpp \
    Elec_Menu/Materials.cpp \
    Elec_Menu/Order.cpp \
    Elec_Menu/Orders.cpp \
    Elec_Menu/SQLserver.cpp \
    Elec_Menu/add_dish.cpp \
    Elec_Menu/create_order.cpp \
    Elec_Menu/functions.cpp \
    Elec_Menu/modify_dish.cpp \
    Elec_Menu/modify_order.cpp
FORMS += ./Elec_Menu/mainwindow.ui \
    Elec_Menu/add_dish.ui \
    Elec_Menu/create_order.ui \
    Elec_Menu/modify_dish.ui \
    Elec_Menu/modify_order.ui
TRANSLATIONS += ./Elec_Menu/Elec_Menu_zh_CN.ts

RESOURCES += \
    Elec_Menu/resources.qrc
