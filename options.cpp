#include "options.h"

Options Options::instance;

Options::Options()
{
    _dllPath = "C:\\Users\\Anton\\Documents\\QtProjects\\hackdlls\\build-abr-Desktop_Qt_5_9_2_MSVC2015_32bit-Debug\\debug\\abr.dll";
    _processName = "AsteriosGame.exe";
}

double Options::mapWidth() const
{
    return _mapWidth;
}

void Options::setMapWidth(double mapWidth)
{
    _mapWidth = mapWidth;
}

QString Options::processName() const
{
    return _processName;
}

void Options::setProcessName(const QString &processName)
{
    _processName = processName;
}

QString Options::dllPath() const
{
    return _dllPath;
}

void Options::setDllPath(const QString &dllPath)
{
    _dllPath = dllPath;
}
