#include "index.h"
#include "ui_index.h"
#include <QQuickWidget>
#include <QQmlEngine>
#include <QQmlContext>
#include <QWebEngineUrlScheme>
#include <QMessageBox>
#include <QDialog>
#include <QLabel>
#include <QVBoxLayout>
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

    // 连接SOS按钮的点击信号到sendSOS槽函数
    connect(ui->buttonSOS, &QPushButton::clicked, this, &IndexWidget::sendSOS);
}

IndexWidget::~IndexWidget()
{
    delete ui;
}

void IndexWidget::showMp3Window()
{
    // 处理跳转到音乐窗口的逻辑
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

void IndexWidget::sendSOS()
{
    QMessageBox sosMsgBox;
    sosMsgBox.setWindowTitle("SOS");
    sosMsgBox.setText("SOS signal sent!");
    sosMsgBox.setIcon(QMessageBox::Warning);

    // 设置QMessageBox的样式表，包括文字颜色
    sosMsgBox.setStyleSheet("QLabel{color: red; font-size: 18px;}");

    sosMsgBox.exec();
    showSOSMessage();
}
void IndexWidget::showSOSMessage()
{
    QDialog *dialog = new QDialog(this);
    dialog->setWindowTitle("SOS Message");
    dialog->resize(300, 200);

    QLabel *label = new QLabel("This is an SOS message!", dialog);
    label->setStyleSheet("color: red; font-size: 18px;");
    label->setAlignment(Qt::AlignCenter);

    QVBoxLayout *layout = new QVBoxLayout(dialog);
    layout->addWidget(label);

    dialog->setLayout(layout);
    dialog->exec();
}
