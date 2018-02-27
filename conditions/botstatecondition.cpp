#include "botstatecondition.h"
#include "botinstance.h"

static QString botAttackingName = "Bot is in attacking state";
static QString botStandingName = "Bot is in standing state";
static QString botPickingUpName = "Bot is in picking up state";

BotStateCondition::BotStateCondition(BotInstance *botInstance, Conditions type):
    Condition(botInstance, type)
{

}

bool BotStateCondition::test()
{
    switch(_type)
    {
    case Conditions::BOT_ATTACKING:
        return _botInstance->getState() == BotState::ATTACKING;
    case Conditions::BOT_STANDING:
        return _botInstance->getState() == BotState::STANDING;
    case Conditions::BOT_PICKINGUP:
        return _botInstance->getState() == BotState::PICKINGUP;
    default:
        return false;
    }
}

QString &BotStateCondition::getName() const
{
    return getName(_type);
}

QWidget *BotStateCondition::createInputWidget()
{
    return new QWidget;
}

void BotStateCondition::retrieveInput()
{
}

QString &BotStateCondition::getName(Conditions type)
{
    switch(type)
    {
    case Conditions::BOT_ATTACKING:
        return botAttackingName;
    case Conditions::BOT_STANDING:
        return botStandingName;
    case Conditions::BOT_PICKINGUP:
        return botPickingUpName;
    default:
        return Condition::getName(type);
    }
}
