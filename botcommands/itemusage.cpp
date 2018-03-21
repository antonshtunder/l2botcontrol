#include "itemusage.h"
#include <bot/botinstance.h>
#include "instanceinfo/instanceinfobank.h"
#include "conditions/relativepointscondition.h"
#include "conditions/botstatecondition.h"
#include "conditions/effectcondition.h"
#include "conditions/effectdurationcondition.h"

ItemUsage::ItemUsage(BotInstance *botInstance):
    Usage(botInstance)
{
    _lastUse = 0;
}

ItemUsage::ItemUsage()
{

}


void ItemUsage::use()
{
    if(!_enabled)
        return;

    for(auto condition : _conditions)
    {
        if(!condition->test())
            return;
    }

    auto itemInfo = InstanceInfoBank::instance()->getItemInfo(_item.typeID);
    auto currTime = QDateTime::currentMSecsSinceEpoch();
    if(currTime - _lastUse > itemInfo.getCooldown())
    {
        _lastUse = QDateTime::currentMSecsSinceEpoch();
    }
}

DWORD ItemUsage::getId() const
{
    return _item.id;
}

QJsonObject ItemUsage::createJsonRepresentation()
{
    return Usage::createJsonRepresentation();
}

const QString &ItemUsage::getName()
{
    return _name;
}

void ItemUsage::setName(const QString &name)
{
    _name = name;
}
