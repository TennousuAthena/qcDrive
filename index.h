#ifndef INDEX_H
#define INDEX_H

#include <QWidget>
#include <QQuickWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class IndexWidget; }
class Dashboard;
QT_END_NAMESPACE

class IndexWidget : public QWidget
{
    Q_OBJECT

public:
    explicit IndexWidget(QWidget *parent = nullptr);
    ~IndexWidget();

    void showMp3WindowFromDashboard(); // 新增的方法

private:
    Ui::IndexWidget *ui;
    Dashboard *dashboard;
    QQuickWidget *mapWebView;
    QQuickWidget *carWebView;

    void setupWebView(QQuickWidget *quickWidget, const QString &qmlSource);
    void initWebViews();  // 新增方法

private slots:
    void showMp3Window();
};

#endif // INDEX_H
