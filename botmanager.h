#ifndef BOTMANAGER_H
#define BOTMANAGER_H

#include <QObject>
#include "botinstance.h"

class BotManager : public QObject
{
    Q_OBJECT

public:
    static BotManager* instance();

    QList<BotInstance *>& getBotInstances();

    BotInstance* getCurrentBotInstance();

private:
    BotManager();

    void connectSignalsAndSlots();

    BotInstance *_botInstance;
    QList<BotInstance*> _botInstances;

    static BotManager *_instance;

public slots:
    void attack();
    void clientDisconnectedSlot(BotInstance*);
    void setBotInstance(BotInstance *botInstance);
    void newBotInstance(BotInstance *botInstance);
    void testClients();
    void refreshData();

signals:
    void updateUISignal();
    void clientDisconnected(BotInstance*);
};

#endif // BOTMANAGER_H
