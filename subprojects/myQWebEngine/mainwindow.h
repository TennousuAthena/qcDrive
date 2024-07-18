#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QWebEngineView>
#include <QWebEnginePage>
#include <QToolBar>
#include <QProgressBar>
#include <QTimer>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QFile>
#include <QTextStream>
#include <QDir>
#include <QMessageBox>
#include <QListWidget>
#include <QWebEngineHistoryItem>
#include "webview.h"




QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void doProcessSetMainPage();
    void doProcessLineEnter();
    void doProcessChangeTitle();
    void doProcessSetMyProgressBar(int p);
    void doProcessHideMyProgressBar(bool isFinished);
    void doProcessRefreshUrl(QUrl url);
    void doProcessGetWebIcon(const QUrl url);
    void doProcessSetWindowIcon();
    void doProcessShowSourceCode();
    void doProcessShowHistory();
    void doProcessGotoHistoryItem(const QModelIndex &index);

    void on_zoomInAction_triggered();
    void on_zoomOutAction_triggered();
    void on_resetZoomAction_triggered();

protected:
    void resizeEvent(QResizeEvent *event);
private:
    Ui::MainWindow *ui;

    webView * myView;
//        QWebEngineView *myView;
    QProgressBar * myProgressBar;
    QNetworkAccessManager * manager;
    QListWidget *historyList;

    void Init();
    void setMyToolBar();
    void loadMainPage();
};
#endif // MAINWINDOW_H
