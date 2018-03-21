#ifndef SKILLUSAGE_H
#define SKILLUSAGE_H

#include "skillrepresentation.h"
#include "usage.h"

class BotInstance;

class SkillUsage : public Usage
{
public:
    SkillUsage(BotInstance *botInstance, SkillRepresentation skill);
    SkillUsage();
    SkillUsage(const SkillUsage &skillUsage);

    void use() override;
    DWORD getId() const override;
    QJsonObject createJsonRepresentation() override;

    void update(SkillRepresentation skillRep);

    static SkillUsage *createFromJson(QJsonObject &json, BotInstance *botInstance);


private:
    static Condition *conditionFromJson(QJsonObject &json, BotInstance *botInstance);

    SkillRepresentation _skill;
};

#endif // SKILLUSAGE_H
