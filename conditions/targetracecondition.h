#ifndef TARGETRACECONDITION_H
#define TARGETRACECONDITION_H

#include "condition.h"
#include "instanceinfo/npcinfo.h"

class TargetRaceCondition : public Condition
{
public:
    TargetRaceCondition(BotInstance *botInstance, Race race = Race::UNDEAD);

    bool test() override;
    QString &getName() const override;
    QWidget *createInputWidget() override;
    void retrieveInput() override;
    QJsonObject createJsonRepresentation() override;
    void parseJsonRepresentation(QJsonObject) override;

    static QString &getName(Conditions type = Conditions::NONE);

private:
    Race race;
    bool notFlag;
};

#endif // TARGETRACECONDITION_H
