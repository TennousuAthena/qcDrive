QT       += core gui webenginewidgets quickwidgets network multimedia multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

CONFIG -= qtquickcompiler

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    dashboard.cpp \
    index.cpp \
    main.cpp \
    login_dialog.cpp\
    miniweather.cpp \
    subprojects/MapB/mapb.cpp \
    subprojects/myQWebEngine/mainwindow.cpp \
    subprojects/myQWebEngine/webview.cpp \
    subprojects/mp3/mp3.cpp \
    subprojects/qtMedia/media.cpp \
    subprojects/carControl/carControl.cpp\
    subprojects/carCenter/carCenter.cpp\
    weatherpage.cpp

HEADERS += \
    dashboard.h \
    index.h \
    miniweather.h \
    login_dialog.h\
    subprojects/MapB/mapb.h \
    subprojects/myQWebEngine/mainwindow.h \
    subprojects/myQWebEngine/webview.h \
    subprojects/mp3/mp3.h \
    subprojects/qtMedia/media.h \
    subprojects/carControl/carControl.h\
    subprojects/carCenter/carCenter.h\
    weatherpage.h

FORMS += \
    dashboard.ui \
    index.ui \
    miniweather.ui \
    login_dialog.ui\
    subprojects/MapB/mapb.ui \
    subprojects/myQWebEngine/mainwindow.ui \
    subprojects/mp3/mp3.ui \
    subprojects/qtMedia/media.ui \
    subprojects/carControl/carControl.ui\
    subprojects/carCenter/carCenter.ui\
# Default rules for deployment.
# qnx: target.path = /tmp/$${TARGET}/bin
# else: unix:!android: target.path = /opt/$${TARGET}/bin
 \# !isEmpty(target.path): INSTALLS += target
    weatherpage.ui

RESOURCES += \
    assets.qrc


DISTFILES +=
