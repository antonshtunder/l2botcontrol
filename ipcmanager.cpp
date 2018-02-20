#include "ipcmanager.h"
#include "lineageipc.h"
#include "threads/commandpipeconnectionthread.h"

IPCManager *IPCManager::_instance;

IPCManager *IPCManager::instance()
{
    if(_instance == NULL)
    {
        _instance = new IPCManager();
    }
    return _instance;
}

const QMap<DWORD, BotInstance*>& IPCManager::getBotInstances() const
{
    return _botInstances;
}

IPCManager::IPCManager()
{
    qDebug("q");
    _commandPipeConnectionThread.start();
    _dataManagmentPipeConnectionThread.start();
}

void IPCManager::addBotInstance(DWORD PID, BotInstance *botInstance)
{
    botInstance->name = QString::number(PID);
    _botInstances.insert(PID, botInstance);
    emit botInstanceAdded(botInstance);
}
