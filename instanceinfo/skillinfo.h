#ifndef SKILLINFO_H
#define SKILLINFO_H

#include <QString>
#include <Windows.h>
#include "misc/utils.h"
#include <QPixmap>

class SkillInfo
{
public:
    SkillInfo(DWORD id);
    SkillInfo();

    QString getName() const;
    int getHpCost(int level) const;
    int getCooldown() const;
    int getCastRange() const;
    int getMpCost(int level) const;
    QPixmap getIcon() const;

private:
    QString name;
    QPixmap icon;
    int cooldown, castRange;
    std::vector<int> mpCost;
    std::vector<int> hpCost;
};

#endif // SKILLINFO_H
