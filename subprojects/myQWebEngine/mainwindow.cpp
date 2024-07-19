#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Init();
}


MainWindow::~MainWindow()
{
    delete ui;
}


/****************** SLOT（数字对应功能） ****************/
//0.设置主页
void MainWindow::doProcessSetMainPage()
{
    QFile *myFile = new QFile;
    bool isOPen = false;
    if(!isOPen){

    }
    else{
        QTextStream out(myFile);
        out<<QString("mainPage=").append(ui->urlEdit->text());
        myFile->close();
        QMessageBox::information(this,"Info","设置成功，重启浏览器生效");
    }
    delete  myFile;
    myFile = NULL;
}
//1.转到当前链接
void MainWindow::doProcessLineEnter()
{
    QString str = ui->urlEdit->text();
    myView->load(QUrl(str));//加载网页
    myView->setFocus();//获取焦点
}
//2.修改窗口标题
void MainWindow::doProcessChangeTitle()
{
//    qDebug()<<"当前标题"<<myView->title();
    this->setWindowTitle(myView->title());
}
//3.设置进度条
void MainWindow::doProcessSetMyProgressBar(int p)
{
    myProgressBar->show();
    myProgressBar->setValue(p);
    myProgressBar->setFixedWidth(this->width());
}
//3.隐藏进度条
void MainWindow::doProcessHideMyProgressBar(bool isFinished)
{
    if(!isFinished){
        //出错了
        this->setWindowTitle("Page Error");
        return;
    }
    QTimer *myTimer = new QTimer(this);
    connect(myTimer,&QTimer::timeout,[=](){
        myTimer->stop();
        myProgressBar->hide();
    });
    myTimer->start(3000);//停留3s后隐藏
}
//4.刷新网页url
void MainWindow::doProcessRefreshUrl(QUrl url)
{
    ui->urlEdit->setText(url.toString());
}
//6. 发送网络请求  获取网页相应图标
void MainWindow::doProcessGetWebIcon(const QUrl url)
{
    QNetworkRequest myIconRequest(url);
//    qDebug()<<"网站图标网址为:"<<url;
    QNetworkReply *myIconReply = manager->get(myIconRequest);
    myIconReply->setParent(this);
    connect(myIconReply,SIGNAL(finished()),this,SLOT(doProcessSetWindowIcon()));
}
//6. 网络请求返回成功与否，均设置icon
void MainWindow::doProcessSetWindowIcon()
{
    QIcon icon;
    QNetworkReply *webReply = qobject_cast<QNetworkReply *>(sender());//获取信号发送的指针对象
    if(webReply&&webReply->error()==QNetworkReply::NoError){
        QByteArray daIcon = webReply->readAll();
        QPixmap iconPix;
//        QPixmap iconPix(daIcon);//这个构造不行
        iconPix.loadFromData(daIcon);//数据做转换，先转成pixmap格式
        icon.addPixmap(iconPix);//在通过icon的构造转成icon格式
        webReply->deleteLater();
    }
    else{
//        qDebug()<<"网络出错"<<webReply->error();
        icon = QIcon(":/res/webIcon.png");
        webReply->deleteLater();

    }
    setWindowIcon(icon);
}
//8.显示网页源代码
void MainWindow::doProcessShowSourceCode()
{
    myView->page()->triggerAction(QWebEnginePage::ViewSource);
}
//9.显示历史记录列表
void MainWindow::doProcessShowHistory()
{
    historyList->clear();
    foreach(QWebEngineHistoryItem item, myView->history()->items()) {
        QListWidgetItem *history = new QListWidgetItem(item.title());
        history->setData(Qt::UserRole, item.url().toString());
        historyList->addItem(history);
    }
    historyList->show();
}

//转到历史记录项
void MainWindow::doProcessGotoHistoryItem(const QModelIndex &index)
{
    QListWidgetItem *item = historyList->item(index.row());
    QString url = item->data(Qt::UserRole).toString();
    myView->load(QUrl(url));
}


/****************** System Slots ****************/
//窗口变化事件捕捉
void MainWindow::resizeEvent(QResizeEvent *event)
{
    if(myProgressBar->isVisible()){
        //已经隐藏
        return;
    }
    else{
        myProgressBar->setFixedWidth(this->width());
    }
}
//7.放大页面 快捷键ctrl++
void MainWindow::on_zoomInAction_triggered()
{
    myView->setZoomFactor(myView->zoomFactor()+0.1);
    ui->statusbar->showMessage(tr("放大 %1%").arg(myView->zoomFactor()*100));
}
//7.缩小页面 快捷键ctrl+-
void MainWindow::on_zoomOutAction_triggered()
{
    myView->setZoomFactor(myView->zoomFactor()-0.1);
    ui->statusbar->showMessage(tr("缩小 %1%").arg(myView->zoomFactor()*100));
}
//7.还原页面 快捷键ctrl+0
void MainWindow::on_resetZoomAction_triggered()
{
    myView->setZoomFactor(1.0);
    ui->statusbar->showMessage(tr("还原 %1%").arg(myView->zoomFactor()*100));
}

/****************** My Function ****************/
void MainWindow::Init()
{
//    myView = new QWebEngineView(this);
    myView = new webView(this);
    ui->gridLayout->addWidget(myView); //添加到布局中
    //连接各界面信号执行相关动作
    //0.加载主页 并修改主页
    this->loadMainPage();
    connect(ui->setMainPageAction,SIGNAL(triggered()),this,SLOT(doProcessSetMainPage()));
    // 1.接受lineEdit回车按钮信号或者“转到”按钮，执行显示当前网址操作
    connect(ui->urlEdit,SIGNAL(returnPressed()),this,SLOT(doProcessLineEnter()));//回车键转到链接
    connect(ui->gotoBtn,SIGNAL(clicked()),this,SLOT(doProcessLineEnter()));
    // 2.接受webEngineView的titleChange信号，执行修改窗口标题操作
    connect(myView,&QWebEngineView::titleChanged,this,&MainWindow::doProcessChangeTitle);//修改title
    // 3.添加进度条，接受loadProgress信号，显示当前进度，任务结束后，接受loadFinish信号，隐藏进度条 */
    myProgressBar = new QProgressBar(ui->statusbar);//将进度条放在状态栏中
    // myProgressBar->setStyleSheet("QProgressBar{background-color:#05B8CC;width:20px;"
                                 // "border:2px solid grey;border-radius:5px;text-align:center;}");
    connect(myView,&QWebEngineView::loadProgress,this,&MainWindow::doProcessSetMyProgressBar);//获取中
//    connect(QWebEngineView,SIGNAL(loadProgress)) 注意此写法再次不支持，可能是QWebEngineView是qt5.5后出来的模块
    connect(myView,&QWebEngineView::loadFinished,this,&MainWindow::doProcessHideMyProgressBar);//获取完成
    //4.网页改变时，刷新url值到网址栏中
    connect(myView,&QWebEngineView::urlChanged,this,&MainWindow::doProcessRefreshUrl);
    //5.添加界面中工具栏,并添加导航工具进工具栏
    setMyToolBar();
    //6.获取并显示网站图标
    manager = new QNetworkAccessManager(this);
    connect(myView,&QWebEngineView::iconUrlChanged,this,&MainWindow::doProcessGetWebIcon);
    //7.实现网页缩放，见转到槽 范围是0.25~500
    //8.查看网页源代码
    connect(ui->soucreCodeAction,SIGNAL(triggered()),this,SLOT(doProcessShowSourceCode()));
    //9.显示历史记录
    historyList = new QListWidget();
    historyList->setWindowTitle("历史记录");
    historyList->setMinimumWidth(300);
    connect(ui->historyAction,SIGNAL(triggered()),this,SLOT(doProcessShowHistory()));
    connect(historyList, &QListWidget::doubleClicked, this, &MainWindow::doProcessGotoHistoryItem);

}


//5.设置带导航栏功能的工具栏
void MainWindow::setMyToolBar()
{
    QToolBar *toolBar = new QToolBar(this);//将工具栏放入窗口中
    addToolBar(Qt::TopToolBarArea,toolBar);//调整默认放在上面
    toolBar->setAllowedAreas(Qt::LeftToolBarArea);//只允许上停靠
    toolBar->setFloatable(false);//不允许浮动
    toolBar->setMovable(false);//关闭移动  总开关
    //pageAction将返回webEngineView的Action
    toolBar->addAction(myView->pageAction(QWebEnginePage::Back));//后退
    toolBar->addAction(myView->pageAction(QWebEnginePage::Forward));//前进
    toolBar->addAction(myView->pageAction(QWebEnginePage::Reload));//刷新
    toolBar->addAction(myView->pageAction(QWebEnginePage::Stop));//停止
    toolBar->addWidget(ui->urlEdit);//添加网址到工具栏
    toolBar->addWidget(ui->gotoBtn);//添加按钮到工具栏
}
//0.加载主页
void MainWindow::loadMainPage()
{
    QFile *myFile = new QFile;
    bool isOPen = false;

    if(!isOPen){
        myView->load(QUrl("https://limestart.cn/"));//加载网页
        myView->setFocus();//获取焦点
    }
    else{
        QTextStream in(myFile);
        myView->load(QUrl(in.readLine().split("=").at(1)));//加载网页
        myView->setFocus();//获取焦点
        myFile->close();
    }
    delete  myFile;
    myFile = NULL;
}




