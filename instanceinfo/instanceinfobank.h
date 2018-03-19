#ifndef INSTANCEINFOBANK_H
#define INSTANCEINFOBANK_H

#include "geodataregion.h"
#include "skillinfo.h"
#include <Windows.h>
#include <map>

class InstanceInfoBank
{
public:
    static InstanceInfoBank *instance();

    SkillInfo &getSkillInfo(DWORD id);
    float getCellHeight(float x, float y, float z);

private:
    InstanceInfoBank();

    static InstanceInfoBank *_instance;

    std::map<DWORD, SkillInfo> _skillInfoBank;
    QMap<QString, GeodataRegion> _geodata;

    int lastXRegion = 0, lastYRegion = 0;
    GeodataRegion *lastRegion = NULL;
};

#endif // INSTANCEINFOBANK_H
