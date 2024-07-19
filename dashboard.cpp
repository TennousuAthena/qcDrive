#include "dashboard.h"
#include "ui_dashboard.h"

Dashboard::Dashboard(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Dashboard)
{
    ui->setupUi(this);

    connect(ui->btn1, &QPushButton::clicked, this, &Dashboard::showIndexWidget);
    connect(ui->btn2, &QPushButton::clicked, this, &Dashboard::showMaps);
    connect(ui->btn3, &QPushButton::clicked, this, &Dashboard::showBrowser);
    connect(ui->btn4, &QPushButton::clicked, this, &Dashboard::showMedia);
    connect(ui->btn5, &QPushButton::clicked, this, &Dashboard::showCenter);
    connect(ui->btn_search, &QPushButton::clicked, this, &Dashboard::showMaps);
}

Dashboard::~Dashboard()
{
    delete ui;
}

QStackedWidget* Dashboard::getStackedWidget()
{
    return ui->stackedWidget; // 返回指向stackedWidget的指针
}

IndexWidget* Dashboard::getIndexWidget()
{
    return ui->stackedWidget->findChild<IndexWidget*>("index_widget"); // 返回指向IndexWidget的指针
}

void Dashboard::showIndexWidget()
{
    ui->stackedWidget->setCurrentIndex(0);
    QPixmap pixmap(":/dashboard-main.svg");
    ui->bg->setPixmap(pixmap);
}

void Dashboard::showMp3Window()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void Dashboard::showBrowser()
{
    ui->stackedWidget->setCurrentIndex(2);
    QPixmap pixmap(":/dashboard-browser.svg");
    ui->bg->setPixmap(pixmap);
}

void Dashboard::showMaps()
{
    ui->stackedWidget->setCurrentIndex(3);
    QPixmap pixmap(":/dashboard-maps.svg");
    ui->bg->setPixmap(pixmap);
}

void Dashboard::showMedia()
{
    ui->stackedWidget->setCurrentIndex(4);
    QPixmap pixmap(":/dashboard-video.svg");
    ui->bg->setPixmap(pixmap);
}
void Dashboard::showCenter()
{
    ui->stackedWidget->setCurrentIndex(5);
}
