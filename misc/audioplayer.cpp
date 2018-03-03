#include "audioplayer.h"
#include <QFile>

AudioPlayer::AudioPlayer()
{
    _alertPlayer.setMedia(QUrl("C:/l2data/alert.mp3"));
    qDebug() << _alertPlayer.error();
    _alertPlayer.setVolume(50);
}

void AudioPlayer::playAlert()
{
    if(_alertPlayer.state() != QMediaPlayer::PlayingState)
    {
        _alertPlayer.play();
    }
}
