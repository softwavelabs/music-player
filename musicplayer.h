#ifndef MUSICPLAYER_H
#define MUSICPLAYER_H
#include <QUrl>
#include <QDir>
#include <QDebug>
#include <QString>
#include <QObject>
#include <QFileDialog>
#include <QAudioOutput>
#include <QtMultimedia/QMediaPlayer>



class MusicPlayer : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QStringList m_files READ getFiles NOTIFY filesChanged)
    Q_PROPERTY(QString getFileName READ getFileName WRITE setFileName NOTIFY fileNameChanged)
    Q_PROPERTY(QString m_directoryPath READ getDirectoryPath WRITE setDirectoryPath NOTIFY directoryPathChanged)
    Q_PROPERTY(float playbackSpeed READ getPlaybackSpeed WRITE setPlaybackSpeed NOTIFY playbackSpeedChanged)
    Q_PROPERTY(float playbackVolume READ getPlaybackVolume WRITE setPlaybackVolume NOTIFY playbackVolumeChanged)
    Q_PROPERTY(double playbackCurrentTime READ getPlaybackCurrentTime WRITE setPlaybackCurrentTime NOTIFY playbackCurrentTimeChanged)


public:
    explicit MusicPlayer(QObject *parent = nullptr) : QObject(parent), m_mediaPlayer(new QMediaPlayer(this)) {
        m_audioOutput = new QAudioOutput();
        m_mediaPlayer->setAudioOutput(m_audioOutput);
    }
    ~MusicPlayer() {}

    Q_INVOKABLE void play();
    Q_INVOKABLE void pause();
    Q_INVOKABLE void stop();
    Q_INVOKABLE void next();
    Q_INVOKABLE void previous();
    Q_INVOKABLE void getAllFilesFromDirectory();

    enum Speed {
        Speed_0_5 = 0,
        Speed_0_75,
        Speed_1,
        Speed_1_25,
        Speed_1_5,
        Speed_1_75,
        Speed_2
    };



    Q_INVOKABLE void setPlaybackSpeed(float speed);
    Q_INVOKABLE void setPlaybackVolume(float volume);
    void setPlaybackCurrentTime(double time);
    void setDirectoryPath(const QString &directoryPath);
    Q_INVOKABLE void setFileName(const QString &fileName);

    float getPlaybackSpeed();
    float getPlaybackVolume();
    double getPlaybackCurrentTime();
    QStringList getFiles() const;

    QStringList m_files;

    Q_INVOKABLE QString getFileName() const;
    Q_INVOKABLE QString getDirectoryPath() const;



signals:
    void filesChanged();
    void playbackSpeedChanged(float speed);
    void playbackVolumeChanged(float volume);
    void labelTextChanged(const QString &newText);
    void fileNameChanged(const QString &newFileName);
    void playbackCurrentTimeChanged(double currentTime);
    void directoryPathChanged(const QString &newDirectoryPath);


private:
    Speed m_speed;
    QString m_fileName;
    QString m_directoryPath;
    QMediaPlayer *m_mediaPlayer;
    QAudioOutput *m_audioOutput;

    bool m_isMusicPlaying;
    float m_playbackSpeed = 1;
    float m_playbackVolume = 0.5;
    double m_playbackCurrentTime;
};

#endif // MUSICPLAYER_H
