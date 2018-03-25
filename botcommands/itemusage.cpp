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

ItemUsage *ItemUsage::createFromJson(QJsonObject &json, BotInstance *botInstance)
{
    auto l2representation = botInstance->getDataManager().lockRepresentation();
    auto &items = l2representation->items;
    bool present = false;
    DWORD id = json.value("id").toInt();
    ItemRepresentation itemRep;

    for(auto &item : items)
    {
        if(item.id == id)
        {
            itemRep = item;
            present = true;
        }
    }
    botInstance->getDataManager().unlockRepresentation();

    if(!present)
        return NULL;

    bool enabled = json.value("enabled").toBool();
    ItemUsage *itemUsage = new ItemUsage(botInstance, itemRep);
    itemUsage->setEnabled(enabled);

    auto conditions = json.value("conditions").toArray();
    for(auto condition : conditions)
    {
        auto object = condition.toObject();
        itemUsage->addCondition(conditionFromJson(object, botInstance));
    }

    return itemUsage;
}
