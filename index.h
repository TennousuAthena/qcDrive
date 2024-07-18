#ifndef INDEX_H
#define INDEX_H

#include <QWidget>
#include <QQuickWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class IndexWidget; }
QT_END_NAMESPACE

class IndexWidget : public QWidget
{
    Q_OBJECT

public:
    explicit IndexWidget(QWidget *parent = nullptr);
    ~IndexWidget();

private:
    Ui::IndexWidget *ui;
    QQuickWidget *mapWebView;
    QQuickWidget *carWebView;

    void setupWebView(QQuickWidget *quickWidget, const QString &qmlSource);

    void initWebViews();  // 新增方法
};

#endif // INDEX_H
