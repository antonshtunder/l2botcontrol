#include "skillinfo.h"
#include <QFile>
#include <QXmlStreamReader>

static QString skillDataBase("C:/l2data/stats/skills/");
static QString iconBase("C:/l2data/icons/skill");

QString getSkillDataDocument(int id)
{
    int firstId = id - id % 100;
    int lastId = firstId + 99;
    QString document = QString("%1%2-%3.xml").arg(skillDataBase).arg(firstId, 5, 10, QChar('0'))
            .arg(lastId, 5, 10,  QChar('0'));//skillDataBase % QString::number(firstId) % "-" % QString::number(lastId) % ".xml";
    return document;
}

SkillInfo::SkillInfo(DWORD id)
{
    icon = {QString("%1%2.bmp").arg(iconBase).arg(id, 4, 10, QChar('0'))};
    if(icon.width() == 0)
        icon = {QString("%1%2.bmp").arg(iconBase).arg(0, 4, 10, QChar('0'))};
    QXmlStreamReader xmlReader;
    QFile dataFile(getSkillDataDocument(id));
    if(!dataFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return;
    }
    xmlReader.setDevice(&dataFile);

    QString element;
    while(!xmlReader.atEnd())
    {
        auto token = xmlReader.readNext();
        if(token == QXmlStreamReader::StartElement)
        {
            if(xmlReader.name() == "skill" && xmlReader.attributes().value("", "id").toInt() == id)
            {
                name = xmlReader.attributes().value("", "name").toString();
                while(true)
                {
                    auto token = xmlReader.readNext();
                    switch(token)
                    {
                    case QXmlStreamReader::StartElement:
                        element = xmlReader.attributes().value("", "name").toString();

                        //MP consume read
                        if(element == "#mpConsume2")
                            mpCost = strToIntVector(xmlReader.readElementText());
                        else if(element == "mpConsume2" && mpCost.size() == 0)
                            mpCost.push_back(xmlReader.attributes().value("", "val").toInt());

                        //HP consume read
                        else if(element == "#hpConsume")
                            hpCost = strToIntVector(xmlReader.readElementText());
                        else if(element == "hpConsume" && mpCost.size() == 0)
                            hpCost.push_back(xmlReader.attributes().value("", "val").toInt());

                        else if(element == "castRange")
                            castRange = xmlReader.attributes().value("", "val").toInt();
                        else if(element == "reuseDelay")
                            cooldown = xmlReader.attributes().value("", "val").toInt();

                        break;
                    case QXmlStreamReader::EndElement:
                        if(xmlReader.name() == "skill")
                        {
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

SkillInfo::SkillInfo()
{

}

int SkillInfo::getHpCost(int level) const
{
    if(hpCost.size() < level - 1)
        return 0;
    return hpCost.at(level);
}

QString SkillInfo::getName() const
{
    return name;
}

int SkillInfo::getCooldown() const
{
    return cooldown;
}

int SkillInfo::getCastRange() const
{
    return castRange;
}

int SkillInfo::getMpCost(int level) const
{
    if(mpCost.size() < level - 1)
        return 0;
    return mpCost.at(level);
}

QPixmap SkillInfo::getIcon() const
{
    return icon;
}