#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <QMap>
#include <QPainterPath>
#include <QPointF>
#include <Windows.h>
#include <memory>
#include "botcommands/skillusage.h"

class Configuration
{
    friend BotInstance;
public:
    Configuration(BotInstance *botInstance);

    SkillUsage *getSkillUsage(SkillRepresentation &skillRepresentation);
    QList<QPointF> &getNodes();
    void addNode(const QPointF &node);

    void saveConfiguration(QString path);
    void loadConfiguration(QString path);

    QPainterPath getNodeArea();

private:
    QMap<DWORD, std::shared_ptr<SkillUsage>> _skillUsages;
    QList<QPointF> _nodes;
    BotInstance *_botInstance;
};

#endif // CONFIGURATION_H
