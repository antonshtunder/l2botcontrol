#include "effectcondition.h"
#include "bot/botinstance.h"
#include <QSpinBox>

static QString playerHasEffectName = "Player has effect with id";
static QString playerDoesntHaveEffectName = "Player doesn't have effect with id";
static QString targetHasEffectName = "Target has effect with id";
static QString targetDoesntHaveEffectName = "Target doesn't have effect with id";

EffectCondition::EffectCondition(BotInstance *botInstance, Conditions type, DWORD id):
    Condition(botInstance, type),
    _id(id)
{

}

bool EffectCondition::test()
{
    std::vector<EffectRepresentation> *effects = NULL;
    auto &dataManager = _botInstance->getDataManager();
    auto l2representation = dataManager.lockRepresentation();
    if(_type == Conditions::TARGET_DOESNT_HAVE_EFFECT || _type == Conditions::TARGET_DOESNT_HAVE_EFFECT)
    {
        effects = &l2representation->targetEffects;
    }
    else
    {
        effects = &l2representation->playerEffects;
    }
    bool result = false;
    switch(_type)
    {
    case Conditions::PLAYER_HAS_EFFECT:
    case Conditions::TARGET_HAS_EFFECT:
        for(auto effect : *effects)
        {
            if(effect.id == _id)
            {
                result = true;
                break;
            }
        }
        result = false;
        break;
    case Conditions::PLAYER_DOESNT_HAVE_EFFECT:
        break;
    case Conditions::TARGET_DOESNT_HAVE_EFFECT:
        for(auto effect : *effects)
        {
            if(effect.id == _id)
            {
                result = false;
                break;
            }
        }
        result = true;
        break;
    default:
        qDebug() << "effects wrong type";
        break;
    }
    dataManager.unlockRepresentation();
    return result;
}

QString &EffectCondition::getName() const
{
    return getName(_type);
}

QWidget *EffectCondition::createInputWidget()
{
    QSpinBox *sb = new QSpinBox;
    sb->setMaximum(100000);
    sb->setValue(_id);
    sb->setSingleStep(1);
    _lastWidget = sb;
    return sb;
}

void EffectCondition::retrieveInput()
{
    QSpinBox *input = reinterpret_cast<QSpinBox*>(_lastWidget);
    _id = input->value();
    qDebug() << _id;
}

QString &EffectCondition::getName(Conditions type)
{
    switch(type)
    {
    case Conditions::PLAYER_HAS_EFFECT:
        return playerHasEffectName;
    case Conditions::PLAYER_DOESNT_HAVE_EFFECT:
        return playerDoesntHaveEffectName;
    case Conditions::TARGET_HAS_EFFECT:
        return targetHasEffectName;
    case Conditions::TARGET_DOESNT_HAVE_EFFECT:
        return targetDoesntHaveEffectName;
    default:
        return Condition::getName(type);
    }
}


QJsonObject EffectCondition::createJsonRepresentation()
{
    QJsonObject object;
    object.insert("class", JsonType::EFFECT_PRESENCE);
    object.insert("type", _type);
    object.insert("id", static_cast<int>(_id));
    return object;
}


void EffectCondition::parseJsonRepresentation(QJsonObject json)
{
    _type = static_cast<Conditions>(json.value("type").toInt());
    _id = json.value("id").toInt();
}
