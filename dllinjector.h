#ifndef DLLINJECTOR_H
#define DLLINJECTOR_H

#include <Windows.h>
#include <vector>

class DllInjector
{
public:
    DllInjector();

    bool InjectToWindow(LPCWSTR windowTitle, LPCWSTR dllPath);
    bool InjectToProcess(LPCWSTR processName, LPCWSTR dllPath);

private:
    bool InjectDll(DWORD processID, LPCWSTR dllPath);
    std::vector<DWORD> injectedPID;
};

#endif // DLLINJECTOR_H
