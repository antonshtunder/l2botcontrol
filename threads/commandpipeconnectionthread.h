#ifndef COMMANDPIPECONNECTIONTHREAD_H
#define COMMANDPIPECONNECTIONTHREAD_H

#include <QThread>



class CommandPipeConnectionThread : public QThread
{
public:
    CommandPipeConnectionThread();

protected:
    void run() override;
};

#endif // COMMANDPIPECONNECTIONTHREAD_H
