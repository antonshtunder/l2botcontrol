#ifndef GAMEDATAMANAGER_H
#define GAMEDATAMANAGER_H

#include "bot/botinstance.h"

class GameDataManager
{
public:
    GameDataManager();
    ~GameDataManager();

    void initDataManagmentPipe(HANDLE pipe);
    void refreshData();
    void waitForRefreshed();
    LineageRepresentation &lockRepresentation();
    void unlockRepresentation();

    std::vector<DroppedItemRepresentation> getItemsInRadius(QPointF loc, double radius);
    MobRepresentation getMobWithID(DWORD id);
    MobRepresentation findNearestMonsterInRadius(double radius, bool ignoreHP, bool ignoreArea = false);
    MobRepresentation getCurrentTarget();
    void focusMob(const MobRepresentation &mob);

    bool isInGame();
    bool isRefreshed();
    bool isDecreasedPerformance();
    bool doesHasTarget();

    QString name;

    LineageRepresentation l2representation;

    MobRepresentation makeInvalidMob();

private:
    HANDLE _dataManagmentPipe;
    HANDLE _sharedMemoryHandle;
    BYTE *_sharedMemoryData = NULL;
    DWORD _PID;

    bool _inGame = false;
    bool _refreshed = true;

    QWaitCondition _stateRefreshed;
    QMutex _mutex;
    QMutex _representationMutex;
};

#endif // GAMEDATAMANAGER_H
