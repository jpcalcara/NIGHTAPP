#-------------------------------------------------
#
# Project created by QtCreator 2017-09-06T15:07:37
#
#-------------------------------------------------

QT       += core gui network sql positioning


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = NightApp
TEMPLATE = app


SOURCES += main.cpp \
    start.cpp \
    login.cpp \
    admindb.cpp \
    ventana.cpp \
    localizacion.cpp \
    mapa.cpp \
    formulario.cpp \
    usuario.cpp \
    sites.cpp \
    infolugar.cpp \
    sitesroute.cpp \
    busquedanombre.cpp \
    lineadetexto.cpp \
    manager.cpp

HEADERS  += \
    start.h \
    login.h \
    admindb.h \
    ventana.h \
    localizacion.h \
    mapa.h \
    formulario.h \
    usuario.h \
    sites.h \
    infolugar.h \
    sitesroute.h \
    busquedanombre.h \
    lineadetexto.h \
    manager.h

FORMS    += \
    start.ui \
    login.ui \
    ventana.ui \
    mapa.ui \
    formulario.ui

CONFIG += mobility
MOBILITY = 

RESOURCES += \
    recursos.qrc

QMAKE_CXXFLAGS += -std=gnu++11

RC_ICONS = a.ico

