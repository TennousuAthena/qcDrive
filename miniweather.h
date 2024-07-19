#ifndef MINIWEATHER_H
#define MINIWEATHER_H

#include <QWidget>

namespace Ui {
class miniWeather;
}

class miniWeather : public QWidget
{
    Q_OBJECT

public:
    explicit miniWeather(QWidget *parent = nullptr);
    ~miniWeather();

private:
    Ui::miniWeather *ui;
};

#endif // MINIWEATHER_H
