#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    serial = new QSerialPort;
    connect(serial, &QSerialPort::readyRead,this, &Widget::receive_data);
    ui->pushButton_3->hide();
    ui->widget->hide();

    ui->pushButton_2->hide();

    player = new QMediaPlayer(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::open_port(
        QString name,QString baud,
        QString stop,QString data,QString parity)
{
    serial->setPortName(name);
    if(baud == "9600") {
        serial->setBaudRate(QSerialPort::Baud9600);
    }
    else if(baud == "115200") {
        serial->setBaudRate(QSerialPort::Baud115200);
    }
    else if(baud == "460800") {
        serial->setBaudRate(baud.toInt());
    }
    else {
        return;
    }
    if(stop == "1") {
        serial->setStopBits(QSerialPort::OneStop);
    }
    else if(stop == "1.5") {
        serial->setStopBits(QSerialPort::OneAndHalfStop);
    }
    else if(stop == "2") {
        serial->setStopBits(QSerialPort::TwoStop);
    }
    else {
        return;
    }
    if(data == "8") {
        serial->setDataBits(QSerialPort::Data8);
    }
    else if(data == "7") {
       serial->setDataBits(QSerialPort::Data7);
    }
    else if(data == "6") {
        serial->setDataBits(QSerialPort::Data6);
    }
    else {
        return;
    }
    if(parity == "No") {
        serial->setParity(QSerialPort::NoParity);
    }
    else if(parity == "Odd") {
       serial->setParity(QSerialPort::OddParity);
    }
    else {
        return;
    }
    serial->setFlowControl(QSerialPort::NoFlowControl);
    if (serial->open(QIODevice::ReadWrite)) {

        return;
    } else {
        return;
    }
}
QList<QSerialPortInfo> Widget::get_port(void)
{
    QList<QSerialPortInfo> infos = QSerialPortInfo::availablePorts();
    return infos;
}
void Widget::close_port(void)
{
    serial->close();
}
void Widget::receive_data(void)
{
    QByteArray array = serial->readAll();
    QString string = QString::fromUtf8(array);
    ui->plainTextEdit->appendPlainText(string);
    qDebug() << string;

    if(string == "1")
    {
        ui->pushButton_3->show();
        ui->pushButton_2->show();
        ui->pushButton_3->setStyleSheet("border-image: url(:/new/prefix1/image/1.png);");



        QString path =QCoreApplication::applicationDirPath() + "/" + "MP3.mp3";

        QUrl audioUrl(path);
        player->setSource(audioUrl);
        player->play();



    }
    else if(string == "2")
    {
        ui->pushButton_3->show();
        ui->pushButton_2->show();
ui->pushButton_3->setStyleSheet("border-image: url(:/new/prefix1/image/2.png);");


QString path =QCoreApplication::applicationDirPath() + "/" + "MP3.mp3";

QUrl audioUrl(path);
player->setSource(audioUrl);
player->play();
    }
    else if(string == "3")
    {
        ui->pushButton_3->show();
        ui->pushButton_2->show();
ui->pushButton_3->setStyleSheet("border-image: url(:/new/prefix1/image/3.png);");


QString path =QCoreApplication::applicationDirPath() + "/" + "MP3.mp3";

QUrl audioUrl(path);
player->setSource(audioUrl);
player->play();
    }
    else if(string == "4")
    {
         ui->pushButton_3->show();
         ui->pushButton_2->show();
ui->pushButton_3->setStyleSheet("border-image: url(:/new/prefix1/image/4.png);");


QString path =QCoreApplication::applicationDirPath() + "/" + "MP3.mp3";

QUrl audioUrl(path);
player->setSource(audioUrl);
player->play();
    }
    else
    {
        ui->pushButton_3->hide();
        player->stop();
        ui->pushButton_2->hide();
        player->stop();
    }
}

void Widget::on_pushButton_clicked()
{
    QList<QSerialPortInfo> portlist = get_port();
    foreach (QSerialPortInfo info, portlist) {
        ui->comboBox->addItem(info.portName());
    }
}

void Widget::on_pushButton_2_clicked()
{
    if(ui->pushButton_2->text() == "openport")
    {
        QString name = ui->comboBox->currentText();
        QString baud = ui->comboBox_2->currentText();
        QString stop = ui->comboBox_3->currentText();
        QString data = ui->comboBox_4->currentText();
        QString parity = ui->comboBox_5->currentText();
        open_port(name,baud,stop,data,parity);
        ui->pushButton_2->setText("closeport");
    }
    else if(ui->pushButton_2->text() == "closeport")
    {
        ui->pushButton_2->setText("openport");
        close_port();
    }
}


void Widget::on_pushButton_3_clicked()
{
    //QString str = ui->lineEdit->text();
//    QByteArray byteArray = str.toUtf8();
//    serial->write(byteArray);
}


void Widget::on_pushButton_7_clicked()
{
    ui->widget->hide();
}

void Widget::on_pushButton_4_clicked()
{
    ui->widget->show();
}



void Widget::on_pushButton_5_clicked()
{
    QList<QSerialPortInfo> portlist = get_port();
    foreach (QSerialPortInfo info, portlist) {
        ui->comboBox->addItem(info.portName());
    }
}

void Widget::on_pushButton_6_clicked()
{
    if(ui->pushButton_6->text() == "openport")
    {
        QString name = ui->comboBox->currentText();
        QString baud = ui->comboBox_2->currentText();
        QString stop = ui->comboBox_3->currentText();
        QString data = ui->comboBox_4->currentText();
        QString parity = ui->comboBox_5->currentText();
        open_port(name,baud,stop,data,parity);
        ui->pushButton_6->setText("closeport");
    }
    else if(ui->pushButton_6->text() == "closeport")
    {
        ui->pushButton_6->setText("openport");
        close_port();
    }
}
