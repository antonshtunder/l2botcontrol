#ifndef CONDITION_H
#define CONDITION_H

#include <QString>

class BotInstance;
class QWidget;

enum Conditions
{
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
    BOT_STANDING,
    BOT_ATTACKING,
    BOT_PICKINGUP
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

    QWidget *lastWidget() const;

    static QString &getName(Conditions type);

protected:
    BotInstance *_botInstance = NULL;
    Conditions _type;
    QWidget *_lastWidget;
};

#endif // CONDITION_H
