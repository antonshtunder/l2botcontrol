#ifndef ITEMUSAGE_H
#define ITEMUSAGE_H

#include "usage.h"
#include "itemrepresentation.h"

class ItemUsage : public Usage
{
public:
    ItemUsage(BotInstance *_instance, ItemRepresentation &item);
    ItemUsage();

    void use() override;
    DWORD getId() const override;
    QJsonObject createJsonRepresentation() override;

    const QString &getName();
    void setName(const QString &name);

    void setItem(DWORD id);

    static ItemUsage *createFromJson(QJsonObject &json, BotInstance *botInstance);

private:
    ItemRepresentation _item;
    QString _name;
};

#endif // ITEMUSAGE_Hc
