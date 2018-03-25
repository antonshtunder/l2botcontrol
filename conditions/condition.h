#ifndef CONDITION_H
#define CONDITION_H

#include <QString>
#include <QJSonObject>
#include <QComboBox>
#include <Windows.h>

class BotInstance;
class QWidget;

enum Conditions
{
    NONE,
    PLAYER_HP_MORE_RELATIVE,
    PLAYER_HP_LESS_RELATIVE,
    PLAYER_MP_MORE_RELATIVE,
    PLAYER_MP_LESS_RELATIVE,
    PLAYER_CP_MORE_RELATIVE,
    PLAYER_CP_LESS_RELATIVE,
    PLAYER_HAS_EFFECT,
    PLAYER_DOESNT_HAVE_EFFECT,
    TARGET_HAS_EFFECT,
    TARGET_DOESNT_HAVE_EFFECT,
    PLAYER_EFFECT_TIME_LEFT,
    BOT_STANDING,
    BOT_ATTACKING,
    BOT_PICKINGUP,
    TARGET_RACE_IS
};

enum JsonType
{
    POINTS_RELATIVE,
    EFFECT_PRESENCE,
    EFFECT_TIME,
    BOT_STATE,
    TARGET_RACE
};

class Condition
{
public:
    Condition(BotInstance *botInstance, Conditions type);
    virtual ~Condition();

    virtual bool test();

    virtual QString &getName() const;

    virtual QWidget *createInputWidget();

    virtual void retrieveInput();

    virtual QJsonObject createJsonRepresentation();
    virtual void parseJsonRepresentation(QJsonObject);

    QWidget *lastWidget() const;

    static QString &getName(Conditions type);

    static void fillConditionComboBox(QComboBox *cb);
    static Condition *processConditionComboBox(QComboBox *cb, BotInstance *botInstance, DWORD id);

protected:
    BotInstance *_botInstance = NULL;
    Conditions _type;
    QWidget *_lastWidget;
};

#endif // CONDITION_H
