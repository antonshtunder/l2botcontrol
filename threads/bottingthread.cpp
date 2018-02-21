#include "bottingthread.h"
#include "botinstance.h"

#define PICKUP_RADIUS 250.0

BottingThread::BottingThread(BotInstance *botInstance)
{
    _bot = botInstance;
}

void BottingThread::stopBotting()
{
    botting = false;
}

void BottingThread::run()
{
    qDebug() << "started botting";
    botting = true;
    while(botting)
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
            if(!botting)
                break;
            msleep(200);
            _bot->attack();
            if(_bot->isDead(mob.address) == l2ipc::Command::REPLY_YES)
                break;
        }
    }
}
