#ifndef SCONSOLE_H
#define SCONSOLE_H

#include <QObject>

class SConsole : public QObject
{
    Q_OBJECT
public:
    explicit SConsole(QObject *parent = nullptr);

signals:

public slots:
    void log(QString msg);
};

#endif // SCONSOLE_H
