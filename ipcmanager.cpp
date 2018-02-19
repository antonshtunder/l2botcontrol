#include "ipcmanager.h"
#include "lineageipc.h"

IPCManager *IPCManager::_instance;

DWORD CALLBACK commandPipeConnectionLoop(LPVOID)
{
    DWORD PID;
    while(true)
    {
        auto pipe = l2ipc::createCommandPipe();
        if(ConnectNamedPipe(pipe, NULL))
        {
            GetNamedPipeClientProcessId(pipe, &PID);
            if(!IPCManager::instance()->_botInstances.keys().contains(PID))
            {
                qDebug("a");
                IPCManager::instance()->addBotInstance(PID, new BotInstance());
            }
            IPCManager::instance()->_botInstances[PID]->initCommandPipe(pipe);
        }
    }

    return 1;
}

DWORD CALLBACK dataManagmentPipeConnectionLoop(LPVOID)
{
    DWORD PID;
    while(true)
    {
        auto pipe = l2ipc::createDataManagmentPipe();
        if(ConnectNamedPipe(pipe, NULL))
        {
            GetNamedPipeClientProcessId(pipe, &PID);
            if(!IPCManager::instance()->_botInstances.keys().contains(PID))
            {
                qDebug("a");
                IPCManager::instance()->addBotInstance(PID, new BotInstance());
            }
            IPCManager::instance()->_botInstances[PID]->initDataManagmentPipe(pipe);
        }
    }

    return 1;
}

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
    auto thread = CreateThread(NULL, 0, commandPipeConnectionLoop, NULL, 0, NULL);
    CloseHandle(thread);
    thread = CreateThread(NULL, 0, dataManagmentPipeConnectionLoop, NULL, 0, NULL);
    CloseHandle(thread);
}

void IPCManager::addBotInstance(DWORD PID, BotInstance *botInstance)
{
    _botInstances.insert(PID, botInstance);
    emit botInstanceAdded(botInstance);
}
