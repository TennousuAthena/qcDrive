#ifndef MEDIA_H
#define MEDIA_H

#include <QWidget>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QAudioOutput>

namespace Ui {
class Media;
}

class Media : public QWidget
{
    Q_OBJECT

public:
    explicit Media(QWidget *parent = nullptr);
    ~Media();

private slots:
    void on_positionChanged(qint64 position);
    void on_durationChanged(qint64 duration);
    void on_positionSliderMoved(int position);

private:
    Ui::Media *ui;
    QMediaPlayer *player;
    QAudioOutput *audioOutput;
};

#endif // MEDIA_H
