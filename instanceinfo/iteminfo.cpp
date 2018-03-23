#include "iteminfo.h"
#include <QFile>
#include <QXmlStreamReader>

static QString itemDataBase("C:/l2data/stats/items/");
static QString iconBase("C:/l2data/icons/");

QString getItemDataDocument(int id)
{
    int firstId = id - id % 100;
    int lastId = firstId + 99;
    QString document = QString("%1%2-%3.xml").arg(itemDataBase).arg(firstId, 5, 10, QChar('0'))
            .arg(lastId, 5, 10,  QChar('0'));

    return document;
}

ItemInfo::ItemInfo(DWORD id)
{
    QXmlStreamReader xmlReader;
    QFile dataFile(getItemDataDocument(id));
    if(!dataFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return;
    }
    xmlReader.setDevice(&dataFile);

    QString element;
    icon = {QString("%1%2.bmp").arg(iconBase).arg("skill0000")};

    xmlReader.readNextStartElement();
    while(!xmlReader.atEnd())
    {
        auto token = xmlReader.readNext();
        if(token == QXmlStreamReader::StartElement)
        {
            if(xmlReader.name() == "item" && xmlReader.attributes().value("", "id").toInt() == id)
            {
                name = xmlReader.attributes().value("", "name").toString();
                while(true)
                {
                    auto token = xmlReader.readNext();
                    switch(token)
                    {
                    case QXmlStreamReader::StartElement:
                        element = xmlReader.attributes().value("", "name").toString();
                        if(element == "reuse_delay")
                            cooldown = xmlReader.attributes().value("", "val").toInt();
                        else if(element == "icon")
                        {
                            auto path = QString("%1%2.bmp").arg(iconBase).arg(xmlReader.attributes().value("", "val").toString().remove(0, 5));
                            if(QFile::exists(path))
                                icon = {path};
                        }
                        break;
                    case QXmlStreamReader::EndElement:
                        if(xmlReader.name() == "item")
                        {
                            return;
                        }
                        break;
                    default:
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

ItemInfo::ItemInfo()
{

}

DWORD ItemInfo::getCooldown() const
{
    return cooldown;
}

QString ItemInfo::getName() const
{
    return name;
}

QPixmap ItemInfo::getIcon() const
{
    return icon;
}
