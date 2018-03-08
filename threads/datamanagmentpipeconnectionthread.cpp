#include "datamanagmentpipeconnectionthread.h"
#include "lineageipc.h"
#include <Windows.h>
#include "ipcmanager.h"
#include "bot/botinstance.h"

DataManagmentPipeConnectionThread::DataManagmentPipeConnectionThread()
{

}

void DataManagmentPipeConnectionThread::run()
{
    DWORD PID;
    while(true)
    {
        auto pipe = l2ipc::createDataManagmentPipe();
        if(ConnectNamedPipe(pipe, NULL))
        {
            GetNamedPipeClientProcessId(pipe, &PID);
            if(!IPCManager::instance()->_botInstances.keys().contains(PID))
            {
                qDebug("a");
                IPCManager::instance()->addBotInstance(PID, new BotInstance(PID));
            }
            IPCManager::instance()->_botInstances[PID]->initDataManagmentPipe(pipe);
        }
    }
}
