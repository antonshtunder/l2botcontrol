#ifndef MOBINFO_H
#define MOBINFO_H

#include <QString>
#include <Windows.h>

enum Race
{
    UNDEAD,
    ANIMAL,
    BEAST,
    HUMANOID,
    HUMAN,
    CONSTRUCT,
    OTHER
};

class NpcInfo
{
public:
    NpcInfo(DWORD id);
    NpcInfo();

    int getHp() const;
    Race getRace() const;

private:
    int hp = 0;
    Race race = Race::OTHER;
};

#endif // MOBINFO_H
