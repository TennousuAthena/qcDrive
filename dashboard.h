#ifndef DASHBOARD_H
#define DASHBOARD_H

#include <QWidget>
#include <QStackedWidget>

namespace Ui {
class Dashboard;
}

class IndexWidget;  // 前向声明

class Dashboard : public QWidget
{
    Q_OBJECT

public:
    explicit Dashboard(QWidget *parent = nullptr);
    ~Dashboard();

    QStackedWidget* getStackedWidget(); // 获取stackedWidget的方法
    IndexWidget* getIndexWidget();      // 获取IndexWidget的方法

private slots:
    void showMp3Window();
    void showIndexWidget();
    void showBrowser();
    void showMaps();
    void showMedia();
    void showCenter();

private:
    Ui::Dashboard *ui;
};

#endif // DASHBOARD_H
