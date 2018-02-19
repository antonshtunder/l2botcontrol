#include "botinstance.h"
#include "lineageipc.h"

DWORD CALLBACK commandPipeLoop(LPVOID botInstance)
{
    BotInstance *instance = reinterpret_cast<BotInstance*>(botInstance);
    while(true)
    {

    }

    return 1;
}

DWORD CALLBACK dataManagmentPipeLoop(LPVOID botInstance)
{
    BotInstance *instance = reinterpret_cast<BotInstance*>(botInstance);
    while(true)
    {

    }

    return 1;
}

BotInstance &BotInstance::BotInstance::operator=(const BotInstance &botInstance)
{
    return *this;
}

BotInstance::BotInstance(const BotInstance &botInstance)
{

}

BotInstance::BotInstance()
{

}

BotInstance::~BotInstance()
{

}

void BotInstance::initCommandPipe(HANDLE pipe)
{
    _commandPipe = pipe;
}

void BotInstance::initDataManagmentPipe(HANDLE pipe)
{
    _dataManagmentPipe = pipe;
}

void BotInstance::attack() const
{
    DWORD command = l2ipc::Command::ATTACK;
    WriteFile(_commandPipe, reinterpret_cast<LPBYTE>(&command), 4, NULL, NULL);
}

BotInstanceWidget* BotInstance::getWidget()
{
    if(_widget == NULL)
    {
        _widget = new BotInstanceWidget(this);
    }
    return _widget;
}
