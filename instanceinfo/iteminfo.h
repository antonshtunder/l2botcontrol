#ifndef ITEMINFO_H
#define ITEMINFO_H

#include <QString>
#include <Windows.h>
#include "misc/utils.h"
#include <QPixmap>

class ItemInfo
{
public:
    ItemInfo(DWORD id);
    ItemInfo();

    DWORD getCooldown() const;

    QString getName() const;

    QPixmap getIcon() const;

private:
    QString name = 0;
    DWORD cooldown = 0;
    QPixmap icon;
};

#endif // ITEMINFO_H
