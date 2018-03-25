#include "npcinfo.h"
#include <QFile>
#include <QXmlStreamReader>
#include <QDebug>

static QString mobDataBase("C:/l2data/stats/npcs/");

QString getMobDataDocument(int id)
{
    int firstId = id - id % 100;
    int lastId = firstId + 99;
    QString document = QString("%1%2-%3.xml").arg(mobDataBase).arg(firstId, 5, 10, QChar('0'))
            .arg(lastId, 5, 10,  QChar('0'));

    return document;
}

Race stringToRace(const QString raceName)
{
    Race race;
    if(raceName == "ANIMAL")
        return Race::ANIMAL;
    else if(raceName == "BEAST")
        return Race::BEAST;
    else if(raceName == "CONSTRUCT")
        return Race::CONSTRUCT;
    else if(raceName == "HUMAN")
        return Race::HUMAN;
    else if(raceName == "HUMANOID")
        return Race::HUMANOID;
    else if(raceName == "UNDEAD")
        return Race::UNDEAD;
    else
        return Race::OTHER;
}

NpcInfo::NpcInfo(DWORD id)
{

    QXmlStreamReader xmlReader;
    QFile dataFile(getMobDataDocument(id));
    if(!dataFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "failed to open " << getMobDataDocument(id);
        return;
    }
    xmlReader.setDevice(&dataFile);

    QString element;
    xmlReader.readNextStartElement();
    while(!xmlReader.atEnd())
    {
        auto token = xmlReader.readNext();
        if(token == QXmlStreamReader::StartElement)
        {
            if(xmlReader.name() == "npc" && xmlReader.attributes().value("", "id").toInt() == id)
            {
                while(true)
                {
                    auto token = xmlReader.readNext();
                    switch(token)
                    {
                    case QXmlStreamReader::StartElement:
                        element = xmlReader.name().toString();
                        if(element == "race")
                        {
                            race = stringToRace(xmlReader.readElementText());
                        }
                        else if(element == "stats")
                        {
                            qDebug() << "found stats";
                            while((token != QXmlStreamReader::StartElement || xmlReader.name() != "vitals") &&
                                  (token != QXmlStreamReader::EndElement || xmlReader.name() != "stats"))
                            {
                                token = xmlReader.readNext();
                            }
                            if(xmlReader.name() == "vitals")
                            {
                                qDebug() << "found vitals";
                                hp = xmlReader.attributes().value("", "hp").toDouble();
                            }
                        }
                        break;
                    case QXmlStreamReader::EndElement:
                        if(xmlReader.name() == "npc")
                        {
                            qDebug() << "read npc with id = " << id << ", hp = " << hp << ", race = " << race;
                            return;
                        }
                        break;
                    }
                }
            }
            else
            {
                xmlReader.readNextStartElement();
                xmlReader.skipCurrentElement();
            }
        }
    }
}

NpcInfo::NpcInfo()
{}

Race NpcInfo::getRace() const
{
    return race;
}

QString NpcInfo::raceToString(Race race)
{
    switch(race)
    {
    case Race::ANIMAL: return "ANIMAL";
    case Race::BEAST: return "BEAST";
    case Race::CONSTRUCT: return "CONSTRUCT";
    case Race::HUMAN: return "HUMAN";
    case Race::HUMANOID: return "HUMANOID";
    case Race::OTHER: return "OTHER";
    case Race::UNDEAD: return "UNDEAD";
    default: return "UNKNOWN";
    }
}

int NpcInfo::getHp() const
{
    return hp;
}
