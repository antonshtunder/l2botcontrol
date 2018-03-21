#include "gamedatamanager.h"
#include "GameDataManager.h"
#include "lineageipc.h"
#include "misc/utils.h"
#include <QtMath>
#include "instanceinfo/instanceinfobank.h"

using namespace std;

GameDataManager::GameDataManager()
{

}

GameDataManager::~GameDataManager()
{
    CloseHandle(_dataManagmentPipe);
    UnmapViewOfFile(_sharedMemoryData);
    CloseHandle(_sharedMemoryHandle);
}

void GameDataManager::initDataManagmentPipe(HANDLE pipe)
{
    qDebug("dataconnected");
    l2ipc::DataCommand response;
    DWORD PID;
    GetNamedPipeClientProcessId(pipe, &PID);

    _dataManagmentPipe = pipe;
    DWORD command = l2ipc::DataCommand::INIT_MEMORY;
    WriteFile(pipe, reinterpret_cast<LPBYTE>(&command), 4, NULL, NULL);
    ReadFile(pipe, &response, 4, NULL, NULL);
    _sharedMemoryHandle = l2ipc::openSharedMemory(PID);
    _sharedMemoryData = l2ipc::getSharedMemory(_sharedMemoryHandle);
    qDebug("success");
    refreshData();
}

void GameDataManager::refreshData()
{
    if(_sharedMemoryData == NULL || !_refreshed)
    {
        return;
    }
    _refreshed = false;

    DWORD command = l2ipc::DataCommand::GET_DATA;
    if(WriteFile(_dataManagmentPipe, reinterpret_cast<LPBYTE>(&command), 4, NULL, NULL) == FALSE)
    {
        qDebug() << "Data WriteFile fail";
        return;
    }

    l2ipc::DataCommand response;
    if(!ReadFile(_dataManagmentPipe, &response, 4, NULL, NULL))
    {
        qDebug() << "Data ReadFile fail";
        return;
    }

    if(response == l2ipc::DataCommand::NOT_IN_GAME)
    {
        _inGame = false;
    }
    else
    {
        _inGame = true;
        lockRepresentation();
        l2representation.fromData(_sharedMemoryData);
        unlockRepresentation();
    }
    _refreshed = true;

    _mutex.lock();
    _stateRefreshed.wakeAll();
    _mutex.unlock();
}

void GameDataManager::waitForRefreshed()
{
    _mutex.lock();
    _stateRefreshed.wait(&_mutex);
    _mutex.unlock();
}

LineageRepresentation *GameDataManager::lockRepresentation()
{
    static DWORD calledFrom;
    /*__asm
    {
        mov eax, dword ptr ss:[ebp + 0x4];
        mov calledFrom, eax;
    }
    qDebug() << "l " << (LPVOID)calledFrom;*/
    _representationMutex.lock();
    return &l2representation;
}

void GameDataManager::unlockRepresentation()
{
    static DWORD calledFrom;
    /*__asm
    {
        mov eax, dword ptr ss:[ebp + 0x4];
        mov calledFrom, eax;
    }
    qDebug() << "u " << (LPVOID)calledFrom;*/
    _representationMutex.unlock();
}

std::vector<DroppedItemRepresentation> GameDataManager::getItemsInRadius(QPointF loc, double radius)
{
    vector<DroppedItemRepresentation> result;
    auto representation = lockRepresentation();
    auto &items = representation->droppedItems;
    for(auto item : items)
    {
        if(qAbs(item.z - representation->character.z) > 250.0f)
        {
            continue;
        }
        if(getDistance({item.x, item.y}, loc) < radius)
        {
            result.push_back(item);
        }
    }
    unlockRepresentation();
    return result;
}

MobRepresentation GameDataManager::makeInvalidMob()
{
    MobRepresentation invalidMob;
    invalidMob.id = 0;

    return invalidMob;
}

MobRepresentation GameDataManager::getCurrentTarget()
{
    auto representation = lockRepresentation();

    if(representation->character.targetModelAddress == 0)
    {
        unlockRepresentation();
        return makeInvalidMob();
    }

    auto &mobs = representation->mobs;
    for(auto mob : mobs)
    {
        if(mob.modelAddress == representation->character.targetModelAddress)
        {
            unlockRepresentation();
            return mob;
        }
    }
    unlockRepresentation();
    return makeInvalidMob();
}

float GameDataManager::getDistanceToMob(MobRepresentation &mob)
{
    return getDistance({mob.x, mob.y}, getPlayerXY());
}

QPointF GameDataManager::getPlayerXY()
{
    return {l2representation.character.x, l2representation.character.y};
}

MobRepresentation GameDataManager::getMobWithID(DWORD id)
{
    auto representation = lockRepresentation();
    auto &mobs = representation->mobs;
    for(auto mob : mobs)
    {
        if(mob.id == id)
        {
            unlockRepresentation();
            return mob;
        }
    }
    unlockRepresentation();
    return makeInvalidMob();
}

bool GameDataManager::isInGame()
{
    return _inGame;
}

bool GameDataManager::isRefreshed()
{
    return _refreshed;
}

bool GameDataManager::isDecreasedPerformance()
{
    DWORD pid;
    if(GetNamedPipeClientProcessId(_dataManagmentPipe, &pid))
    {
        auto process = OpenProcess(PROCESS_VM_READ, false, pid);
        if(process == NULL)
            return false;

        DWORD base, result;
        ReadProcessMemory(process, reinterpret_cast<LPCVOID>(0x0019F020), &base, 4, NULL);
        ReadProcessMemory(process, reinterpret_cast<LPCVOID>(base + 0x388), &result, 4, NULL);
        return static_cast<bool>(result);
    }
    return false;
}

bool GameDataManager::doesHasTarget()
{
    return l2representation.character.targetModelAddress != 0;
}
