#ifndef DATAMANAGMENTPIPECONNECTIONTHREAD_H
#define DATAMANAGMENTPIPECONNECTIONTHREAD_H

#include <QThread>

class DataManagmentPipeConnectionThread : public QThread
{
public:
    DataManagmentPipeConnectionThread();

protected:
    void run() override;
};

#endif // DATAMANAGMENTPIPECONNECTIONTHREAD_H
