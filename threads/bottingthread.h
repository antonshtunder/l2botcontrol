#ifndef BOTTINGTHREAD_H
#define BOTTINGTHREAD_H

#include <QThread>

class BotInstance;


class BottingThread : public QThread
{
public:
    BottingThread(BotInstance* botInstance);

    void stopBotting();

private:
    BotInstance* _bot;
    bool botting = false;

    // QThread interface
protected:
    void run() override;
};

#endif // BOTTINGTHREAD_H
