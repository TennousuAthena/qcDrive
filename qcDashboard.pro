QT       += core gui webenginewidgets quickwidgets network multimedia

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
    subprojects/myQWebEngine/mainwindow.cpp \
    subprojects/myQWebEngine/webview.cpp \
    subprojects/mp3/mp3.cpp

HEADERS += \
    dashboard.h \
    index.h \
    subprojects/myQWebEngine/mainwindow.h \
    subprojects/myQWebEngine/webview.h \
    subprojects/mp3/mp3.h

FORMS += \
    dashboard.ui \
    index.ui \
    subprojects/myQWebEngine/mainwindow.ui \
    subprojects/mp3/mp3.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    assets.qrc

DISTFILES +=
