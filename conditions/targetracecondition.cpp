#include "targetracecondition.h"
#include "bot/botinstance.h"
#include "instanceinfo/instanceinfobank.h"

static QString targetRaceConditionName = "Target race is ";

TargetRaceCondition::TargetRaceCondition(BotInstance *botInstance,  Race race):
    Condition(botInstance, Conditions::TARGET_RACE_IS),
    race(race)
{

}

bool TargetRaceCondition::test()
{
    auto mob = _botInstance->getCurrentTarget();
    auto mobInfo = InstanceInfoBank::instance()->getNpcInfo(mob.typeID);
    if(mobInfo.getRace() == race)
    {
        return !notFlag;
    }
    return notFlag;
}

QString &TargetRaceCondition::getName() const
{
    return targetRaceConditionName;
}

QWidget *TargetRaceCondition::createInputWidget()
{
    _lastWidget = new QWidget;
    QHBoxLayout *layout = new QHBoxLayout;
    layout->setAlignment(Qt::AlignLeft);

    QCheckBox *cbNot = new QCheckBox;
    cbNot->setChecked(false);
    layout->addWidget(cbNot);
    QLabel *lblNot = new QLabel("not");
    layout->addWidget(lblNot);
    QComboBox *cbRace = new QComboBox;
    for(int i = Race::UNDEAD; i < Race::LAST; ++i)
    {
        cbRace->addItem(NpcInfo::raceToString(static_cast<Race>(i)));
    }
    layout->addWidget(cbRace);

    _lastWidget->setLayout(layout);
    return _lastWidget;
}

void TargetRaceCondition::retrieveInput()
{
    auto widgets = _lastWidget->children();
    QCheckBox *cbNot = reinterpret_cast<QCheckBox*>(widgets[1]);
    notFlag = cbNot->isChecked();
    QComboBox *cbRace = reinterpret_cast<QComboBox*>(widgets[3]);
    race = static_cast<Race>(cbRace->currentIndex());
}

QJsonObject TargetRaceCondition::createJsonRepresentation()
{
    QJsonObject json;
    json.insert("class", JsonType::TARGET_RACE);
    json.insert("type", _type);
    json.insert("race", race);
    json.insert("not", notFlag);
    return json;
}

void TargetRaceCondition::parseJsonRepresentation(QJsonObject json)
{
    _type = static_cast<Conditions>(json.value("type").toInt());
    race = static_cast<Race>(json.value("race").toInt());
    notFlag = json.value("not").toBool();
}

QString &TargetRaceCondition::getName(Conditions type)
{
    return targetRaceConditionName;
}
