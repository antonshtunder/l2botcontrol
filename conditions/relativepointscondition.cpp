#include "relativepointscondition.h"
#include "bot/botinstance.h"

static QString playerHpMoreName = "Player hp more than";
static QString playerHpLessName = "Player hp less than";
static QString playerMpMoreName = "Player mp more than";
static QString playerMpLessName = "Player mp less than";
static QString playerCpMoreName = "Player cp more than";
static QString playerCpLessName = "Player cp less than";

RelativePointsCondition::RelativePointsCondition(BotInstance *botInstance, Conditions type, float val):
    Condition(botInstance, type),
    _val(val)
{
    if(type < Conditions::PLAYER_HP_MORE_RELATIVE || type > Conditions::PLAYER_CP_LESS_RELATIVE)
        qDebug() << "false type";
}

bool RelativePointsCondition::test()
{
    auto player = _botInstance->l2representation.character;
    switch(_type)
    {
    case Conditions::PLAYER_HP_MORE_RELATIVE:
        if(player.hp >= player.maxHp * _val)
            return true;
        break;
    case Conditions::PLAYER_HP_LESS_RELATIVE:
        if(player.hp < player.maxHp * _val)
            return true;
        break;
    case Conditions::PLAYER_MP_MORE_RELATIVE:
        if(player.mp >= player.maxMp * _val)
            return true;
        break;
    case Conditions::PLAYER_MP_LESS_RELATIVE:
        if(player.mp < player.maxMp * _val)
            return true;
        break;
    case Conditions::PLAYER_CP_MORE_RELATIVE:
        if(player.cp >= player.maxCp * _val)
            return true;
        break;
    case Conditions::PLAYER_CP_LESS_RELATIVE:
        if(player.cp < player.maxCp * _val)
            return true;
        break;
    }
    return false;
}

QString &RelativePointsCondition::getName() const
{
    return RelativePointsCondition::getName(_type);
}

QWidget *RelativePointsCondition::createInputWidget()
{
    auto input = new QDoubleSpinBox;
    input->setDecimals(3);
    input->setSingleStep(0.005);
    input->setMaximum(1.00);
    input->setValue(_val);
    _lastWidget = input;
    return _lastWidget;
}

void RelativePointsCondition::retrieveInput()
{
    _val = qobject_cast<QDoubleSpinBox*>(_lastWidget)->value();
}

QString &RelativePointsCondition::getName(Conditions type)
{
    switch(type)
    {
    case Conditions::PLAYER_HP_MORE_RELATIVE:
        return playerHpMoreName;
    case Conditions::PLAYER_HP_LESS_RELATIVE:
        return playerHpLessName;
    case Conditions::PLAYER_MP_MORE_RELATIVE:
        return playerMpMoreName;
    case Conditions::PLAYER_MP_LESS_RELATIVE:
        return playerMpLessName;
    case Conditions::PLAYER_CP_MORE_RELATIVE:
        return playerCpMoreName;
    case Conditions::PLAYER_CP_LESS_RELATIVE:
        return playerCpLessName;
    }
    return Condition::getName(type);
}


QJsonObject RelativePointsCondition::createJsonRepresentation()
{
    QJsonObject object;
    object.insert("class", JsonType::POINTS_RELATIVE);
    object.insert("type", _type);
    object.insert("value", _val);
    return object;
}


void RelativePointsCondition::parseJsonRepresentation(QJsonObject json)
{
    _type = static_cast<Conditions>(json.value("type").toInt());
    _val = json.value("value").toInt();
}
