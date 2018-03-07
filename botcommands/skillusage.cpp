#include "skillusage.h"
#include <bot/botinstance.h>
#include "instanceinfo/instanceinfobank.h"
#include "conditions/relativepointscondition.h"

using namespace std;

SkillUsage::SkillUsage(BotInstance *botInstance, SkillRepresentation skill):
    _botInstance(botInstance),
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

void SkillUsage::setEnabled(bool enabled)
{
    _enabled = enabled;
}

bool SkillUsage::isEnabled() const
{
    return _enabled;
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
            auto distance = getDistance({_botInstance->l2representation.character.x, _botInstance->l2representation.character.y},
            {target.x, target.y});
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

QList<std::shared_ptr<Condition> > &SkillUsage::getConditions()
{
    return _conditions;
}

BotInstance *SkillUsage::getBotInstance()
{
    return _botInstance;
}
