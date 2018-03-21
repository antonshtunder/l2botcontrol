#include "sbot.h"
#include "misc/utils.h"

SBot::SBot(BotInstance *botInstance, QObject *parent):
    QObject(parent),
    _bot(botInstance)
{

}

void SBot::moveTo(float x, float y)
{
    _bot->forceMoveTo(x, y, 100.0f);
}

void SBot::npcChat(int index)
{
    _bot->npcChat(index);
}

void SBot::acceptAction()
{
    _bot->acceptAction();
}

void SBot::speakTo(int npcId)
{
    _bot->speakTo(npcId);
}
