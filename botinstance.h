#ifndef BOTINSTANCE_H
#define BOTINSTANCE_H

#include <Windows.h>
#include "botinstancewidget.h"
#include "lineagerepresentation.h"
#include "threads/bottingthread.h"
#include "lineageipc.h"

class BotInstance : public QObject
{
    Q_OBJECT
    /*friend DWORD CALLBACK commandPipeLoop(LPVOID botInstance);
    friend DWORD CALLBACK dataManagmentPipeLoop(LPVOID botInstance);*/

public:
    BotInstance &BotInstance::operator=(const BotInstance &);
    BotInstance(const BotInstance &);
    BotInstance();
    ~BotInstance();

    void initCommandPipe(HANDLE pipe);
    void initDataManagmentPipe(HANDLE pipe);
    void refreshData();

    l2ipc::Command performActionOn(DWORD instanceID, DWORD instanceAddress, Representations instanceType);
    l2ipc::Command attack();
    l2ipc::Command isDead(DWORD mobAddress);

    MobRepresentation focusNextMob();
    MobRepresentation getMobWithID(DWORD id);
    MobRepresentation findNearestMonster();

    bool isInGame();
    bool isRefreshed();

    BotInstanceWidget* getWidget();
    QString name;

    LineageRepresentation l2representation;

    MobRepresentation makeInvalidMob();

private:
    HANDLE _commandPipe;
    HANDLE _dataManagmentPipe;
    HANDLE _sharedMemoryHandle;
    BYTE *_sharedMemoryData = NULL;

    BotInstanceWidget *_widget = NULL;
    BottingThread _bottingThread;

    QTimer *_pipeTestTimer;

    bool _inGame = false;
    bool _refreshed = true;

public slots:
    void startBotting();
    void stopBotting();
    void testClient();

signals:
    void clientDisconnected(BotInstance*);
};

#endif // BOTINSTANCE_H
