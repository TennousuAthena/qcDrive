#include "media.h"
#include "ui_media.h"
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QFileDialog>
#include <QStyle>
#include <QAudioOutput>

Media::Media(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Media),
    player(new QMediaPlayer(this)),
    audioOutput(new QAudioOutput(this))
{
    ui->setupUi(this);

    // Setup video widget
    player->setVideoOutput(ui->videoWidget);

    // Setup audio output
    player->setAudioOutput(audioOutput);

    // Load video from resources
    player->setSource(QUrl("https://file-cdn.qmcmc.cn/playback/bedwars.mp4"));

    // Connect buttons to player slots
    connect(ui->playButton, &QPushButton::clicked, player, &QMediaPlayer::play);
    connect(ui->pauseButton, &QPushButton::clicked, player, &QMediaPlayer::pause);

    // Connect slider to player position
    connect(player, &QMediaPlayer::positionChanged, this, &Media::on_positionChanged);
    connect(player, &QMediaPlayer::durationChanged, this, &Media::on_durationChanged);
    connect(ui->positionSlider, &QSlider::sliderMoved, this, &Media::on_positionSliderMoved);

    // Connect volume controls
    connect(ui->volumeSlider, &QSlider::valueChanged, audioOutput, &QAudioOutput::setVolume);
    ui->volumeSlider->setValue(audioOutput->volume() * 100);  // Set initial volume slider value
}

Media::~Media()
{
    delete ui;
}

void Media::on_positionChanged(qint64 position)
{
    ui->positionSlider->setValue(position);
}

void Media::on_durationChanged(qint64 duration)
{
    ui->positionSlider->setRange(0, duration);
}

void Media::on_positionSliderMoved(int position)
{
    player->setPosition(position);
}
