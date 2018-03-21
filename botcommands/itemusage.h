#ifndef ITEMUSAGE_H
#define ITEMUSAGE_H

#include "usage.h"
#include "itemrepresentation.h"

class ItemUsage : Usage
{
public:
    ItemUsage(BotInstance *_instance, ItemRepresentation &item);
    ItemUsage();

    void use() override;
    DWORD getId() const override;
    QJsonObject createJsonRepresentation() override;

    const QString &getName();
    void setName(const QString &name);

private:
    ItemRepresentation _item;
    QString _name;
};

#endif // ITEMUSAGE_H
