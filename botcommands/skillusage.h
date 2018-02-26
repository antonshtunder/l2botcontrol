#ifndef SKILLUSAGE_H
#define SKILLUSAGE_H

#include "skillrepresentation.h"
#include <QDateTime>
#include "conditions/condition.h"
#include <memory>

class BotInstance;

class SkillUsage
{
public:
    SkillUsage(BotInstance *botInstance, SkillRepresentation skill);

    SkillUsage();

    void setEnabled(bool enabled);
    bool isEnabled() const;

    void update(SkillRepresentation skillRep);
    void use();

    QList<std::shared_ptr<Condition>> &getConditions();
    BotInstance *getBotInstance();

private:
    BotInstance *_botInstance;
    SkillRepresentation _skill;
    QList<std::shared_ptr<Condition>> _conditions;

    qint64 lastUse = 0;
    bool _enabled = false;
};

#endif // SKILLUSAGE_H
