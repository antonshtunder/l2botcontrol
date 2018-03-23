#ifndef BOTINSTANCE_H
#define BOTINSTANCE_H

#include <Windows.h>
#include "botinstancewidget.h"
#include "lineagerepresentation.h"
#include "threads/bottingthread.h"
#include "lineageipc.h"
#include <vector>
#include "widgets/skillwidget.h"
#include "widgets/skilllistwidget.h"
#include "botcommands/skillusage.h"
#include <memory>
#include "misc/audioplayer.h"
#include "configuration.h"
#include "gamedatamanager.h"

enum BotState
{
    ATTACKING,
    PICKINGUP,
    STANDING
};

class BotInstance : public QObject
{
    Q_OBJECT
    /*friend DWORD CALLBACK commandPipeLoop(LPVOID botInstance);
    friend DWORD CALLBACK dataManagmentPipeLoop(LPVOID botInstance);*/

public:
    BotInstance &BotInstance::operator=(const BotInstance &);
    BotInstance(const BotInstance &);
    BotInstance(DWORD PID);
    ~BotInstance();

    void initCommandPipe(HANDLE pipe);
    void initDataManagmentPipe(HANDLE pipe);
    void refreshData();
    DWORD getPID();

    l2ipc::Command performActionOn(DWORD instanceID, DWORD instanceAddress, Representations instanceType);
    l2ipc::Command attack();
    l2ipc::Command isDead(DWORD mobAddress);
    void pickupInRadius(double radius);
    void pickup();
    bool useSkill(DWORD id);
    void useCommands();
    void useItem(DWORD id);
    void assist();
    void moveTo(float x, float y);
    void forceMoveTo(float x, float y, float radius);
    void npcChat(DWORD index);
    void acceptAction();
    void speakTo(int npcId);
    MobRepresentation assist(const QString &name);

    void alert();

    MobRepresentation focusNextMob(double radius, bool ignoreHP, bool ignoreArea = false);
    MobRepresentation getMobWithID(DWORD id);
    MobRepresentation findNearestMonsterInRadius(double radius, bool ignoreHP, bool ignoreArea = false);
    MobRepresentation getTargetedMob();
    MobRepresentation getCurrentTarget();
    void focusMob(const MobRepresentation &mob);

    bool isInGame();
    bool isRefreshed();
    bool isDecreasedPerformance();
    bool isBotting();
    bool doesHasTarget();
    bool checkIfAttacking();
    bool isDead();

    BotInstanceWidget* getWidget();
    Configuration &getConfiguration();

    void updateWidgets();
    QString name;

    BotState getState() const;
    void setState(const BotState &state);

    GameDataManager &getDataManager();

private:
    l2ipc::Command sendCommand(LPVOID command, size_t size);

    HANDLE _commandPipe;
    HANDLE _dataManagmentPipe;
    HANDLE _sharedMemoryHandle;
    BYTE *_sharedMemoryData = NULL;
    DWORD _PID;
    static AudioPlayer _audioPlayer;

    BotInstanceWidget *_widget = NULL;

    BottingThread _bottingThread;

    QTimer *_pipeTestTimer;
    Configuration _configuration;
    GameDataManager _dataManager;

    bool _inGame = false;
    bool _refreshed = true;
    bool _pipeUsed = false;
    BotState _state;

    QWaitCondition _stateRefreshed;
    QMutex _mutex;
    QMutex _representationMutex;
    QMutex _actionMutex;
    QMutex _commandPipeMutex;

    qint64 _attackCheck = 0;
    DWORD _lastHp;
    QPointF _lastLoc;

public slots:
    void startBotting();
    void stopBotting();
    void testClient();
    void detach();


signals:
    void clientDisconnected(BotInstance*);
};

#endif // BOTINSTANCE_H
