#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QQuickWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    Ui::Widget *ui;
    QQuickWidget *mapWebView;
    QQuickWidget *carWebView;

    void setupWebView(QQuickWidget *quickWidget, const QString &qmlSource);

    void initWebViews();  // 新增方法
};

#endif // WIDGET_H
