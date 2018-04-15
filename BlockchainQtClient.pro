#-------------------------------------------------
#
# Project created by QtCreator 2018-03-19T13:57:03
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BlockchainQtClient
TEMPLATE = app

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
        definitions\loginwindow.cpp \
    definitions\httprequest.cpp \
    definitions\mainwindow.cpp \
    definitions/wallet.cpp \
    definitions/btcaddress.cpp \
    definitions/txmodel.cpp \
    definitions/settingswindow.cpp \
    qrencode/bitstream.c \
    qrencode/mask.c \
    qrencode/mmask.c \
    qrencode/mqrspec.c \
    qrencode/qrencode.c \
    qrencode/qrinput.c \
    qrencode/qrspec.c \
    qrencode/rscode.c \
    qrencode/split.c

HEADERS += \
        headers\loginwindow.h \
        headers/httprequest.h \
    headers/loginwindow.h \
    headers/mainwindow.h \
    headers/QrQtcode.h \
    headers/txmodel.h \
    headers/wallet.h \
    headers/btcaddress.h \
    headers/settingswindow.h \
    qrencode/bitstream.h \
    qrencode/config.h \
    qrencode/mask.h \
    qrencode/mmask.h \
    qrencode/mqrspec.h \
    qrencode/qrencode.h \
    qrencode/qrencode_inner.h \
    qrencode/qrinput.h \
    qrencode/qrspec.h \
    qrencode/rscode.h \
    qrencode/split.h \
    headers/settingswindow.h

FORMS += \
        forms\loginwindow.ui \
    forms\mainwindow.ui \
    forms/settingswindow.ui

RESOURCES += \
    resources.qrc

win32:RC_ICONS += res/btcico.ico








