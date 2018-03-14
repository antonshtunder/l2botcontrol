#include "botinstance.h"
#include "lineageipc.h"
#include "misc/utils.h"
#include <QtMath>

using namespace std;

AudioPlayer BotInstance::_audioPlayer;

BotInstance &BotInstance::BotInstance::operator=(const BotInstance &botInstance)
{
    return *this;
}

BotInstance::BotInstance(const BotInstance &botInstance):
    _bottingThread(this),
    _configuration(this)
{

}

BotInstance::BotInstance(DWORD PID):
    _bottingThread(this),
    _configuration(this)
{
    _PID = PID;
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

void BotInstance::waitForRefreshed()
{
    _mutex.lock();
    _stateRefreshed.wait(&_mutex);
    _mutex.unlock();
}

DWORD BotInstance::getPID()
{
    return _PID;
}

void BotInstance::lockRepresentation()
{
    _representationMutex.lock();
}

void BotInstance::unlockRepresentation()
{
    _representationMutex.unlock();
}

void BotInstance::detach()
{
    emit clientDisconnected(this);
}

l2ipc::Command BotInstance::performActionOn(DWORD instanceID, DWORD instanceAddress, Representations instanceType)
{
    //qDebug() << (LPVOID)instanceID;
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

void BotInstance::pickupInRadius(double radius)
{
    qDebug() << "starting picking up";
    QThread::msleep(100);
    QPointF loc(l2representation.character.x, l2representation.character.y);
    auto items = getItemsInRadius(loc, radius);
    DWORD pickupTime = 250;
    if(isDecreasedPerformance())
    {
        pickupTime *= 2.5;
        qDebug() << "decreased performance";
    }
    for(int i = 0; i < items.size() * 2; ++i)
    {
        pickup();
        QThread::msleep(pickupTime);
    }
    auto ugu = items.size();

    waitForRefreshed();
    items = getItemsInRadius(loc, radius);
    _pipeUsed = true;
    for(auto item : items)
    {
        auto reply = performActionOn(item.id, item.address, Representations::DROPPED_ITEM);
        if(reply == l2ipc::Command::REPLY_YES)
            qDebug() << "pickup success";
        else
        {
            qDebug() << "pickup fail";
            qDebug() << "item address = " << (LPVOID)item.address;
            qDebug() << "item id = " << (LPVOID)item.id;
        }
    }
    qDebug() << "init size - " << ugu;
    qDebug() << "picked up automatically - " << (ugu - items.size());
    _pipeUsed = false;
}

void BotInstance::pickup()
{
    DWORD command[2];
    command[0] = l2ipc::Command::DO_ACTION;
    command[1] = 5;
    l2ipc::sendCommand(_commandPipe, &command, sizeof(command));
}

bool BotInstance::useSkill(DWORD id)
{
    _pipeUsed = true;
    DWORD command[2];
    command[0] = l2ipc::Command::USE_SKILL;
    command[1] = id;
    auto reply = l2ipc::sendCommand(_commandPipe, &command, sizeof(command));
    _pipeUsed = false;
    if(reply == l2ipc::Command::REPLY_NO)
    {

        return false;
    }
    return true;
}

void BotInstance::useSkills()
{

    for(auto skillUsage : _configuration._skillUsages.values())
    {
        skillUsage->use();
    }
}

void BotInstance::alert()
{
    double radius = 750.0;
    lockRepresentation();
    auto name = QString::fromUtf16(l2representation.character.name);
    QString mobName;
    for(auto mob : l2representation.mobs)
    {
        if(mob.mobType == MobType::PLAYER)
        {
            auto distance = getDistance({l2representation.character.x, l2representation.character.y}, {mob.x, mob.y});

            if(distance < radius && qAbs(l2representation.character.z - mob.z) < 250.0)
            {
                mobName = QString::fromUtf16(mob.name);
                if(name != mobName)
                {
                    qDebug() << distance;
                    qDebug() << mobName;
                    _audioPlayer.playAlert();
                    unlockRepresentation();
                    return;
                }
            }
        }
    }
    unlockRepresentation();
}

std::vector<DroppedItemRepresentation> BotInstance::getItemsInRadius(QPointF loc, double radius)
{
    vector<DroppedItemRepresentation> result;
    lockRepresentation();
    auto &items = l2representation.droppedItems;
    for(auto item : items)
    {
        if(qAbs(item.z - l2representation.character.z) > 250.0f)
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

MobRepresentation BotInstance::makeInvalidMob()
{
    MobRepresentation invalidMob;
    invalidMob.id = 0;

    return invalidMob;
}

BotState BotInstance::getState() const
{
    return _state;
}

void BotInstance::setState(const BotState &state)
{
    _state = state;
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

MobRepresentation BotInstance::findNearestMonsterInRadius(double radius, bool ignoreHP, bool ignoreArea)
{
    lockRepresentation();
    auto &mobs = l2representation.mobs;
    auto &character = l2representation.character;
    size_t minDistanceIndex = 0;
    double minDistance = radius;
    QPointF myLoc(character.x, character.y);
    double distance;
    bool areaIsPresent = false;
    QPainterPath nodeArea;

    if(!ignoreArea)
    {
        areaIsPresent = _configuration.getNodes().size() >= 3;
    }

    if(areaIsPresent)
    {
        nodeArea = _configuration.getNodeArea();
    }

    for(size_t i = 0; i < mobs.size(); ++i)
    {
        if(mobs.at(i).mobType != MobType::MONSTER || (mobs.at(i).hp < mobs.at(i).maxHp && !ignoreHP))
            continue;

        if(qAbs(mobs.at(i).z - character.z) > 250.0)
            continue;

        if(areaIsPresent && !nodeArea.contains({mobs.at(i).x, mobs.at(i).y}))
        {
            continue;
        }

        distance = getDistance(myLoc, {mobs.at(i).x, mobs.at(i).y});
        if(distance < minDistance)
        {
            if(ignoreHP)
                if(isDead(mobs.at(i).address))
                    continue;

            minDistance = distance;
            minDistanceIndex = i;
        }
    }
    unlockRepresentation();

    if(minDistance < radius)
        return mobs.at(minDistanceIndex);
    else
    {
        return makeInvalidMob();
    }
}

MobRepresentation BotInstance::getTargetedMob()
{
    for(auto mob : l2representation.mobs)
    {
        //if(l2representation.character.targetModelAddress == mob.)
        qDebug() << "not implemented";
    }
    return makeInvalidMob();
}

MobRepresentation BotInstance::getCurrentTarget()
{
    if(l2representation.character.targetModelAddress == 0)
        return makeInvalidMob();

    lockRepresentation();
    auto &mobs = l2representation.mobs;
    for(auto mob : mobs)
    {
        if(mob.modelAddress == l2representation.character.targetModelAddress)
        {
            unlockRepresentation();
            return mob;
        }
    }
    unlockRepresentation();
    return makeInvalidMob();
}

MobRepresentation BotInstance::focusNextMob(double radius, bool ignoreHP, bool ignoreArea)
{
    auto mob = findNearestMonsterInRadius(radius, ignoreHP, ignoreArea);
    if(mob.id != 0)
        performActionOn(mob.id, mob.address, Representations::MOB);
    return mob;
}

MobRepresentation BotInstance::getMobWithID(DWORD id)
{
    lockRepresentation();
    auto &mobs = l2representation.mobs;
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

bool BotInstance::isInGame()
{
    return _inGame;
}

bool BotInstance::isRefreshed()
{
    return _refreshed;
}

bool BotInstance::isDecreasedPerformance()
{
    DWORD pid;
    if(GetNamedPipeClientProcessId(_commandPipe, &pid))
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

bool BotInstance::isBotting()
{
    return _bottingThread.isBotting();
}

bool BotInstance::doesHasTarget()
{
    return l2representation.character.targetModelAddress != 0;
}

l2ipc::Command BotInstance::attack()
{
    DWORD command = l2ipc::Command::ATTACK;
    auto reply = l2ipc::sendCommand(_commandPipe, reinterpret_cast<LPBYTE>(&command), sizeof(command));
    return reply;
}

void BotInstance::testClient()
{
    if(_pipeUsed)
        return;

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

Configuration &BotInstance::getConfiguration()
{
    return _configuration;
}
