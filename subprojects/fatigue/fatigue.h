#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>
#include <QFileDialog>
#include <QMediaPlayer>
#include <QFileDialog>
#include <QSlider>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    void open_port(
            QString name,QString baud,
            QString stop,QString data,QString parity);
    QList<QSerialPortInfo> get_port(void);
    void close_port(void);
    void receive_data(void);
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

private:
    QSerialPort *serial;
private:
    Ui::Widget *ui;
        QMediaPlayer *player;
};
#endif // WIDGET_H
