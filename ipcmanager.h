#ifndef IPCMANAGER_H
#define IPCMANAGER_H

#include <QMap>
#include "botinstance.h"
#include <Windows.h>
#include "threads/commandpipeconnectionthread.h"
#include "threads/datamanagmentpipeconnectionthread.h"

class IPCManager : public QObject
{
    Q_OBJECT

    friend class CommandPipeConnectionThread;
    friend class DataManagmentPipeConnectionThread;

public:
    static IPCManager *instance();

    const QMap<DWORD, BotInstance*>& getBotInstances() const;

private:
    static IPCManager *_instance;

    IPCManager();

    void addBotInstance(DWORD PID, BotInstance *botInstance);
    QMap<DWORD, BotInstance*> _botInstances;

    CommandPipeConnectionThread _commandPipeConnectionThread;
    DataManagmentPipeConnectionThread _dataManagmentPipeConnectionThread;

signals:
    void botInstanceAdded(BotInstance *botInstance);
};

#endif // IPCMANAGER_H
