#ifndef MAPB_H
#define MAPB_H

#include <QMainWindow>
#include <QWebEngineView>

QT_BEGIN_NAMESPACE
namespace Ui { class MapB; }
QT_END_NAMESPACE

class MapB : public QMainWindow
{
    Q_OBJECT

public:
    MapB(QWidget *parent = nullptr);
    ~MapB();

private:
    Ui::MapB *ui;

};

#endif // MAPB_H
