#include "botinstance.h"
#include "lineageipc.h"
#include "misc/utils.h"
#include <QtMath>

BotInstance &BotInstance::BotInstance::operator=(const BotInstance &botInstance)
{
    return *this;
}

BotInstance::BotInstance(const BotInstance &botInstance):
    _bottingThread(this)
{

}

BotInstance::BotInstance():
    _bottingThread(this)
{
}

BotInstance::~BotInstance()
{
    _bottingThread.stopBotting();
    while(_bottingThread.isRunning())
        QThread::msleep(20);
    delete _widget;
    CloseHandle(_dataManagmentPipe);
    CloseHandle(_commandPipe);
    UnmapViewOfFile(_sharedMemoryData);
    CloseHandle(_sharedMemoryHandle);
}

void BotInstance::initCommandPipe(HANDLE pipe)
{
    _commandPipe = pipe;
}

void BotInstance::initDataManagmentPipe(HANDLE pipe)
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

void BotInstance::refreshData()
{
    if(_sharedMemoryData == NULL || !_refreshed)
    {
        return;
    }
    _refreshed = false;

    DWORD command = l2ipc::DataCommand::GET_DATA;
    if(WriteFile(_dataManagmentPipe, reinterpret_cast<LPBYTE>(&command), 4, NULL, NULL) == FALSE)
        return;

    l2ipc::DataCommand response;
    if(!ReadFile(_dataManagmentPipe, &response, 4, NULL, NULL))
        return;



    if(response == l2ipc::DataCommand::NOT_IN_GAME)
    {
        _inGame = false;
    }
    else
    {
        _inGame = true;
        l2representation.fromData(_sharedMemoryData);
    }
    _refreshed = true;
}

l2ipc::Command BotInstance::performActionOn(DWORD instanceID, DWORD instanceAddress, Representations instanceType)
{
    qDebug() << instanceID;
    DWORD command[4];
    command[0] = l2ipc::Command::PERFORM_ACTION_ON;
    command[1] = instanceID;
    command[2] = instanceAddress;
    command[3] = instanceType;
    auto reply = l2ipc::sendCommand(_commandPipe, command, sizeof(command));
    return reply;
}

l2ipc::Command BotInstance::isDead(DWORD mobAddress)
{
    DWORD command[2];
    command[0] = l2ipc::Command::IS_MOB_DEAD;
    command[1] = mobAddress;
    return l2ipc::sendCommand(_commandPipe, command, sizeof(command));
}

MobRepresentation BotInstance::makeInvalidMob()
{
    MobRepresentation invalidMob;
    invalidMob.id = 0;

    return invalidMob;
}

void BotInstance::startBotting()
{
    qDebug() << "startBotting()";
    if(!_bottingThread.isRunning())
    {
        _bottingThread.start();
    }
}

void BotInstance::stopBotting()
{
    _bottingThread.stopBotting();
}

MobRepresentation BotInstance::findNearestMonster()
{
    auto mobs = l2representation.mobs;
    auto character = l2representation.character;
    size_t minDistanceIndex = 0;
    double minDistance = 100000.0;
    QPointF myLoc(character.x, character.y);
    double distance;

    for(size_t i = 0; i < mobs.size(); ++i)
    {
        if(mobs.at(i).mobType != MobType::MONSTER || mobs.at(i).hp < mobs.at(i).maxHp)
            continue;

        if(qAbs(mobs.at(i).z - character.z) > 250.0)
            continue;

        if((qAbs(mobs.at(i).z - character.z) / distance) > (1.0 / 3.0))
            continue;

        distance = getDistance(myLoc, {mobs.at(i).x, mobs.at(i).y});
        if(distance < minDistance)
        {
            minDistance = distance;
            minDistanceIndex = i;
        }
    }

    if(minDistance < 100000.0)
        return mobs.at(minDistanceIndex);
    else
    {
        return makeInvalidMob();
    }
}

MobRepresentation BotInstance::focusNextMob()
{
    auto mob = findNearestMonster();
    if(mob.id == 0)
        return mob;
    performActionOn(mob.id, mob.address, Representations::MOB);
    return mob;
}

MobRepresentation BotInstance::getMobWithID(DWORD id)
{
    auto mobs = l2representation.mobs;
    for(auto mob : mobs)
    {
        if(mob.id == id)
        {
            return mob;
        }
    }
    return makeInvalidMob();
}

bool BotInstance::isInGame()
{
    return _inGame;
}

bool BotInstance::isRefreshed()
{
    return _refreshed;
}

l2ipc::Command BotInstance::attack()
{
    DWORD command = l2ipc::Command::ATTACK;
    auto reply = l2ipc::sendCommand(_commandPipe, reinterpret_cast<LPBYTE>(&command), sizeof(command));
    return reply;
}

void BotInstance::testClient()
{
    DWORD command = l2ipc::Command::TEST;
    if(WriteFile(_commandPipe, reinterpret_cast<LPBYTE>(&command), 4, NULL, NULL) == FALSE)
    {
        emit clientDisconnected(this);
    }
}

BotInstanceWidget* BotInstance::getWidget()
{
    if(_widget == NULL)
    {
        _widget = new BotInstanceWidget(this);
    }
    return _widget;
}
