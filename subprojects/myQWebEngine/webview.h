#ifndef WEBVIEW_H
#define WEBVIEW_H

#include <QWebEngineView>
#include <QMainWindow>
#include <QDebug>
class webView : public QWebEngineView
{
    Q_OBJECT
public:
    explicit webView(QWidget *parent = nullptr);
protected:
    QWebEngineView *createWindow(QWebEnginePage::WebWindowType type) override;
signals:

};

#endif // WEBVIEW_H
