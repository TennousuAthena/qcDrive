#include "dashboard.h"
#include "ui_dashboard.h"

Dashboard::Dashboard(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Dashboard)
{
    ui->setupUi(this);

    connect(ui->btn1, &QPushButton::clicked, this, &Dashboard::showIndexWidget);
    connect(ui->btn2, &QPushButton::clicked, this, &Dashboard::showMp3Window);
    connect(ui->btn3, &QPushButton::clicked, this, &Dashboard::showBrowser);
}

Dashboard::~Dashboard()
{
    delete ui;
}

void Dashboard::showIndexWidget()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void Dashboard::showMp3Window()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void Dashboard::showBrowser()
{
    ui->stackedWidget->setCurrentIndex(2);
}