#include "effectdurationcondition.h"
#include "botinstance.h"

static QString playerEffectTimeLeftName = "Player effect with id, time left";

EffectDurationCondition::EffectDurationCondition(BotInstance *botInstance, Conditions type, DWORD id, DWORD timeLeft):
    Condition(botInstance, type),
    _id(id),
    _timeLeft(timeLeft)
{

}

bool EffectDurationCondition::test()
{
    auto effects = _botInstance->l2representation.playerEffects;
    for(auto effect : effects)
    {
        if(effect.id == _id)
        {
            if(effect.remainingTime <= _timeLeft)
                return true;
            else
                return false;
        }
    }
    return true;
}

QString &EffectDurationCondition::getName() const
{
    return getName(_type);
}

QWidget *EffectDurationCondition::createInputWidget()
{
    _lastWidget = new QWidget;
    QHBoxLayout *layout = new QHBoxLayout;
    QSpinBox *sbId = new QSpinBox;
    sbId->setMaximum(100000);
    sbId->setValue(_id);
    sbId->setSingleStep(1);
    QSpinBox *sbTime = new QSpinBox;
    sbTime->setMaximum(3600);
    sbTime->setValue(_timeLeft);
    sbTime->setSingleStep(1);
    layout->addWidget(sbId);
    layout->addWidget(sbTime);
    _lastWidget->setLayout(layout);
    return _lastWidget;
}

void EffectDurationCondition::retrieveInput()
{
    auto children = _lastWidget->children();
    auto sbId = reinterpret_cast<QSpinBox*>(children[1]);
    auto sbTime = reinterpret_cast<QSpinBox*>(children[2]);
    _id = sbId->value();
    _timeLeft = sbTime->value();
}

QString &EffectDurationCondition::getName(Conditions type)
{
    if(type == Conditions::PLAYER_EFFECT_TIME_LEFT)
        return playerEffectTimeLeftName;
    else
        return Condition::getName(type);
}
