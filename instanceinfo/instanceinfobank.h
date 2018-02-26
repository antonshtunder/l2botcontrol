#ifndef INSTANCEINFOBANK_H
#define INSTANCEINFOBANK_H

#include "skillinfo.h"
#include <Windows.h>
#include <map>

class InstanceInfoBank
{
public:
    static InstanceInfoBank *instance();

    SkillInfo &getSkillInfo(DWORD id);

private:
    InstanceInfoBank();

    static InstanceInfoBank *_instance;

    std::map<DWORD, SkillInfo> _skillInfoBank;
};

#endif // INSTANCEINFOBANK_H
