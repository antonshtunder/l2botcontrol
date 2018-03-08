#include "condition.h"
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
