#include "itemusage.h"
#include <bot/botinstance.h>
#include "instanceinfo/instanceinfobank.h"
#include "conditions/relativepointscondition.h"
#include "conditions/botstatecondition.h"
#include "conditions/effectcondition.h"
#include "conditions/effectdurationcondition.h"

ItemUsage::ItemUsage(BotInstance *botInstance, ItemRepresentation &item):
    Usage(botInstance),
    _item(item)
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
        qDebug() << "item used";
        qDebug() << "cooldown" << itemInfo.getCooldown();
        _lastUse = QDateTime::currentMSecsSinceEpoch();
        _botInstance->useItem(_item.typeID);
    }
}

DWORD ItemUsage::getId() const
{
    return _item.typeID;
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

void ItemUsage::setItem(DWORD id)
{
    _item.typeID = id;
}
