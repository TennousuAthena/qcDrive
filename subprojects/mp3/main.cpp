#include "mp3.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Mp3Window w;
    w.show();
    return a.exec();
}
