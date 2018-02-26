#ifndef RELATIVEPOINTSCONDITION_H
#define RELATIVEPOINTSCONDITION_H

#include "condition.h"

class BotInstance;

class RelativePointsCondition : public Condition
{
public:
    RelativePointsCondition(BotInstance *botInstance, Conditions type, float val);

    bool test() override;
    QString &getName() const override;
    QWidget *createInputWidget() override;
    void retrieveInput() override;

    static QString &getName(Conditions type);

private:
    float _val;
};

#endif // RELATIVEPOINTSCONDITION_H
