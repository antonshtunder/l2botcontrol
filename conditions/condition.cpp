#include "botstatecondition.h"
#include "condition.h"
#include "effectcondition.h"
#include "effectdurationcondition.h"
#include "relativepointscondition.h"
#include <QLabel>
#include <QWidget>
#include <QDebug>

static QString name = "Condition";

Condition::Condition(BotInstance *botInstance, Conditions type):
    _botInstance(botInstance),
    _type(type)
{

}

Condition::~Condition()
{
    qDebug() << "condition removed";
}

bool Condition::test()
{
    return true;
}

QString &Condition::getName() const
{
    return name;
}

QWidget *Condition::createInputWidget()
{
    _lastWidget =  new QLabel("none");
    return _lastWidget;
}

void Condition::retrieveInput()
{

}

QJsonObject Condition::createJsonRepresentation()
{
    return QJsonObject();
}

void Condition::parseJsonRepresentation(QJsonObject)
{

}

QWidget *Condition::lastWidget() const
{
    return _lastWidget;
}

QString &Condition::getName(Conditions type)
{
    return name;
}

void Condition::fillConditionComboBox(QComboBox *cb)
{
    cb->addItem(RelativePointsCondition::getName(Conditions::PLAYER_HP_MORE_RELATIVE));
    cb->addItem(RelativePointsCondition::getName(Conditions::PLAYER_HP_LESS_RELATIVE));
    cb->addItem(RelativePointsCondition::getName(Conditions::PLAYER_MP_MORE_RELATIVE));
    cb->addItem(RelativePointsCondition::getName(Conditions::PLAYER_MP_LESS_RELATIVE));
    cb->addItem(RelativePointsCondition::getName(Conditions::PLAYER_CP_MORE_RELATIVE));
    cb->addItem(RelativePointsCondition::getName(Conditions::PLAYER_CP_LESS_RELATIVE));
    cb->addItem(EffectCondition::getName(Conditions::PLAYER_HAS_EFFECT));
    cb->addItem(EffectCondition::getName(Conditions::PLAYER_DOESNT_HAVE_EFFECT));
    cb->addItem(EffectCondition::getName(Conditions::TARGET_HAS_EFFECT));
    cb->addItem(EffectCondition::getName(Conditions::TARGET_DOESNT_HAVE_EFFECT));
    cb->addItem(EffectDurationCondition::getName(Conditions::PLAYER_EFFECT_TIME_LEFT));
    cb->addItem(BotStateCondition::getName(Conditions::BOT_ATTACKING));
    cb->addItem(BotStateCondition::getName(Conditions::BOT_STANDING));
    cb->addItem(BotStateCondition::getName(Conditions::BOT_PICKINGUP));
}

Condition *Condition::processConditionComboBox(QComboBox *cb, BotInstance *botInstance, DWORD id)
{
    switch(cb->currentIndex())
    {
    case 0:
        return new RelativePointsCondition(botInstance, Conditions::PLAYER_HP_MORE_RELATIVE, 0.5);
    case 1:
        return new RelativePointsCondition(botInstance, Conditions::PLAYER_HP_LESS_RELATIVE, 0.5);
    case 2:
        return new RelativePointsCondition(botInstance, Conditions::PLAYER_MP_MORE_RELATIVE, 0.5);
    case 3:
        return new RelativePointsCondition(botInstance, Conditions::PLAYER_MP_LESS_RELATIVE, 0.5);
    case 4:
        return new RelativePointsCondition(botInstance, Conditions::PLAYER_CP_MORE_RELATIVE, 0.5);
    case 5:
        return new RelativePointsCondition(botInstance, Conditions::PLAYER_CP_LESS_RELATIVE, 0.5);
    case 6:
        return new EffectCondition(botInstance, Conditions::PLAYER_HAS_EFFECT, id);
    case 7:
        return new EffectCondition(botInstance, Conditions::PLAYER_DOESNT_HAVE_EFFECT, id);
    case 8:
        return new EffectCondition(botInstance, Conditions::TARGET_HAS_EFFECT, id);
    case 9:
        return new EffectCondition(botInstance, Conditions::TARGET_DOESNT_HAVE_EFFECT, id);
    case 10:
        return new EffectDurationCondition(botInstance, Conditions::PLAYER_EFFECT_TIME_LEFT, id, 5);
    case 11:
        return new BotStateCondition(botInstance, Conditions::BOT_ATTACKING);
    case 12:
        return new BotStateCondition(botInstance, Conditions::BOT_STANDING);
    case 13:
        return new BotStateCondition(botInstance, Conditions::BOT_PICKINGUP);
    }
}
