#ifndef DASHBOARD_H
#define DASHBOARD_H

#include <QWidget>

namespace Ui {
class Dashboard;
}

class Dashboard : public QWidget
{
    Q_OBJECT

public:
    explicit Dashboard(QWidget *parent = nullptr);
    ~Dashboard();

private slots:
    void showIndexWidget();
    void showMp3Window();
    void showBrowser();
    void showMaps();
    void showMedia();
    void showControl();

private:
    Ui::Dashboard *ui;
};

#endif // DASHBOARD_H
