#ifndef BOTSTATECONDITION_H
#define BOTSTATECONDITION_H

#include "condition.h"

class BotStateCondition : public Condition
{
public:
    BotStateCondition(BotInstance *botInstance, Conditions type);

    bool test() override;
    QString &getName() const override;
    QWidget *createInputWidget() override;
    void retrieveInput() override;
    QJsonObject createJsonRepresentation() override;
    void parseJsonRepresentation(QJsonObject) override;

    static QString &getName(Conditions type);
};

#endif // BOTSTATECONDITION_H
