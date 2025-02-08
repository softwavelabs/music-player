#ifndef MUSICPLAYER_H
#define MUSICPLAYER_H
#include <QUrl>
#include <QDebug>
#include <QString>
#include <QObject>
#include <QFileDialog>
#include <QtMultimedia/QMediaPlayer>



class MusicPlayer : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QStringList m_files READ getFiles NOTIFY filesChanged)
    Q_PROPERTY(QString getFileName READ getFileName WRITE setFileName NOTIFY fileNameChanged)
    Q_PROPERTY(QString m_directoryPath READ getDirectoryPath WRITE setDirectoryPath NOTIFY directoryPathChanged)


public:
    explicit MusicPlayer(QObject *parent = nullptr) : QObject(parent), m_mediaPlayer(new QMediaPlayer(this)) {}
    ~MusicPlayer() {}

    Q_INVOKABLE void play();

    enum Speed {
        Speed_0_5 = 0,
        Speed_0_75,
        Speed_1,
        Speed_1_25,
        Speed_1_5,
        Speed_1_75,
        Speed_2
    };
    QStringList getFiles() const;

    void setPlaybackSpeed();
    void setPlaybackVolume();
    void setPlaybackCurrentTime();
    void setDirectoryPath(const QString &directoryPath);
    Q_INVOKABLE void setFileName(const QString &fileName);


    float getPlaybackSpeed();
    float getPlaybackVolume();
    double getPlaybackCurrentTime();
    Q_INVOKABLE void getAllFilesFromDirectory();
    Q_INVOKABLE QString getFileName() const;
    Q_INVOKABLE QString getDirectoryPath() const;

    QStringList m_files;

signals:
    void filesChanged();
    void labelTextChanged(const QString &newText);
    void fileNameChanged(const QString &newFileName);
    void directoryPathChanged(const QString &newDirectoryPath);

private:
    Speed m_speed;
    QString m_fileName;
    QString m_directoryPath;
    QMediaPlayer *m_mediaPlayer;

    bool m_isMusicPlaying;
    float m_playbackSpeed;
    float m_playbackVolume;
    double m_playbackCurrentTime;
};

#endif // MUSICPLAYER_H
