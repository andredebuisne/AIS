#-------------------------------------------------
#
# Project created by QtCreator (ANDRE DEBUISNE) 2017-11-13T23:21:56
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = AIS3
TEMPLATE = app

TRANSLATIONS = AIS_en.ts #We load the different language files here
#Languages should be:
#French --> default language
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

#GFL = GOOD FILE LOCATION
SOURCES += \
    main.cpp \ #GFL
    views/mainwindow.cpp \ #GFL
    views/CRUD/source/homepagenosite.cpp \ #GFL
    services/source/actionservice.cpp \ #GFL
    views/CRUD/source/createsitedialog.cpp \ #GFL
    classes/source/site.cpp \ #GFL
    classes/source/horizon.cpp \ #GFL
    classes/source/layer.cpp \ #GFL
    classes/source/object.cpp \ #GFL
    services/source/siteservice.cpp \ #GFL
    services/source/horizonservice.cpp \ #GFL
    services/source/layerservice.cpp \ #GFL
    services/source/sitefileservice.cpp \ #GFL
    services/source/layerfileservice.cpp \ #GFL
    views/dialogs/source/settingsdialog.cpp \ #GFL
    views/CRUD/source/homepagesite.cpp \ #GFL
    views/CRUD/source/createhorizonwidget.cpp \ #GFL
    views/CRUD/source/createlayerwidget.cpp \ #GFL
    views/CRUD/source/createobjectwidget.cpp \ #GFL
    views/CRUD/source/viewhorizonwidget.cpp \ #GFL
    views/CRUD/source/viewlayerwidget.cpp \ #GFL
    views/CRUD/source/viewobjectwidget.cpp \ #GFL
    views/toolbar/source/testcontrolswidget.cpp \ #GFL
    views/harrisMatrix/source/harrismatrixwidget.cpp \ #GFL
    views/tree/source/sitetree.cpp \ #GFL
    views/toolbar/source/lefttoolbar.cpp \ #GFL
    views/toolbar/source/toptoolbar.cpp \ #GFL
    views/CRUD/source/viewsitewidget.cpp \ #GFL
    views/CRUD/source/siteinformation.cpp \ #GFL
    views/statistics/source/statisticswidgets.cpp \ #GFL
    views/map/source/mapwidget.cpp \ #GFL
    errors/source/fileerror.cpp \ #GFL
    views/harrisMatrix/source/layermatrixitem.cpp \ #GFL
    classes/source/relationship.cpp \ #GFL
    services/source/relationshipservice.cpp #GFL

HEADERS += \
    views/mainwindow.h \ #GFL
    views/CRUD/headers/homepagenosite.h \ #GFL
    services/headers/actionservice.h \ #GFL
    views/CRUD/headers/createsitedialog.h \ #GFL
    classes/headers/site.h \ #GFL
    classes/headers/horizon.h \ #GFL
    classes/headers/layer.h \ #GFL
    classes/headers/object.h \ #GFL
    services/headers/siteservice.h \ #GFL
    services/headers/horizonservice.h \ #GFL
    services/headers/layerservice.h \ #GFL
    services/headers/sitefileservice.h \ #GFL
    services/headers/layerfileservice.h \ #GFL
    views/dialogs/headers/settingsdialog.h \ #GFL
    views/CRUD/headers/homepagesite.h \ #GFL
    views/CRUD/headers/createhorizonwidget.h \ #GFL
    views/CRUD/headers/createlayerwidget.h \ #GFL
    views/CRUD/headers/createobjectwidget.h \ #GFL
    views/CRUD/headers/viewhorizonwidget.h \ #GFL
    views/CRUD/headers/viewlayerwidget.h \ #GFL
    views/CRUD/headers/viewobjectwidget.h \ #GFL
    views/toolbar/headers/testcontrolswidget.h \ #GFL
    views/harrisMatrix/headers/harrismatrixwidget.h \ #GFL
    views/tree/headers/sitetree.h \ #GFL
    views/toolbar/headers/lefttoolbar.h \ #GFL
    views/toolbar/headers/toptoolbar.h \ #GFL
    views/CRUD/headers/viewsitewidget.h \ #GFL
    views/CRUD/headers/siteinformation.h \ #GFL
    views/statistics/headers/statisticswidgets.h \ #GFL
    views/map/headers/mapwidget.h \ #GFL
    errors/headers/fileerror.h \ #GFL
    views/harrisMatrix/headers/layermatrixitem.h \ #GFL
    classes/headers/relationship.h \ #GFL
    services/headers/relationshipservice.h #GFL

DISTFILES += \
    flowchart.qmodel

RESOURCES += \
    visuals.qrc \
    content/translations/translations.qrc
