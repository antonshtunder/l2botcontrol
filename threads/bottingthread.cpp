#include "bottingthread.h"
#include "botinstance.h"

#define PICKUP_RADIUS 200.0

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
    _bot->setState(BotState::STANDING);
    _bot->useSkills();
    _botting = true;
    while(_botting)
    {
        auto mob = _bot->focusNextMob(10000.0, false);
        qDebug() << "1new mob id = " << (LPVOID)mob.id;
        if(mob.id == 0)
        {
            msleep(200);
            continue;
        }
        while(true)
        {
            if(!_botting)
                break;
            msleep(300);
            _bot->setState(BotState::ATTACKING);
            _bot->useSkills();
            if(_bot->isDead(mob.address) == l2ipc::Command::REPLY_YES)
            {
                qDebug() << "mob dead";
                _bot->setState(BotState::PICKINGUP);
                _bot->useSkills();

                mob = _bot->focusNextMob(150.0, true);
                if(mob.id != 0)
                    continue;

                _bot->pickupInRadius(PICKUP_RADIUS);

                _bot->setState(BotState::STANDING);
                _bot->useSkills();
                break;
            }
            if(!_bot->doesHasTarget())
                break;
            _bot->attack();
        }
    }
}
