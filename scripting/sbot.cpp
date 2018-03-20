#include "sbot.h"
#include "misc/utils.h"

SBot::SBot(BotInstance *botInstance, QObject *parent):
    QObject(parent),
    _bot(botInstance)
{

}

void SBot::moveTo(float x, float y)
{
    QPointF moveToLoc(x, y);
    _bot->moveTo(x, y);
    while(getDistance(moveToLoc, {_bot->l2representation.character.x, _bot->l2representation.character.y}) > 100.0f)
    {
        Sleep(50);
    }
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
