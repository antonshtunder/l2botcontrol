#ifndef EFFECTCONDITION_H
#define EFFECTCONDITION_H

#include "condition.h"
#include <Windows.h>


class EffectCondition : public Condition
{
public:
    EffectCondition(BotInstance *botInstance, Conditions type, DWORD id);

    bool test() override;
    QString &getName() const override;
    QWidget *createInputWidget() override;
    void retrieveInput() override;

    static QString &getName(Conditions type);

private:
    DWORD _id;
};

#endif // EFFECTCONDITION_H
