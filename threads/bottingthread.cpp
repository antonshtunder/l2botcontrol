#include "bottingthread.h"
#include "bot/botinstance.h"

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
    const auto &configuration = _bot->getConfiguration();
    _botting = true;
    _bot->setState(BotState::STANDING);
    _bot->useSkills();
    auto &data = _bot->getDataManager();
    while(_botting)
    {
        MobRepresentation mob;
        if(configuration.getTargeting() == Targeting::ASSIST)
        {
            mob = _bot->assist(configuration.getAssistPlayerName());
        }
        else if(configuration.getTargeting() == Targeting::MOB_IN_AREA)
        {
            mob = _bot->focusNextMob(10000.0, false);
        }
        qDebug() << "new mob address = " << (LPVOID)mob.address;
        if(mob.id == 0)
        {
            msleep(200);
            continue;
        }
        if(data.getDistanceToMob(mob) > 1000.0f)
        {
            _bot->forceMoveTo(mob.x, mob.y, 400.0f);
        }
        while(true)
        {
            if(!_botting)
                break;
            msleep(200);
            _bot->alert();
            _bot->setState(BotState::ATTACKING);
            _bot->useSkills();
            if(_bot->isDead(mob.address) == l2ipc::Command::REPLY_YES)
            {
                qDebug() << "mob dead, address = " << (LPVOID)mob.address;
                _bot->getDataManager().waitForRefreshed();
                _bot->setState(BotState::PICKINGUP);
                _bot->useSkills();

                if(configuration.getTargeting() == Targeting::MOB_IN_AREA)
                {
                    mob = _bot->focusNextMob(150.0, true, true);
                    if(mob.id != 0)
                    {
                        qDebug() << "found new close range mob";
                        continue;
                    }
                }

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
