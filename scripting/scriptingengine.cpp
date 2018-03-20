#include "sbot.h"
#include "sconsole.h"
#include "scriptingengine.h"
#include <QJSEngine>
#include <bot/botmanager.h>
#include <QDebug>
#include <QtConcurrent>

ScriptingEngine::ScriptingEngine()
{

}

void ScriptingEngine::execute(const QString &script)
{
    QtConcurrent::run([this, script] {
        QJSEngine engine;
        SBot bot(BotManager::instance()->getCurrentBotInstance());
        auto botObject = engine.newQObject(&bot);
        engine.globalObject().setProperty("Bot", botObject);

        SConsole console;
        auto consoleObject = engine.newQObject(&console);
        engine.globalObject().setProperty("console", consoleObject);

        engine.evaluate(script);
    });

}
