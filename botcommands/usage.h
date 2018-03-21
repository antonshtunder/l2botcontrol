#ifndef USAGE_H
#define USAGE_H

#include "skillrepresentation.h"
#include <QDateTime>
#include "conditions/condition.h"
#include <memory>
#include <QJsonObject>
#include <QJsonArray>

class Usage
{
public:
    Usage();
    Usage(BotInstance *botInstance);
    virtual ~Usage();

    void setEnabled(bool enabled);
    bool isEnabled() const;

    virtual void use();

    virtual DWORD getId() const;

    QList<std::shared_ptr<Condition>> &getConditions();
    void addCondition(Condition *condition);
    BotInstance *getBotInstance();

    virtual QJsonObject createJsonRepresentation();
    static Usage *createFromJson(QJsonObject &json, BotInstance *botInstance);

protected:
    static Condition *conditionFromJson(QJsonObject &json, BotInstance *botInstance);

    BotInstance *_botInstance;
    QList<std::shared_ptr<Condition>> _conditions;

    qint64 _lastUse;
    bool _enabled = false;
};

#endif // USAGE_H
