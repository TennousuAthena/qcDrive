#include "miniweather.h"
#include "ui_miniweather.h"

miniWeather::miniWeather(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::miniWeather)
{
    ui->setupUi(this);
}

miniWeather::~miniWeather()
{
    delete ui;
}
