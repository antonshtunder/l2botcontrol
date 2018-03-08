#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <QMap>
#include <Windows.h>
#include <memory>
#include "botcommands/skillusage.h"

class Configuration
{
    friend BotInstance;
public:
    Configuration(BotInstance *botInstance);

    SkillUsage *getSkillUsage(SkillRepresentation &skillRepresentation);

    void saveConfiguration(QString path);
    void loadConfiguration(QString path);

private:
    QMap<DWORD, std::shared_ptr<SkillUsage>> _skillUsages;
    BotInstance *_botInstance;
};

#endif // CONFIGURATION_H
