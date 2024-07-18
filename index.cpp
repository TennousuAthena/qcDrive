#include "index.h"
#include "ui_index.h"
#include <QQuickWidget>
#include <QQmlEngine>
#include <QQmlContext>
#include <QWebEngineUrlScheme>

IndexWidget::IndexWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::IndexWidget)
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

IndexWidget::~IndexWidget()
{
    delete ui;
}

void IndexWidget::setupWebView(QQuickWidget *quickWidget, const QString &qmlSource)
{
    if (quickWidget) {
        quickWidget->setSource(QUrl(qmlSource));
        QQmlEngine *engine = quickWidget->engine();
        if (engine) {
            engine->rootContext()->setContextProperty("cppObject", this);
        }
    }
}

void IndexWidget::initWebViews()
{
    mapWebView = findChild<QQuickWidget*>("map_webview");
    setupWebView(mapWebView, QStringLiteral("qrc:/navigator.qml"));

    carWebView = findChild<QQuickWidget*>("car_webview");
    setupWebView(carWebView, QStringLiteral("qrc:/su7.qml"));
}
