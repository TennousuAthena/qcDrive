#include <QApplication>
#include <QWebEngineView>
#include "widget.h"
#include <QCoreApplication>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_DisableHighDpiScaling);
    QCoreApplication::setAttribute(Qt::AA_UseOpenGLES);
    QApplication a(argc, argv);
    Widget w;
    w.show();
    return a.exec();
}
