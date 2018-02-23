#include "commandpipeconnectionthread.h"
#include "lineageipc.h"
#include <Windows.h>
#include "ipcmanager.h"
#include "botinstance.h"

CommandPipeConnectionThread::CommandPipeConnectionThread()
{

}

void CommandPipeConnectionThread::run()
{
    DWORD PID;
    while(true)
    {
        auto pipe = l2ipc::createCommandPipe();
        if(ConnectNamedPipe(pipe, NULL))
        {
            GetNamedPipeClientProcessId(pipe, &PID);
            if(!IPCManager::instance()->_botInstances.keys().contains(PID))
            {
                qDebug("a");
                IPCManager::instance()->addBotInstance(PID, new BotInstance(PID));
            }
            IPCManager::instance()->_botInstances[PID]->initCommandPipe(pipe);
        }
    }
}
