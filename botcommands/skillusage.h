#ifndef SKILLUSAGE_H
#define SKILLUSAGE_H

#include <botinstance.h>

class SkillUsage
{
public:
    SkillUsage(BotInstance *botInstance, SkillRepresentation skill);

private:
    BotInstance *_botInstance;
    SkillRepresentation _skill;
};

#endif // SKILLUSAGE_H
