#include "webview.h"

webView::webView(QWidget *parent) : QWebEngineView(parent)
{

}

QWebEngineView *webView::createWindow(QWebEnginePage::WebWindowType type)
{
    return this;
}
