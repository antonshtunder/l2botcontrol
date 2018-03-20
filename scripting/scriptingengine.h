#ifndef SCRIPTINGENGINE_H
#define SCRIPTINGENGINE_H

#include <QString>

class SBot;

class ScriptingEngine
{
public:
    ScriptingEngine();

    void execute(const QString &script);

private:
    SBot *_bot = NULL;
};

#endif // SCRIPTINGENGINE_H
