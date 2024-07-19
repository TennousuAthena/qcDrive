#include "carcontrol.h"
#include "ui_carcontrol.h"

carControl::carControl(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::carControl)
{
    ui->setupUi(this);
    initSocket();
    initButton();
}

carControl::~carControl()
{
    delete ui;
}

void carControl::initSocket()
{
    socket = new QTcpSocket;
    bool ok = socket->bind(QHostAddress("127.0.0.1"),8000);
    if(ok == false)
    {
        QMessageBox::warning(this,"警告","车机控制连接失败！！！");
    }
    socket->connectToHost("localhost",9000);
    if (!socket->waitForConnected(3000)) {
        qDebug() << "连接失败！";
        return;
    }
}

void carControl::initButton()
{
    ui->pushButton_Door->setAccessibleName("open");
    ui->pushButton_Light->setAccessibleName("open");
    ui->pushButton_airCondition->setAccessibleName("open");
    ui->pushButton_lock->setAccessibleName("open");
    ui->pushButton_seatAdjustment->setAccessibleName("open");
    ui->pushButton_skylight->setAccessibleName("open");
}

void carControl::on_pushButton_Door_clicked()
{
    if(ui->pushButton_Door->accessibleName() == "open")
    {
        QString message = "1 1 车门已打开！";
        socket->write(message.toLocal8Bit());
        ui->pushButton_Door->setAccessibleName("close");
    }else if(ui->pushButton_Door->accessibleName() == "close")
    {
        QString message = "1 0 车门已关闭！";
        socket->write(message.toLocal8Bit());
        ui->pushButton_Door->setAccessibleName("open");
    }
}

void carControl::on_pushButton_Light_clicked()
{
    if(ui->pushButton_Light->accessibleName() == "open")
    {
        QString message = "2 1 灯光已打开！";
        socket->write(message.toLocal8Bit());
        ui->pushButton_Light->setAccessibleName("close");
    }else if(ui->pushButton_Light->accessibleName() == "close")
    {
        QString message = "2 0 灯光已关闭！";
        socket->write(message.toLocal8Bit());
        ui->pushButton_Light->setAccessibleName("open");
    }
}

void carControl::on_pushButton_lock_clicked()
{
    if(ui->pushButton_lock->accessibleName() == "open")
    {
        QString message = "3 1 车锁已打开！";
        socket->write(message.toLocal8Bit());
        ui->pushButton_lock->setAccessibleName("close");
    }else if(ui->pushButton_lock->accessibleName() == "close")
    {
        QString message = "3 0 车锁已关闭！";
        socket->write(message.toLocal8Bit());
        ui->pushButton_lock->setAccessibleName("open");
    }
}

void carControl::on_pushButton_airCondition_clicked()
{
    if(ui->pushButton_airCondition->accessibleName() == "open")
    {
        QString message = "4 1 空调已打开！";
        socket->write(message.toLocal8Bit());
        ui->pushButton_airCondition->setAccessibleName("close");
    }else if(ui->pushButton_airCondition->accessibleName() == "close")
    {
        QString message = "4 0 空调已关闭！";
        socket->write(message.toLocal8Bit());
        ui->pushButton_airCondition->setAccessibleName("open");
    }
}

void carControl::on_pushButton_skylight_clicked()
{
    if(ui->pushButton_skylight->accessibleName() == "open")
    {
        QString message = "5 1 天窗已打开！";
        socket->write(message.toLocal8Bit());
        ui->pushButton_skylight->setAccessibleName("close");
    }else if(ui->pushButton_skylight->accessibleName() == "close")
    {
        QString message = "5 0 天窗已关闭！";
        socket->write(message.toLocal8Bit());
        ui->pushButton_skylight->setAccessibleName("open");
    }
}

void carControl::on_pushButton_seatAdjustment_clicked()
{
    if(ui->pushButton_seatAdjustment->accessibleName() == "open")
    {
        QString message = "6 1 座椅调节已打开！";
        socket->write(message.toLocal8Bit());
        ui->pushButton_seatAdjustment->setAccessibleName("close");
    }else if(ui->pushButton_seatAdjustment->accessibleName() == "close")
    {
        QString message = "6 0 座椅调节已关闭！";
        socket->write(message.toLocal8Bit());
        ui->pushButton_seatAdjustment->setAccessibleName("open");
    }
}
