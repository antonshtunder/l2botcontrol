#include "skillusage.h"
#include <botinstance.h>
#include "instanceinfo/instanceinfobank.h"
#include "conditions/relativepointscondition.h"

using namespace std;

SkillUsage::SkillUsage(BotInstance *botInstance, SkillRepresentation skill):
    _botInstance(botInstance),
    _skill(skill)
{

}

SkillUsage::SkillUsage()
{

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
    if(currTime - lastUse > skillInfo.getCooldown())
    {
        lastUse = QDateTime::currentMSecsSinceEpoch();
        _botInstance->useSkill(_skill.id);
    }
}

QList<std::shared_ptr<Condition> > &SkillUsage::getConditions()
{
    return _conditions;
}

BotInstance *SkillUsage::getBotInstance()
{
    return _botInstance;
}
