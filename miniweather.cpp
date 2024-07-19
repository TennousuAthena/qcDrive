#include "miniweather.h"
#include "ui_miniweather.h"
#include "qtimer.h"

miniWeather::miniWeather(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::miniWeather)
    , networkManager(new QNetworkAccessManager(this))
{
    ui->setupUi(this);

    // 设置定时器定期更新天气
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &miniWeather::updateWeather);
    timer->start(3600000); // 每小时更新一次

    // 连接网络请求的信号和槽
    connect(networkManager, &QNetworkAccessManager::finished, this, &miniWeather::onNetworkReply);

    // 初次启动时更新天气
    updateWeather();
}

miniWeather::~miniWeather()
{
    delete ui;
    delete networkManager;
}

void miniWeather::updateWeather()
{
    // 发送网络请求获取天气数据
    QUrl url("https://api.caiyunapp.com/v2.6/7rrq5Y0LX1U6Whk9/123.45923,41.76693/realtime");
    QNetworkRequest request(url);
    networkManager->get(request);
}

void miniWeather::onNetworkReply(QNetworkReply* reply)
{
    if (reply->error() != QNetworkReply::NoError) {
        qDebug() << "Error: " << reply->errorString();
        reply->deleteLater();
        return;
    }

    QByteArray responseData = reply->readAll();
    QJsonDocument jsonDoc = QJsonDocument::fromJson(responseData);
    QJsonObject jsonObj = jsonDoc.object();

    // 获取实时天气信息
    QJsonObject result = jsonObj["result"].toObject();
    QJsonObject realtime = result["realtime"].toObject();
    double temperature = realtime["temperature"].toDouble();
    QString skycon = realtime["skycon"].toString();

    // 四舍五入温度
    int roundedTemperature = qRound(temperature);

    // 更新界面
    ui->tempature->setText(QString::number(roundedTemperature) + "°");
    if (skycon == "CLEAR_DAY") {
        ui->weather_icon->setPixmap(QPixmap(":/icons/clear_day.png"));
        ui->weather->setText("Sunny");
    } else if (skycon == "CLEAR_NIGHT") {
        ui->weather_icon->setPixmap(QPixmap(":/icons/clear_night.png"));
        ui->weather->setText("Clear Night");
    }
    // 继续添加其他天气情况的处理...

    reply->deleteLater();
}
