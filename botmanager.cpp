#include "botmanager.h"
#include "ipcmanager.h"

BotManager *BotManager::_instance = NULL;

BotManager* BotManager::instance()
{
    if(_instance == NULL)
    {
        _instance = new BotManager();
    }

    return _instance;
}

QList<BotInstance*>& BotManager::getBotInstances()
{
    return _botInstances;
}

BotManager::BotManager()
{
    connectSignalsAndSlots();
}

void BotManager::connectSignalsAndSlots()
{
    QObject::connect(IPCManager::instance(), SIGNAL(botInstanceAdded(BotInstance*)), this, SLOT(newBotInstance(BotInstance*)));
}

void BotManager::attack()
{
    _botInstance->attack();
}

void BotManager::setBotInstance(BotInstance *botInstance)
{
    _botInstance = botInstance;
    emit updateUISignal();
}

void BotManager::newBotInstance(BotInstance *botInstance)
{
    _botInstances.append(botInstance);
    setBotInstance(botInstance);
    qDebug("added");
}
