#ifndef CARCONTROL_H
#define CARCONTROL_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QHostAddress>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class carControl; }
QT_END_NAMESPACE

class carControl : public QMainWindow
{
    Q_OBJECT

public:
    carControl(QWidget *parent = nullptr);
    ~carControl();
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
    Ui::carControl *ui;
    QTcpSocket *socket;
};

#endif // CARCONTROL_H
