#ifndef AUDIOPLAYER_H
#define AUDIOPLAYER_H

#include <QMediaPlayer>

class AudioPlayer
{
public:
    AudioPlayer();

    void playAlert();

private:
    QMediaPlayer _alertPlayer;
};

#endif // AUDIOPLAYER_H
