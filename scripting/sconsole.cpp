#include "sconsole.h"

#include <QDebug>

SConsole::SConsole(QObject *parent) : QObject(parent)
{

}

void SConsole::log(QString msg)
{
    qDebug() << "console: " << msg;
}
