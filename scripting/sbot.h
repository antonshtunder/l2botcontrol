#ifndef SBOT_H
#define SBOT_H

#include <QObject>
#include "bot/botinstance.h"

class SBot : public QObject
{
    Q_OBJECT
public:
    explicit SBot(BotInstance *botInstance, QObject *parent = nullptr);

private:
    BotInstance *_bot;

public slots:
    void moveTo(float x, float y);
    void npcChat(int index);
    void acceptAction();
    void speakTo(int npcId);
};

#endif // SBOT_H
