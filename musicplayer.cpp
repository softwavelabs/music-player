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

}

void MusicPlayer::setPlaybackSpeed()
{
    switch (m_speed) {
    case Speed_0_5: m_playbackSpeed = 0.5f; break;
    case Speed_0_75: m_playbackSpeed = 0.75f; break;
    case Speed_1: m_playbackSpeed = 1.0f; break;
    case Speed_1_25: m_playbackSpeed = 1.25f; break;
    case Speed_1_5: m_playbackSpeed = 1.5f; break;
    case Speed_1_75: m_playbackSpeed = 1.75f; break;
    case Speed_2: m_playbackSpeed = 2.0f; break;
    }
    m_mediaPlayer->setPlaybackRate(m_playbackSpeed);
}

void MusicPlayer::setPlaybackVolume()
{

}

void MusicPlayer::setPlaybackCurrentTime()
{

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
