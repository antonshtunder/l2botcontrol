#ifndef EFFECTDURATIONCONDITION_H
#define EFFECTDURATIONCONDITION_H

#include "condition.h"
#include <Windows.h>

class EffectDurationCondition : public Condition
{
public:
    EffectDurationCondition(BotInstance *botInstance, Conditions type, DWORD id, DWORD timeLeft);

    // Condition interface
public:
    virtual bool test() override;
    virtual QString &getName() const override;
    virtual QWidget *createInputWidget() override;
    virtual void retrieveInput() override;
    QJsonObject createJsonRepresentation() override;
    void parseJsonRepresentation(QJsonObject) override;

    static QString &getName(Conditions type);

private:
    DWORD _id, _timeLeft;
};

#endif // EFFECTDURATIONCONDITION_H
