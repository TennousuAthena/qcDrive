#ifndef MINIWEATHER_H
#define MINIWEATHER_H

#include <QWidget>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>

QT_BEGIN_NAMESPACE
namespace Ui { class miniWeather; }
QT_END_NAMESPACE

class miniWeather : public QWidget
{
    Q_OBJECT

public:
    miniWeather(QWidget *parent = nullptr);
    ~miniWeather();

private slots:
    void updateWeather();
    void onNetworkReply(QNetworkReply* reply);

private:
    Ui::miniWeather *ui;
    QNetworkAccessManager *networkManager;
};

#endif // MINIWEATHER_H
