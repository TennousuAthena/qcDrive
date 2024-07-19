#ifndef CARCENTER_H
#define CARCENTER_H

#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>

QT_BEGIN_NAMESPACE
namespace Ui { class carCenter; }
QT_END_NAMESPACE

class carCenter : public QMainWindow
{
    Q_OBJECT

public:
    carCenter(QWidget *parent = nullptr);
    ~carCenter();
    void initSocket();
    void initLabel();

private slots:
    void onNewConnect();    // 客户端新的连接请求处理
    void onReadMsg();       // 服务端读取客户端发来的数据

private:
    Ui::carCenter *ui;
    QTcpServer* m_tcpServer;    // tcp服务端
    QTcpSocket* m_tcpSocket;    // tcp套接字
};

#endif // CARCENTER_H
