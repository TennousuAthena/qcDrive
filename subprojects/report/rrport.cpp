#include "rrport.h"
#include "ui_rrport.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initSocket();
    initLabel();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initSocket()
{
    m_tcpServer = new QTcpServer(this);
    // 服务端监听客户端发来的请求
    if (!m_tcpServer->listen(QHostAddress::Any, 9000)) {
        qDebug() << m_tcpServer->errorString();
    }
    connect(m_tcpServer, &QTcpServer::newConnection, this, &MainWindow::onNewConnect);
}

void MainWindow::initLabel()
{
    ui->label_door->setText("");
    ui->label_airCondition->setText("");
    ui->label_light->setText("");
    ui->label_lock->setText("");
    ui->label_seatAdjustment->setText("");
    ui->label_skylight->setText("");
}

void MainWindow::onNewConnect()
{
    // 当前连接的客户端
    m_tcpSocket = m_tcpServer->nextPendingConnection();
    // 断开连接
    connect(m_tcpSocket, &QTcpSocket::disconnected, m_tcpSocket, &QTcpSocket::deleteLater);
    // socket有数据时会发送readyRead信号
    connect(m_tcpSocket, &QTcpSocket::readyRead, this, &MainWindow::onReadMsg);
}

void MainWindow::onReadMsg()
{
    // 服务端将客户端发来的数据显示到标签上
    QString data = QString::fromLocal8Bit(m_tcpSocket->readAll());
    QStringList list = data.split(" ");
    int type = list.at(0).toInt();
    int flag = list.at(1).toInt();
    switch (type)
    {
    case 1:
        if (flag == 0)
            ui->label_door->setText("");
        if (flag == 1)
            ui->label_door->setText("不要分心驾驶");
        break;
    case 2:
        if (flag == 0)
            ui->label_light->setText("");
        if (flag == 1)
            ui->label_light->setText("不要打电话");
        break;
    case 3:
        if (flag == 0)
            ui->label_lock->setText("");
        if (flag == 1)
            ui->label_lock->setText("不要吸烟");
        break;
    case 4:
        if (flag == 0)
            ui->label_airCondition->setText("");
        if (flag == 1)
            ui->label_airCondition->setText("不要瞌睡");
        break;
    case 5:
        if (flag == 0)
            ui->label_skylight->setText("");
        if (flag == 1)
            ui->label_skylight->setText("不要打搅");
        break;
    case 6:
        if (flag == 0)
            ui->label_seatAdjustment->setText("");
        if (flag == 1)
            ui->label_seatAdjustment->setText("不要看说的道理");
        break;
    default:
        break;
    }
}
