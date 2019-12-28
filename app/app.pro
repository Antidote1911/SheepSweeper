QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets sql

TEMPLATE = app



HEADERS += \
    Constants.h \
    mainwindow.h \
    model/CModel.h \
    model/CTableModel.h \
    model/SField.h \
    SPreferences.h \
    savescore.h \
    topten.h \
    view/CActiveDelegate.h \
    view/CInactiveDelegate.h \
    view/CSettingsDialog.h \
    view/CTableView.h \
    view/CTopWidget.h


SOURCES += main.cpp \
    mainwindow.cpp \
    model/CModel.cpp \
    model/CTableModel.cpp \
    savescore.cpp \
    topten.cpp \
    view/CActiveDelegate.cpp \
    view/CInactiveDelegate.cpp \
    view/CSettingsDialog.cpp \
    view/CTableView.cpp \
    view/CTopWidget.cpp


FORMS += \
    mainwindow.ui \
    savescore.ui \
    topten.ui \
    view/CTopWidget.ui \
    view/CSettingsDialog.ui

CONFIG       += c++17
RESOURCES    += images.qrc
TRANSLATIONS += trans_pl.ts

DISTFILES += \
    ../.travis.yml \
    ../.appveyor.yml \
    ../LICENSE.md \
    ../README.md \
    ../doc/screen1.png \
    ../doc/screen2.png

