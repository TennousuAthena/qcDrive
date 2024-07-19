#include "mapb.h"
#include "ui_mapb.h"

MapB::MapB(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MapB)  // Correct initialization
{
    ui->setupUi(this);

    ui->web_widget->load(QUrl("qrc:/webview/AMap.html"));
}

MapB::~MapB()
{
    delete ui;
}
