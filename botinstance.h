#ifndef BOTINSTANCE_H
#define BOTINSTANCE_H

#include <Windows.h>
#include "botinstancewidget.h"
#include "lineagerepresentation.h"

class BotInstance : public QObject
{
    Q_OBJECT
    /*friend DWORD CALLBACK commandPipeLoop(LPVOID botInstance);
    friend DWORD CALLBACK dataManagmentPipeLoop(LPVOID botInstance);*/

public:
    BotInstance &BotInstance::operator=(const BotInstance &);
    BotInstance(const BotInstance &);
    BotInstance();
    ~BotInstance();

    void initCommandPipe(HANDLE pipe);
    void initDataManagmentPipe(HANDLE pipe);
    void refreshData();

    bool isInGame();
    bool isRefreshed();

    BotInstanceWidget* getWidget();
    QString name;

    LineageRepresentation l2representation;

private:
    HANDLE _commandPipe;
    HANDLE _dataManagmentPipe;
    HANDLE _sharedMemoryHandle;
    BYTE *_sharedMemoryData = NULL;

    BotInstanceWidget *_widget = NULL;

    QTimer *_pipeTestTimer;

    bool _inGame = false;
    bool _refreshed = true;

public slots:
    void attack() const;
    void testClient();

signals:
    void clientDisconnected(BotInstance*);
};

#endif // BOTINSTANCE_H
