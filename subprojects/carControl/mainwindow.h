#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QHostAddress>
#include <QMessageBox>
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
    void initButton();
private slots:
    void on_pushButton_Door_clicked();

    void on_pushButton_Light_clicked();

    void on_pushButton_lock_clicked();

    void on_pushButton_airCondition_clicked();

    void on_pushButton_skylight_clicked();

    void on_pushButton_seatAdjustment_clicked();

private:
    Ui::MainWindow *ui;
    QTcpSocket *socket;
};
#endif // MAINWINDOW_H
