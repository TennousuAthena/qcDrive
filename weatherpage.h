#ifndef WEATHERPAGE_H
#define WEATHERPAGE_H

#include <QWidget>

namespace Ui {
class WeatherPage;
}

class WeatherPage : public QWidget
{
    Q_OBJECT

public:
    explicit WeatherPage(QWidget *parent = nullptr);
    ~WeatherPage();

private:
    Ui::WeatherPage *ui;
};

#endif // WEATHERPAGE_H
