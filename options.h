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

private:
    Options();
    QString _dllPath;
    QString _processName;
};

#endif // OPTIONS_H
