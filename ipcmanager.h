#ifndef IPCMANAGER_H
#define IPCMANAGER_H

#include <QMap>
#include "botinstance.h"
#include <Windows.h>

class IPCManager : public QObject
{
    Q_OBJECT

    friend DWORD CALLBACK commandPipeConnectionLoop(LPVOID);
    friend DWORD CALLBACK dataManagmentPipeConnectionLoop(LPVOID);

public:
    static IPCManager *instance();

    const QMap<DWORD, BotInstance*>& getBotInstances() const;

private:
    static IPCManager *_instance;

    IPCManager();

    void addBotInstance(DWORD PID, BotInstance *botInstance);

    QMap<DWORD, BotInstance*> _botInstances;

signals:
    void botInstanceAdded(BotInstance *botInstance);
};

#endif // IPCMANAGER_H
