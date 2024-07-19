#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void initSocket();
    void initLabel();
private slots:
    void onNewConnect();    //客户端新的连接请求处理
    void onReadMsg();       //服务端读取客户端发来的数据
private:
    Ui::MainWindow *ui;
    QTcpServer* m_tcpServer;    //tcp服务端
    QTcpSocket* m_tcpSocket;    //tcp套接字
};
#endif // MAINWINDOW_H
