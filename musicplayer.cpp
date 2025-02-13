#include "musicplayer.h"

void MusicPlayer::setFileName(const QString &fileName)
{
    if (m_fileName != fileName) {
        m_fileName = fileName;
        emit fileNameChanged(m_fileName);
    }
}

void MusicPlayer::setDirectoryPath(const QString &directoryPath)
{
    if (m_directoryPath != directoryPath) {
        m_directoryPath = directoryPath;
        emit directoryPathChanged(m_directoryPath);
    }
}


void MusicPlayer::play()
{
    if (m_files.isEmpty()) {
        qDebug() << "No files to play.";
        return;
    }

    if (m_fileName.isEmpty()) {
        setFileName(m_files.first());
    }

    QString absolutePath = QDir(m_directoryPath).filePath(m_fileName);

    if (!QFile::exists(absolutePath)) {
        qDebug() << "File does not exist: " << absolutePath;
        return;
    }

    m_mediaPlayer->setSource(QUrl::fromLocalFile(absolutePath));
    m_mediaPlayer->play();
    m_isMusicPlaying = true;

    qDebug() << "Playing: " << absolutePath;
}


void MusicPlayer::pause()
{
    if (m_isMusicPlaying) {
        m_mediaPlayer->pause();
        m_isMusicPlaying = false;
        qDebug() << "Music paused.";
    } else {
        m_mediaPlayer->play();
        m_isMusicPlaying = true;
        qDebug() << "Music playing";
    }
}

void MusicPlayer::stop()
{
    if (m_isMusicPlaying) {
        m_mediaPlayer->stop();
        m_isMusicPlaying = false;
        qDebug() << "Music stopped.";
    }
}

void MusicPlayer::next()
{
    int currentIndex = m_files.indexOf(m_fileName);
    if (currentIndex != -1 && currentIndex < m_files.size() - 1) {
        setFileName(m_files[currentIndex + 1]);
        play();
    } else {
        qDebug() << "No next file.";
    }
}

void MusicPlayer::previous()
{
    int currentIndex = m_files.indexOf(m_fileName);
    if (currentIndex > 0) {
        setFileName(m_files[currentIndex - 1]);
        play();
    } else {
        qDebug() << "No previous file.";
    }
}

void MusicPlayer::setPlaybackSpeed(float speed)
{
    m_playbackSpeed = speed;
    m_mediaPlayer->setPlaybackRate(m_playbackSpeed);
    emit playbackSpeedChanged(m_playbackSpeed);
}

void MusicPlayer::setPlaybackVolume(float volume)
{
    m_playbackVolume = volume;
    if (m_audioOutput) {
        m_audioOutput->setVolume(m_playbackVolume);
    }
    emit playbackVolumeChanged(m_playbackVolume);
}

void MusicPlayer::setPlaybackCurrentTime(double time)
{
    m_playbackCurrentTime = time;
    m_mediaPlayer->setPosition(static_cast<qint64>(m_playbackCurrentTime * 1000));
    emit playbackCurrentTimeChanged(m_playbackCurrentTime);
}

void MusicPlayer::getAllFilesFromDirectory()
{
    QStringList fileNames;

    QString dirPath;

    dirPath = QFileDialog::getExistingDirectory(
        nullptr,
        "Select Folder",
        "/Users/anath/Music/Music/Media.localized/Music", // my path with music, for now, to simpler testing
        QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks
        );

    if (!dirPath.isEmpty()) {
        QDir dir(dirPath);
        fileNames = dir.entryList(QStringList() << "*.mp3" << "*.wav" << "*.flac", QDir::Files);
        qDebug() << "Files from folder:" << fileNames;
    }

    setDirectoryPath(dirPath);
    m_files = fileNames;
    emit filesChanged();
}

QStringList MusicPlayer::getFiles() const { return m_files; }

QString MusicPlayer::getFileName() const { return m_fileName; }

QString MusicPlayer::getDirectoryPath() const { return m_directoryPath; }

float MusicPlayer::getPlaybackSpeed() { return m_playbackSpeed; }

float MusicPlayer::getPlaybackVolume() { return m_playbackVolume; }

double MusicPlayer::getPlaybackCurrentTime() { return m_playbackCurrentTime; }
