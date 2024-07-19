#include "index.h"
#include "ui_index.h"
#include <QQuickWidget>
#include <QQmlEngine>
#include <QQmlContext>
#include <QWebEngineUrlScheme>
#include "dashboard.h"

IndexWidget::IndexWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::IndexWidget)
    , dashboard(qobject_cast<Dashboard*>(parent))  // 初始化dashboard指针
    , mapWebView(nullptr)
    , carWebView(nullptr)
{
    ui->setupUi(this);
    connect(ui->gotoMusic, &QPushButton::clicked, this, &IndexWidget::showMp3Window);

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

void IndexWidget::showMp3Window()
{
    //doto: not working
    if (dashboard) {
        qDebug() << dashboard;
        dashboard->getStackedWidget()->setCurrentIndex(1);  // 使用getStackedWidget方法
        dashboard->show();
    }
}

void IndexWidget::showMp3WindowFromDashboard()
{
    showMp3Window(); // 调用showMp3Window方法
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
