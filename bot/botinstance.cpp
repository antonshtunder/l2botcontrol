#include "botinstance.h"
#include "lineageipc.h"
#include "misc/utils.h"
#include <QtMath>
#include "instanceinfo/instanceinfobank.h"
#include <QtConcurrent>

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
    CloseHandle(_commandPipe);
}

void BotInstance::initCommandPipe(HANDLE pipe)
{
    _commandPipe = pipe;
}

void BotInstance::initDataManagmentPipe(HANDLE pipe)
{
    _dataManager.initDataManagmentPipe(pipe);
}

void BotInstance::refreshData()
{
    _dataManager.refreshData();
}

DWORD BotInstance::getPID()
{
    return _PID;
}

void BotInstance::detach()
{
    emit clientDisconnected(this);
}

l2ipc::Command BotInstance::performActionOn(DWORD instanceID, DWORD instanceAddress, Representations instanceType)
{
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
    QThread::msleep(100);
    auto l2representation = &_dataManager.l2representation;
    QPointF loc(l2representation->character.x, l2representation->character.y);
    auto items = _dataManager.getItemsInRadius(loc, radius);
    DWORD pickupTime = 250;
    if(isDecreasedPerformance())
    {
        pickupTime *= 2.5;
    }
    for(int i = 0; i < items.size() * 2; ++i)
    {
        pickup();
        QThread::msleep(pickupTime);
    }

   _dataManager.waitForRefreshed();
    items = _dataManager.getItemsInRadius(loc, radius);
    _pipeUsed = true;
    for(auto item : items)
    {
        auto reply = performActionOn(item.id, item.address, Representations::DROPPED_ITEM);
    }
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

void BotInstance::useItem(DWORD id)
{
    DWORD command[2];
    command[0] = l2ipc::Command::USE_ITEM;
    command[1] = id;
    l2ipc::sendCommand(_commandPipe, &command, sizeof(command));
}

void BotInstance::assist()
{
    DWORD command = l2ipc::Command::ASSIST;
    l2ipc::sendCommand(_commandPipe, &command, sizeof(command));
}

void BotInstance::moveTo(float x, float y)
{
    float z = InstanceInfoBank::instance()->getCellHeight(x, y, _dataManager.l2representation.character.z) - 30.0f;
    qDebug() << "moving to (" << x << ", " << y << ", " << z << ")";

    DWORD command[4];
    command[0] = l2ipc::Command::MOVE_TO;
    memcpy(&(command[1]), &x, sizeof(DWORD));
    memcpy(&(command[2]), &y, sizeof(DWORD));
    memcpy(&(command[3]), &z, sizeof(DWORD));
    l2ipc::sendCommand(_commandPipe, &command, sizeof(command));
}

void BotInstance::forceMoveTo(float x, float y, float radius)
{
    QtConcurrent::run([this, x, y, radius]{
        QPointF moveToLoc(x, y);
        moveTo(x, y);
        auto &l2representation = getDataManager().l2representation;
        QPointF charLoc(l2representation.character.x, l2representation.character.y);
        while(getDistance(moveToLoc, charLoc) > radius)
        {
            Sleep(30);
        }
    });
}

void BotInstance::npcChat(DWORD index)
{
    DWORD command[2];
    command[0] = l2ipc::Command::NPC_CHAT;
    command[1] = index;
    l2ipc::sendCommand(_commandPipe, &command, sizeof(command));
}

void BotInstance::acceptAction()
{
    DWORD command;
    command = l2ipc::Command::ACCEPT_ACTION;
    l2ipc::sendCommand(_commandPipe, &command, sizeof(command));
}

void BotInstance::speakTo(int npcId)
{
    DWORD command[2];
    command[0] = l2ipc::Command::SPEAK_TO;
    command[1] = npcId;
    l2ipc::sendCommand(_commandPipe, &command, sizeof(command));
}

MobRepresentation BotInstance::assist(const QString &name)
{
    auto l2representation = _dataManager.lockRepresentation();
    auto &mobs = l2representation->mobs;
    MobRepresentation target;
    for(auto mob : mobs)
    {
        if(QString::fromUtf16(mob.name) == name)
        {
            target = mob;
            break;
        }
    }

    MobRepresentation assistedMob;
    if(target.address != 0)
    {
        for(auto mob : mobs)
        {
            if(target.targetModelAddress == mob.modelAddress)
            {
                assistedMob = mob;
                focusMob(mob);
                break;
            }
        }
    }
    _dataManager.unlockRepresentation();
    return assistedMob;
}

void BotInstance::alert()
{
    double radius = 750.0;
    auto representation = _dataManager.lockRepresentation();
    auto name = QString::fromUtf16(representation->character.name);
    QString mobName;
    for(auto mob : representation->mobs)
    {
        if(mob.mobType == MobType::PLAYER)
        {
            auto distance = getDistance({representation->character.x, representation->character.y}, {mob.x, mob.y});

            if(distance < radius && qAbs(representation->character.z - mob.z) < 250.0)
            {
                mobName = QString::fromUtf16(mob.name);
                if(name != mobName && mobName != QString("GroznijKarlik") && mobName != QString("Opezdal"))
                {
                    qDebug() << distance;
                    qDebug() << mobName;
                    _audioPlayer.playAlert();
                    _dataManager.unlockRepresentation();
                    return;
                }
            }
        }
    }
    _dataManager.unlockRepresentation();
}

BotState BotInstance::getState() const
{
    return _state;
}

void BotInstance::setState(const BotState &state)
{
    _state = state;
}

GameDataManager &BotInstance::getDataManager()
{
    return _dataManager;
}

void BotInstance::startBotting()
{
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
    auto representation = _dataManager.lockRepresentation();
    auto &mobs = representation->mobs;
    auto &character = representation->character;
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

        if(qAbs(mobs.at(i).z - character.z) > 400.0f)
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
    _dataManager.unlockRepresentation();

    if(minDistance < radius)
        return mobs.at(minDistanceIndex);
    else
    {
        return _dataManager.makeInvalidMob();
    }
}

MobRepresentation BotInstance::getCurrentTarget()
{
    return _dataManager.getCurrentTarget();
}

void BotInstance::focusMob(const MobRepresentation &mob)
{
    performActionOn(mob.id, mob.address, Representations::MOB);
}

MobRepresentation BotInstance::focusNextMob(double radius, bool ignoreHP, bool ignoreArea)
{
    MobRepresentation mob;
    mob = findNearestMonsterInRadius(radius, ignoreHP, ignoreArea);
    if(mob.id != 0)
    {
        focusMob(mob);
    }
    return mob;
}

MobRepresentation BotInstance::getMobWithID(DWORD id)
{
    return _dataManager.getMobWithID(id);
}

bool BotInstance::isInGame()
{
    return _dataManager.isInGame();
}

bool BotInstance::isRefreshed()
{
    return _dataManager.isRefreshed();
}

bool BotInstance::isDecreasedPerformance()
{
    return _dataManager.isDecreasedPerformance();
}

bool BotInstance::isBotting()
{
    return _bottingThread.isBotting();
}

bool BotInstance::doesHasTarget()
{
    return _dataManager.doesHasTarget();
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
