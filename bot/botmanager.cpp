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

BotInstance *BotManager::getCurrentBotInstance()
{
    return _botInstance;
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
    QObject::connect(botInstance, SIGNAL(clientDisconnected(BotInstance*)), this, SLOT(clientDisconnectedSlot(BotInstance*)));
    _botInstances.append(botInstance);
    setBotInstance(botInstance);
    qDebug("added");
}

void BotManager::testClients()
{
    for(auto instance : _botInstances)
    {
        instance->testClient();
    }
}

void BotManager::refreshData()
{
    for(auto instance : _botInstances)
    {
        instance->refreshData();
    }
    emit updateUISignal();
}

void BotManager::clientDisconnectedSlot(BotInstance *botInstance)
{
    IPCManager::instance()->removeBotInstance(botInstance);
    _botInstances.removeOne(botInstance);
    if(_botInstance == botInstance)
    {
        if(!_botInstances.isEmpty())
        {
            _botInstance = _botInstances.at(0);
        }
        else
        {
            _botInstance = NULL;
        }
    }
    emit clientDisconnected(botInstance);
}
