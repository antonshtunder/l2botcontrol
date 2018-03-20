#ifndef SCRIPTINGTHREAD_H
#define SCRIPTINGTHREAD_H

#include <QThread>



class ScriptingThread : public QThread
{
public:
    ScriptingThread();

protected:
    void run() override;
};

#endif // SCRIPTINGTHREAD_H
