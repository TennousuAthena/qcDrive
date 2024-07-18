#ifndef MP3WINDOW_H
#define MP3WINDOW_H

#include <QMainWindow>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QListWidgetItem>
#include <QMap>
#include <QString>

QT_BEGIN_NAMESPACE
namespace Ui { class Mp3Window; }
QT_END_NAMESPACE

class Mp3Window : public QMainWindow
{
    Q_OBJECT

public:
    Mp3Window(QWidget *parent = nullptr);
    ~Mp3Window();

private slots:
    void openFiles();
    void play();
    void pause();
    void togglePlayPause();
    void next();
    void previous();
    void toggleVolumeSlider();
    void changeVolume(int value);
    void mediaStateChanged(QMediaPlayer::PlaybackState state);
    void mediaStatusChanged(QMediaPlayer::MediaStatus status);
    void handlePlaylistClick(QListWidgetItem *item);
    void updatePosition(qint64 position);
    void updateDuration(qint64 duration);
    void setPosition(int position);
    void updateImageLabelText(const QString &filePath);
    void updateCoverImage(const QString &filePath);
    void loadLyrics(const QString &filePath);
    void updateLyrics(qint64 position);

private:
    Ui::Mp3Window *ui;
    QMediaPlayer *player;
    QAudioOutput *audioOutput;
    QList<QString> mediaFiles;
    int currentIndex;
    QMap<qint64, QString> lyricsMap;
    QString formatSongTitle(const QString &filePath);
};

#endif // MP3WINDOW_H
