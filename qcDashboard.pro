QT       += core gui webenginewidgets quickwidgets printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

CONFIG -= qtquickcompiler

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    widget.cpp

HEADERS += \
    widget.h

FORMS += \
    widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    assets.qrc

DISTFILES +=


macx {
    QMAKE_RPATHDIR += @executable_path/../Frameworks
    QMAKE_LFLAGS_SONAME = -Wl,-install_name,@rpath/

    # 复制依赖的Qt库
    qtwebengine_framework.files = $$[QT_INSTALL_LIBS]/QtWebEngineCore.framework
    qtwebengine_framework.path = Contents/Frameworks
    QMAKE_BUNDLE_DATA += qtwebengine_framework

    qtwebenginewidgets_framework.files = $$[QT_INSTALL_LIBS]/QtWebEngineWidgets.framework
    qtwebenginewidgets_framework.path = Contents/Frameworks
    QMAKE_BUNDLE_DATA += qtwebenginewidgets_framework
}
