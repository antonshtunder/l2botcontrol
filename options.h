#ifndef OPTIONS_H
#define OPTIONS_H

#include <QString>

class Options
{
public:

    static Options instance;

    QString dllPath() const;
    void setDllPath(const QString &dllPath);

    QString processName() const;
    void setProcessName(const QString &processName);

    double mapWidth() const;
    void setMapWidth(double mapWidth);

private:
    Options();
    QString _dllPath;
    QString _processName;
    double _mapWidth = 558500.0;
};

#endif // OPTIONS_H
