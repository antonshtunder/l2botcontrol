#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <QMap>
#include <QPainterPath>
#include <QPointF>
#include <Windows.h>
#include <memory>
#include "botcommands/skillusage.h"

enum Targeting
{
    MOB_IN_AREA,
    ASSIST
};

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

    Targeting getTargeting() const;
    void setTargeting(const Targeting &targeting);

    QString getAssistPlayerName() const;
    void setAssistPlayerName(const QString &assistPlayerName);

private:
    QMap<DWORD, std::shared_ptr<SkillUsage>> _skillUsages;
    QList<QPointF> _nodes;
    BotInstance *_botInstance;
    Targeting _targeting;
    QString _assistPlayerName;
};

#endif // CONFIGURATION_H
