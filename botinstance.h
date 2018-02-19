#ifndef BOTINSTANCE_H
#define BOTINSTANCE_H

#include <Windows.h>
#include "botinstancewidget.h"

class BotInstance
{
    /*friend DWORD CALLBACK commandPipeLoop(LPVOID botInstance);
    friend DWORD CALLBACK dataManagmentPipeLoop(LPVOID botInstance);*/

public:
    BotInstance &BotInstance::operator=(const BotInstance &);

    BotInstance(const BotInstance &);

    BotInstance();

    ~BotInstance();

    void initCommandPipe(HANDLE pipe);

    void initDataManagmentPipe(HANDLE pipe);


    BotInstanceWidget* getWidget();

private:
    HANDLE _commandPipe;
    HANDLE _dataManagmentPipe;

    BotInstanceWidget *_widget;

public slots:
    void attack() const;
};

#endif // BOTINSTANCE_H
