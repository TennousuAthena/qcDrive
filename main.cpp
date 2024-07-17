#include "widget.h"

#include <QApplication>
#include <QQuickWidget>
#include <QQmlEngine>
#include <QQmlContext>
#include <QWebEngineUrlScheme>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;

    // 配置 QWebEngineUrlScheme
    QWebEngineUrlScheme scheme("qrc");
    scheme.setFlags(
        QWebEngineUrlScheme::SecureScheme |
        QWebEngineUrlScheme::LocalAccessAllowed |
        QWebEngineUrlScheme::ViewSourceAllowed |
        QWebEngineUrlScheme::ContentSecurityPolicyIgnored |
        QWebEngineUrlScheme::CorsEnabled |
        QWebEngineUrlScheme::FetchApiAllowed
        );
    QWebEngineUrlScheme::registerScheme(scheme);


    // 获取QQuickWidget控件
    QQuickWidget *quickWidget = w.findChild<QQuickWidget*>("map_webview");
    if (quickWidget) {
        // 设置QML文件的源
        quickWidget->setSource(QUrl(QStringLiteral("qrc:/navigator.qml")));

        // 获取QML引擎
        QQmlEngine *engine = quickWidget->engine();
        if (engine) {
            // 将C++对象暴露给QML上下文（如果需要）
            engine->rootContext()->setContextProperty("cppObject", &w);
        }
    }


    QQuickWidget *quickWidget_su7 = w.findChild<QQuickWidget*>("car_webview");
    if (quickWidget_su7) {
        // 设置QML文件的源
        quickWidget_su7->setSource(QUrl(QStringLiteral("qrc:/su7.qml")));

        // 获取QML引擎
        QQmlEngine *engine = quickWidget_su7->engine();
        if (engine) {
            // 将C++对象暴露给QML上下文（如果需要）
            engine->rootContext()->setContextProperty("cppObject", &w);
        }
    }

    w.show();

    return a.exec();
}
