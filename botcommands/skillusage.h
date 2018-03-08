#ifndef SKILLUSAGE_H
#define SKILLUSAGE_H

#include "skillrepresentation.h"
#include <QDateTime>
#include "conditions/condition.h"
#include <memory>
#include <QJsonObject>
#include <QJsonArray>

class BotInstance;

class SkillUsage
{
public:
    SkillUsage(BotInstance *botInstance, SkillRepresentation skill);
    SkillUsage();
    SkillUsage(const SkillUsage &skillUsage);



    void setEnabled(bool enabled);
    bool isEnabled() const;

    void update(SkillRepresentation skillRep);
    void use();

    DWORD getId() const;

    QList<std::shared_ptr<Condition>> &getConditions();
    void addCondition(Condition *condition);
    BotInstance *getBotInstance();

    QJsonObject createJsonRepresentation();
    static SkillUsage *createFromJson(QJsonObject &json, BotInstance *botInstance);


private:
    static Condition *conditionFromJson(QJsonObject &json, BotInstance *botInstance);

    BotInstance *_botInstance;
    SkillRepresentation _skill;
    QList<std::shared_ptr<Condition>> _conditions;

    qint64 _lastUse;
    bool _enabled = false;
};

#endif // SKILLUSAGE_H
