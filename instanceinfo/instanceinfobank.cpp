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

ItemInfo &InstanceInfoBank::getItemInfo(DWORD id)
{
    if(_itemInfoBank.count(id) == 0)
    {
        ItemInfo itemInfo(id);
        _itemInfoBank[id] = itemInfo;
    }
    return _itemInfoBank[id];
}

float InstanceInfoBank::getCellHeight(float x, float y, float z)
{
    float posX = x - GEO_LEFT_BORDER;
    float posY = y - GEO_TOP_BORDER;
    int xRegionNum = static_cast<int>(posX / GEO_REGION);
    int yRegionNum = static_cast<int>(posY / GEO_REGION);
    int xRegion = 10 + xRegionNum;
    int yRegion = 10 + yRegionNum;
    float regionX = posX - xRegionNum * GEO_REGION;
    float regionY = posY - yRegionNum * GEO_REGION;

    if(xRegion == lastXRegion && yRegion == lastYRegion)
    {
        return lastRegion->getHeight(regionX, regionY, z);
    }

    QString regionName = QString("%1_%2").arg(xRegion).arg(yRegion);
    if(!_geodata.contains(regionName))
    {
        GeodataRegion newGeodata(regionName);
        _geodata.insert(regionName, newGeodata);
        lastRegion = &newGeodata;
    }

    lastRegion = &_geodata[regionName];
    return lastRegion->getHeight(regionX, regionY, z);
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
