#include "mp3.h"
#include "ui_mp3.h"
#include <QFileDialog>
#include <QListWidgetItem>
#include <QTime>
#include <QDir>
#include <QPixmap>
#include <QFile>
#include <QTextStream>
#include <QRegularExpression>

Mp3Window::Mp3Window(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Mp3Window)
    , player(new QMediaPlayer(this))
    , audioOutput(new QAudioOutput(this))
    , currentIndex(-1)
{
    ui->setupUi(this);

    // 设置样式表
    QString styleSheet =
        "QMainWindow { background-color: #d3d3d3; }"
        "QPushButton { background-color: transparent; border: none; }"
        "QPushButton#prevButton, QPushButton#playPauseButton, QPushButton#nextButton, QPushButton#volumeButton, QPushButton#fileButton {"
        "   border: none;"
        "   padding: 10px;"
        "}"
        "QSlider::groove:horizontal { height: 6px; background: #bbb; }"
        "QSlider::handle:horizontal { background: white; border: 1px solid #0059b3; width: 18px; margin: -5px 0; border-radius: 9px; }"
        "QListWidget { background-color: #d3d3d3; color: black; border: 1px solid #aaa; }"
        "QListWidget::item { padding: 5px; }"
        "QListWidget::item:selected { background-color: #aaa; }"
        "QMenuBar { background-color: #d3d3d3; color: black; }"
        "QMenuBar::item { background-color: #d3d3d3; color: black; }"
        "QMenuBar::item:selected { background-color: #aaa; }"
        "QStatusBar { background-color: #d3d3d3; color: black; }";

    this->setStyleSheet(styleSheet);

    // 设置按钮图标
    ui->playPauseButton->setIcon(QIcon(":/new/prefix1/play.png"));
    ui->playPauseButton->setIconSize(QSize(64, 64));
    ui->prevButton->setIcon(QIcon(":/new/prefix1/previous.png"));
    ui->prevButton->setIconSize(QSize(48, 48));
    ui->nextButton->setIcon(QIcon(":/new/prefix1/next.png"));
    ui->nextButton->setIconSize(QSize(48, 48));
    ui->volumeButton->setIcon(QIcon(":/new/prefix1/volume.png"));
    ui->volumeButton->setIconSize(QSize(48, 48));
    ui->fileButton->setIcon(QIcon(":/new/prefix1/file.png"));
    ui->fileButton->setIconSize(QSize(48, 48));

    player->setAudioOutput(audioOutput);
    audioOutput->setVolume(0.5); // 设置初始音量为 50%

    connect(ui->fileButton, &QPushButton::clicked, this, &Mp3Window::openFiles); // 添加文件按钮的连接
    connect(ui->playPauseButton, &QPushButton::clicked, this, &Mp3Window::togglePlayPause);
    connect(ui->nextButton, &QPushButton::clicked, this, &Mp3Window::next);
    connect(ui->prevButton, &QPushButton::clicked, this, &Mp3Window::previous);
    connect(ui->volumeButton, &QPushButton::clicked, this, &Mp3Window::toggleVolumeSlider);
    connect(ui->volumeSlider, &QSlider::valueChanged, this, &Mp3Window::changeVolume);
    connect(ui->playlistWidget, &QListWidget::itemClicked, this, &Mp3Window::handlePlaylistClick);

    connect(player, &QMediaPlayer::playbackStateChanged, this, &Mp3Window::mediaStateChanged);
    connect(player, &QMediaPlayer::mediaStatusChanged, this, &Mp3Window::mediaStatusChanged);
    connect(player, &QMediaPlayer::positionChanged, this, &Mp3Window::updatePosition);
    connect(player, &QMediaPlayer::durationChanged, this, &Mp3Window::updateDuration);
    connect(ui->progressSlider, &QSlider::sliderMoved, this, &Mp3Window::setPosition);

    QAction *openAction = new QAction("&Open", this);
    connect(openAction, &QAction::triggered, this, &Mp3Window::openFiles);

    QMenu *fileMenu = menuBar()->addMenu("&File");
    fileMenu->addAction(openAction);
}

Mp3Window::~Mp3Window()
{
    delete ui;
}

void Mp3Window::openFiles()
{
    QStringList files = QFileDialog::getOpenFileNames(this, "Open Files", QString(), "Audio Files (*.mp3)");
    for (const QString &file : files) {
        mediaFiles.append(file);

        QListWidgetItem *item = new QListWidgetItem(QFileInfo(file).fileName());
        ui->playlistWidget->addItem(item);

        qDebug() << "Added file:" << file;
    }
}

void Mp3Window::play()
{
    if (currentIndex < 0 && !mediaFiles.isEmpty()) {
        currentIndex = 0;
        QString mediaFile = mediaFiles.at(currentIndex);
        qDebug() << "Setting media file:" << mediaFile;
        player->setSource(QUrl::fromLocalFile(mediaFile));
        updateImageLabelText(mediaFile);
        updateCoverImage(mediaFile);
        loadLyrics(mediaFile);
    }
    qDebug() << "Playing media";
    player->play();
    ui->playPauseButton->setIcon(QIcon(":/new/prefix1/pause.png"));
}

void Mp3Window::pause()
{
    qDebug() << "Pausing media";
    player->pause();
    ui->playPauseButton->setIcon(QIcon(":/new/prefix1/play.png"));
}

void Mp3Window::togglePlayPause()
{
    if (player->playbackState() == QMediaPlayer::PlayingState) {
        pause();
    } else {
        play();
    }
}

void Mp3Window::next()
{
    if (currentIndex + 1 < mediaFiles.size()) {
        currentIndex++;
        QString mediaFile = mediaFiles.at(currentIndex);
        qDebug() << "Next media file:" << mediaFile;
        player->setSource(QUrl::fromLocalFile(mediaFile));
        player->play();
        updateImageLabelText(mediaFile);
        updateCoverImage(mediaFile);
        loadLyrics(mediaFile);
        ui->playPauseButton->setIcon(QIcon(":/new/prefix1/pause.png"));
    }
}

void Mp3Window::previous()
{
    if (currentIndex - 1 >= 0) {
        currentIndex--;
        QString mediaFile = mediaFiles.at(currentIndex);
        qDebug() << "Previous media file:" << mediaFile;
        player->setSource(QUrl::fromLocalFile(mediaFile));
        player->play();
        updateImageLabelText(mediaFile);
        updateCoverImage(mediaFile);
        loadLyrics(mediaFile);
        ui->playPauseButton->setIcon(QIcon(":/new/prefix1/pause.png"));
    }
}

void Mp3Window::toggleVolumeSlider()
{
    bool visible = ui->volumeSlider->isVisible();
    ui->volumeSlider->setVisible(!visible);
    ui->volumeSlider->raise();  // 将音量滑块置于顶层

    if (visible) {
        ui->volumeSlider->setGeometry(QRect(ui->volumeButton->x(), ui->volumeButton->y(), 0, 0));
    } else {
        int sliderWidth = this->width() / 2;
        int sliderX = (this->width() - sliderWidth) / 2;
        ui->volumeSlider->setGeometry(sliderX, 0, sliderWidth, 30);  // 将音量滑块移到窗口顶部并居中显示，占据屏幕宽度的一半
    }
}

void Mp3Window::changeVolume(int value)
{
    audioOutput->setVolume(value / 100.0);
}

void Mp3Window::mediaStateChanged(QMediaPlayer::PlaybackState state)
{
    qDebug() << "Media state changed:" << state;
    if (state == QMediaPlayer::StoppedState && currentIndex + 1 < mediaFiles.size()) {
        next();
    }
}

void Mp3Window::mediaStatusChanged(QMediaPlayer::MediaStatus status)
{
    qDebug() << "Media status changed:" << status;
    if (status == QMediaPlayer::EndOfMedia && currentIndex + 1 < mediaFiles.size()) {
        next();
    }
}

void Mp3Window::handlePlaylistClick(QListWidgetItem *item)
{
    currentIndex = ui->playlistWidget->row(item);
    QString mediaFile = mediaFiles.at(currentIndex);
    qDebug() << "Clicked media file:" << mediaFile;
    player->setSource(QUrl::fromLocalFile(mediaFile));
    player->play();
    updateImageLabelText(mediaFile);
    updateCoverImage(mediaFile);
    loadLyrics(mediaFile);
    ui->playPauseButton->setIcon(QIcon(":/new/prefix1/pause.png"));
}

void Mp3Window::updatePosition(qint64 position)
{
    ui->progressSlider->setValue(static_cast<int>(position));
    QTime currentTime((position / 3600000) % 60, (position / 60000) % 60, (position / 1000) % 60);
    ui->currentTimeLabel->setText(currentTime.toString("mm:ss"));

    // 更新歌词
    updateLyrics(position);
}

void Mp3Window::updateDuration(qint64 duration)
{
    ui->progressSlider->setRange(0, static_cast<int>(duration));
    QTime totalTime((duration / 3600000) % 60, (duration / 60000) % 60, (duration / 1000) % 60);
    ui->totalTimeLabel->setText(totalTime.toString("mm:ss"));
}

void Mp3Window::setPosition(int position)
{
    player->setPosition(position);
}

void Mp3Window::updateImageLabelText(const QString &filePath)
{
    QString songTitle = formatSongTitle(filePath);
    ui->imageLabel->setText(songTitle);
    ui->imageLabel->setAlignment(Qt::AlignCenter); // 设置文本居中对齐
    QFont font = ui->imageLabel->font();
    font.setPointSize(36); // 设置字体大小
    font.setItalic(true); // 设置斜体
    font.setBold(true); // 设置加粗
    ui->imageLabel->setFont(font);
    ui->imageLabel->setStyleSheet("QLabel { color: black; }"); // 设置文本颜色
}

void Mp3Window::updateCoverImage(const QString &filePath)
{
    // 这里假设封面图片与音频文件同名但扩展名为 .jpg
    QString coverImagePath = filePath;
    coverImagePath.replace(".mp3", ".jpg");

    if (QFile::exists(coverImagePath)) {
        QPixmap coverPixmap(coverImagePath);
        qDebug() << "Loading cover image:" << coverImagePath;
        ui->vinylLabel->setPixmap(coverPixmap.scaled(ui->vinylLabel->size(), Qt::KeepAspectRatio));
    } else {
        qDebug() << "Cover image not found:" << coverImagePath;
        ui->vinylLabel->clear();
    }
}

QString Mp3Window::formatSongTitle(const QString &filePath)
{
    // 这里假设文件名是 "artist - title.mp3" 格式，你可以根据需要调整
    QString baseName = QFileInfo(filePath).completeBaseName();
    QStringList parts = baseName.split(" - ");
    if (parts.size() == 2) {
        QString artist = parts[0];
        QString title = parts[1];
        return QString("%1\n%2").arg(artist).arg(title);
    }
    return baseName; // 如果没有分割符，则直接返回基本名称
}

void Mp3Window::loadLyrics(const QString &filePath)
{
    lyricsMap.clear();
    QString lyricsFilePath = filePath;
    lyricsFilePath.replace(".mp3", ".lrc");

    if (QFile::exists(lyricsFilePath)) {
        QFile lyricsFile(lyricsFilePath);
        if (lyricsFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(&lyricsFile);
            while (!in.atEnd()) {
                QString line = in.readLine();
                QRegularExpression regex("\\[(\\d+):(\\d+).(\\d+)\\](.*)");
                QRegularExpressionMatch match = regex.match(line);
                if (match.hasMatch()) {
                    int minutes = match.captured(1).toInt();
                    int seconds = match.captured(2).toInt();
                    int milliseconds = match.captured(3).toInt();
                    QString text = match.captured(4);
                    qint64 time = minutes * 60000 + seconds * 1000 + milliseconds * 10;
                    lyricsMap[time] = text;
                }
            }
        }
    }

    if (!lyricsMap.isEmpty()) {
        updateLyrics(0);
    } else {
        ui->coverLabel->clear();
    }
}

void Mp3Window::updateLyrics(qint64 position)
{
    qint64 closestTime = -1;
    foreach (qint64 time, lyricsMap.keys()) {
        if (time <= position) {
            closestTime = time;
        } else {
            break;
        }
    }

    if (closestTime != -1) {
        ui->coverLabel->setText(lyricsMap[closestTime]);
        ui->coverLabel->setAlignment(Qt::AlignCenter); // 设置文本居中对齐
        QFont font = ui->coverLabel->font();
        font.setPointSize(18); // 设置字体大小
        font.setItalic(true); // 设置斜体
        ui->coverLabel->setFont(font);
        ui->coverLabel->setStyleSheet("QLabel { color: black; }"); // 设置文本颜色
    } else {
        ui->coverLabel->clear();
    }
}
