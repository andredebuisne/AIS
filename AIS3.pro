#-------------------------------------------------
#
# Project created by QtCreator 2017-11-13T23:21:56
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = AIS3
TEMPLATE = app

TRANSLATIONS = AIS_en.ts #We load the different language files here
#Languages should be:
#French
#English
#Spanish
#Italian
#German

#AIS_es.ts \
#AIS_it.ts \
#AIS_de.ts

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    homepagenosite.cpp \
    actionservice.cpp \
    createsitedialog.cpp \
    site.cpp \
    horizon.cpp \
    layer.cpp \
    object.cpp \
    siteservice.cpp \
    horizonservice.cpp \
    layerservice.cpp \
    sitefileservice.cpp \
    layerfileservice.cpp \
    settingsdialog.cpp \
    homepagesite.cpp \
    createhorizonwidget.cpp \
    createlayerwidget.cpp \
    createobjectwidget.cpp \
    viewhorizonwidget.cpp \
    viewlayerwidget.cpp \
    viewobjectwidget.cpp \
    testcontrolswidget.cpp \
    harrismatrixwidget.cpp \
    sitetree.cpp \
    lefttoolbar.cpp \
    toptoolbar.cpp \
    viewsitewidget.cpp \
    siteinformation.cpp \
    statisticswidgets.cpp \
    mapwidget.cpp \
    fileerror.cpp \
    layermatrixitem.cpp \
    relationship.cpp \
    relationshipservice.cpp

HEADERS += \
        mainwindow.h \
    homepagenosite.h \
    actionservice.h \
    createsitedialog.h \
    site.h \
    horizon.h \
    layer.h \
    object.h \
    siteservice.h \
    horizonservice.h \
    layerservice.h \
    sitefileservice.h \
    layerfileservice.h \
    settingsdialog.h \
    homepagesite.h \
    createhorizonwidget.h \
    createlayerwidget.h \
    createobjectwidget.h \
    viewhorizonwidget.h \
    viewlayerwidget.h \
    viewobjectwidget.h \
    testcontrolswidget.h \
    harrismatrixwidget.h \
    sitetree.h \
    lefttoolbar.h \
    toptoolbar.h \
    viewsitewidget.h \
    siteinformation.h \
    statisticswidgets.h \
    mapwidget.h \
    fileerror.h \
    layermatrixitem.h \
    relationship.h \
    relationshipservice.h

DISTFILES += \
    flowchart.qmodel

FORMS += \
    mainwindow_nosite.ui \
    error.ui

RESOURCES += \
    visuals.qrc \
    translations.qrc
