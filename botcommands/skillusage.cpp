#include "skillusage.h"
#include <bot/botinstance.h>
#include "instanceinfo/instanceinfobank.h"
#include "conditions/relativepointscondition.h"
#include "conditions/botstatecondition.h"
#include "conditions/effectcondition.h"
#include "conditions/effectdurationcondition.h"
#include "conditions/targetracecondition.h"

using namespace std;

SkillUsage::SkillUsage(BotInstance *botInstance, SkillRepresentation skill):
    Usage(botInstance),
    _skill(skill)
{
    qDebug() << "SKILLUSAGE(b)";
    _lastUse = 0;
}

SkillUsage::SkillUsage()
{
    qDebug() << "SKILLUSAGE()";
    _lastUse = 0;
}

SkillUsage::SkillUsage(const SkillUsage &skillUsage)
{
    qDebug() << "SKILLUSAGE(c)";
    _lastUse = skillUsage._lastUse;
    _enabled = skillUsage._enabled;
    _botInstance = skillUsage._botInstance;
    _conditions = skillUsage._conditions;
    _skill = skillUsage._skill;
}

void SkillUsage::update(SkillRepresentation skillRep)
{
    _skill = skillRep;
}

void SkillUsage::use()
{
    if(!_enabled)
        return;

    for(auto condition : _conditions)
    {
        if(!condition->test())
            return;
    }

    auto skillInfo = InstanceInfoBank::instance()->getSkillInfo(_skill.id);
    auto currTime = QDateTime::currentMSecsSinceEpoch();
    if(currTime - _lastUse > skillInfo.getCooldown())
    {
        if(_botInstance->getState() == BotState::ATTACKING)
        {
            auto target = _botInstance->getCurrentTarget();
            auto l2representation = _botInstance->getDataManager().lockRepresentation();
            auto distance = getDistance({l2representation->character.x, l2representation->character.y},
            {target.x, target.y});
            _botInstance->getDataManager().unlockRepresentation();

            if(distance > skillInfo.getCastRange() + 120.0)
            {
                return;
            }
        }
        if(_botInstance->useSkill(_skill.id))
        {
            _lastUse = QDateTime::currentMSecsSinceEpoch();
        }
        else
        {
            qDebug() << "failed to use skill with name - " << skillInfo.getName();
        }
    }
}

DWORD SkillUsage::getId() const
{
    return _skill.id;
}

QJsonObject SkillUsage::createJsonRepresentation()
{
    QJsonObject object;
    QJsonArray conditions;
    for(auto condition : _conditions)
    {
        conditions.push_back(condition->createJsonRepresentation());
    }

    object.insert("enabled", _enabled);
    object.insert("id", static_cast<int>(_skill.id));
    object.insert("conditions", conditions);

    return object;
}

SkillUsage *SkillUsage::createFromJson(QJsonObject &json, BotInstance *botInstance)
{
    auto l2representation = botInstance->getDataManager().lockRepresentation();
    auto &skills = l2representation->activeSkills;
    bool present = false;
    DWORD id = json.value("id").toInt();
    SkillRepresentation skillRep;

    for(auto &skill : skills)
    {
        if(skill.id == id)
        {
            skillRep = skill;
            present = true;
        }
    }
    botInstance->getDataManager().unlockRepresentation();

    if(!present)
        return NULL;

    bool enabled = json.value("enabled").toBool();
    SkillUsage *skillUsage = new SkillUsage(botInstance, skillRep);
    skillUsage->setEnabled(enabled);

    auto conditions = json.value("conditions").toArray();
    for(auto condition : conditions)
    {
        auto object = condition.toObject();
        skillUsage->addCondition(conditionFromJson(object, botInstance));
    }

    return skillUsage;
}
