#include "instanceinfobank.h"

InstanceInfoBank *InstanceInfoBank::_instance = NULL;

SkillInfo &InstanceInfoBank::getSkillInfo(DWORD id)
{
    if(_skillInfoBank.count(id) == 0)
    {
        SkillInfo skillInfo(id);
        _skillInfoBank[id] = skillInfo;
    }
    return _skillInfoBank[id];
}

InstanceInfoBank::InstanceInfoBank()
{

}

InstanceInfoBank *InstanceInfoBank::instance()
{
    if(_instance == NULL)
    {
        _instance = new InstanceInfoBank();
    }
    return _instance;
}
