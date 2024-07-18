#include "widget.h"
#include "ui_widget.h"
#include <QQuickWidget>
#include <QQmlEngine>
#include <QQmlContext>
#include <QWebEngineUrlScheme>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
    , mapWebView(nullptr)
    , carWebView(nullptr)
{
    ui->setupUi(this);
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
    initWebViews();  // 初始化webviews
}

Widget::~Widget()
{
    delete ui;
}

void Widget::setupWebView(QQuickWidget *quickWidget, const QString &qmlSource)
{
    if (quickWidget) {
        quickWidget->setSource(QUrl(qmlSource));
        QQmlEngine *engine = quickWidget->engine();
        if (engine) {
            engine->rootContext()->setContextProperty("cppObject", this);
        }
    }
}

void Widget::initWebViews()
{
    mapWebView = findChild<QQuickWidget*>("map_webview");
    setupWebView(mapWebView, QStringLiteral("qrc:/navigator.qml"));

    carWebView = findChild<QQuickWidget*>("car_webview");
    setupWebView(carWebView, QStringLiteral("qrc:/su7.qml"));
}
