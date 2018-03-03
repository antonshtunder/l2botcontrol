#include "dllinjector.h"
#include <QtCore>
#include <TlHelp32.h>

#pragma comment(lib, "User32.lib")

static char __buffer__[256];
#define I_TO_A(x) itoa(x, __buffer__, 10)
#define ALERTA(x) MessageBoxA(NULL, "Alert", x, MB_OK);
#define ALERTW(x) MessageBoxW(NULL, L"Alert", x, MB_OK);

DllInjector::DllInjector()
{

}

bool DllInjector::InjectToWindow(LPCWSTR windowTitle, LPCWSTR dllPath)
{
    auto window = FindWindowW(NULL, windowTitle);
    if(window == NULL)
    {
        return false;
    }

    DWORD processID;
    GetWindowThreadProcessId(window, &processID);

    return InjectDll(processID, dllPath);
}

bool DllInjector::InjectToProcess(LPCWSTR processName, LPCWSTR dllPath)
{
    PROCESSENTRY32W pe32;
    auto snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if(snapshot == INVALID_HANDLE_VALUE)
        return false;

    pe32.dwSize = sizeof(PROCESSENTRY32W);

    if(!Process32FirstW(snapshot, &pe32))
        return false;

    do
    {
        if(wcscmp(processName, pe32.szExeFile) == 0)
        {
            qDebug() << "attach";
            if(!InjectDll(pe32.th32ProcessID, dllPath))
                return false;
        }
    } while(Process32NextW(snapshot, &pe32));

    return true;
}

bool DllInjector::InjectDll(DWORD processID, LPCWSTR dllPath)
{
    auto process = OpenProcess(PROCESS_VM_READ | PROCESS_VM_WRITE | PROCESS_VM_OPERATION, FALSE, processID);
    if(process != NULL)
    {
        auto kernel32 = GetModuleHandleW(L"Kernel32.dll");
        auto loadLibraryFunction = GetProcAddress(kernel32, "LoadLibraryW");

        size_t paramSize = (wcslen(dllPath) + 1) * 2;
        auto paramAddress = VirtualAllocEx(process, NULL, paramSize, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
        WriteProcessMemory(process, paramAddress, dllPath, paramSize, NULL);
        auto thread = CreateRemoteThread(process, NULL, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(loadLibraryFunction), paramAddress, 0, NULL);
        CloseHandle(thread);
        CloseHandle(process);
        return true;
    }

    return false;
}
