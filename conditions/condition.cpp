#include "condition.h"
#include <QLabel>
#include <QWidget>

static QString name = "Condition";

Condition::Condition(BotInstance *botInstance, Conditions type):
    _botInstance(botInstance),
    _type(type)
{

}

Condition::~Condition()
{

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

QWidget *Condition::lastWidget() const
{
    return _lastWidget;
}

QString &Condition::getName(Conditions type)
{
    return name;
}
