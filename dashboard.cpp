#include "dashboard.h"
#include "ui_dashboard.h"

Dashboard::Dashboard(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Dashboard)
{
    ui->setupUi(this);

    connect(ui->btn1, &QPushButton::clicked, this, &Dashboard::showIndexWidget);
    connect(ui->btn2, &QPushButton::clicked, this, &Dashboard::showMp3Window);
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
