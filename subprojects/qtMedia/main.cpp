#include "media.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Media w;
    w.show();
    return a.exec();
}
