#include "weatherpage.h"
#include "ui_weatherpage.h"

WeatherPage::WeatherPage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::WeatherPage)
{
    ui->setupUi(this);
    ui->widget->setUrl(QUrl("qrc:/webview/weather.html"));
}

WeatherPage::~WeatherPage()
{
    delete ui;
}
