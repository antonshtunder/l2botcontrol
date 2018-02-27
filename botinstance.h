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
    void waitForRefreshed();
    DWORD getPID();

    l2ipc::Command performActionOn(DWORD instanceID, DWORD instanceAddress, Representations instanceType);
    l2ipc::Command attack();
    l2ipc::Command isDead(DWORD mobAddress);
    void pickupInRadius(double radius);
    void pickup();
    bool useSkill(DWORD id);
    void useSkills();
    std::vector<DroppedItemRepresentation> getItemsInRadius(QPointF center, double radius);

    MobRepresentation focusNextMob(double radius, bool ignoreHP);
    MobRepresentation getMobWithID(DWORD id);
    MobRepresentation findNearestMonsterInRadius(double radius, bool ignoreHP);
    MobRepresentation getTargetedMob();

    SkillUsage *getSkillUsage(SkillRepresentation &skillRepresentation);

    bool isInGame();
    bool isRefreshed();
    bool isDecreasedPerformance();
    bool isBotting();
    bool doesHasTarget();

    BotInstanceWidget* getWidget();

    void updateWidgets();
    QString name;

    LineageRepresentation l2representation;

    MobRepresentation makeInvalidMob();

    BotState getState() const;
    void setState(const BotState &state);

private:
    HANDLE _commandPipe;
    HANDLE _dataManagmentPipe;
    HANDLE _sharedMemoryHandle;
    BYTE *_sharedMemoryData = NULL;
    DWORD _PID;

    BotInstanceWidget *_widget = NULL;

    BottingThread _bottingThread;

    QTimer *_pipeTestTimer;

    bool _inGame = false;
    bool _refreshed = true;
    bool _pipeUsed = false;
    BotState _state;

    QWaitCondition _stateRefreshed;
    QMutex _mutex;

    QMap<DWORD, std::shared_ptr<SkillUsage>> _skillUsages;

public slots:
    void startBotting();
    void stopBotting();
    void testClient();
    void detach();


signals:
    void clientDisconnected(BotInstance*);
};

#endif // BOTINSTANCE_H
