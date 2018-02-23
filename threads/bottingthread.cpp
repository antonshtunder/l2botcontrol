#include "bottingthread.h"
#include "botinstance.h"

#define PICKUP_RADIUS 400.0

BottingThread::BottingThread(BotInstance *botInstance)
{
    _bot = botInstance;
    botInstance->moveToThread(this);
}

void BottingThread::stopBotting()
{
    _botting = false;
}

bool BottingThread::isBotting()
{
    return _botting;
}

void BottingThread::run()
{
    qDebug() << "started botting";
    _botting = true;
    while(_botting)
    {
        auto mob = _bot->focusNextMob();
        qDebug() << "new mob id = " << (LPVOID)mob.id;
        if(mob.id == 0)
        {
            msleep(100);
            continue;
        }
        while(true)
        {
            if(!_botting)
                break;
            msleep(200);
            _bot->attack();
            if(_bot->isDead(mob.address) == l2ipc::Command::REPLY_YES)
            {
                _bot->pickupInRadius(PICKUP_RADIUS);
                break;
            }
        }
    }
}
