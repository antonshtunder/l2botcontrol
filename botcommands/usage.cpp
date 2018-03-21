#include "Usage.h"
#include <bot/botinstance.h>
#include "instanceinfo/instanceinfobank.h"
#include "conditions/relativepointscondition.h"
#include "conditions/botstatecondition.h"
#include "conditions/effectcondition.h"
#include "conditions/effectdurationcondition.h"

using namespace std;

Usage::Usage(BotInstance *botInstance):
    _botInstance(botInstance)
{
    qDebug() << "Usage(b)";
    _lastUse = 0;
}

Usage::~Usage()
{

}

Usage::Usage()
{
    qDebug() << "Usage()";
    _lastUse = 0;
}

void Usage::setEnabled(bool enabled)
{
    _enabled = enabled;
}

bool Usage::isEnabled() const
{
    return _enabled;
}

void Usage::use()
{}

DWORD Usage::getId() const
{
    return 0;
}

QList<std::shared_ptr<Condition> > &Usage::getConditions()
{
    return _conditions;
}

void Usage::addCondition(Condition *condition)
{
    _conditions.append(std::shared_ptr<Condition>(condition));
}

BotInstance *Usage::getBotInstance()
{
    return _botInstance;
}

QJsonObject Usage::createJsonRepresentation()
{
    QJsonObject object;
    return object;
}

Usage *Usage::createFromJson(QJsonObject &json, BotInstance *botInstance)
{
    Usage *usage = new Usage(botInstance);
    return usage;
}

Condition *Usage::conditionFromJson(QJsonObject &json, BotInstance *botInstance)
{
    auto conditionClass = static_cast<JsonType>(json.value("class").toInt());
    Condition *result = NULL;
    switch(conditionClass)
    {
    case JsonType::BOT_STATE:
        result = new BotStateCondition(botInstance, Conditions::NONE);
        break;
    case JsonType::EFFECT_PRESENCE:
        result = new EffectCondition(botInstance, Conditions::NONE, 0);
        break;
    case JsonType::EFFECT_TIME:
        result = new EffectDurationCondition(botInstance, Conditions::NONE, 0, .0);
        break;
    case JsonType::POINTS_RELATIVE:
        result = new RelativePointsCondition(botInstance, Conditions::NONE, .0);
        break;
    }

    result->parseJsonRepresentation(json);

    return result;
}
