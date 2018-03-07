#include "addconditiondialog.h"
#include "ui_addconditiondialog.h"
#include "conditions/effectcondition.h"
#include "conditions/botstatecondition.h"
#include "conditions/effectdurationcondition.h"

AddConditionDialog::AddConditionDialog(DWORD id, BotInstance *botInstance, Condition **result, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddConditionDialog),
    _result(result),
    _botInstance(botInstance),
    _id(id)
{
    ui->setupUi(this);
    auto cb = ui->cbCondition;
    cb->addItem(RelativePointsCondition::getName(Conditions::PLAYER_HP_MORE_RELATIVE));
    cb->addItem(RelativePointsCondition::getName(Conditions::PLAYER_HP_LESS_RELATIVE));
    cb->addItem(RelativePointsCondition::getName(Conditions::PLAYER_MP_MORE_RELATIVE));
    cb->addItem(RelativePointsCondition::getName(Conditions::PLAYER_MP_LESS_RELATIVE));
    cb->addItem(RelativePointsCondition::getName(Conditions::PLAYER_CP_MORE_RELATIVE));
    cb->addItem(RelativePointsCondition::getName(Conditions::PLAYER_CP_LESS_RELATIVE));
    cb->addItem(EffectCondition::getName(Conditions::PLAYER_HAS_EFFECT));
    cb->addItem(EffectCondition::getName(Conditions::PLAYER_DOESNT_HAVE_EFFECT));
    cb->addItem(EffectCondition::getName(Conditions::TARGET_HAS_EFFECT));
    cb->addItem(EffectCondition::getName(Conditions::TARGET_DOESNT_HAVE_EFFECT));
    cb->addItem(EffectDurationCondition::getName(Conditions::PLAYER_EFFECT_TIME_LEFT));
    cb->addItem(BotStateCondition::getName(Conditions::BOT_ATTACKING));
    cb->addItem(BotStateCondition::getName(Conditions::BOT_STANDING));
    cb->addItem(BotStateCondition::getName(Conditions::BOT_PICKINGUP));

    connect(this, SIGNAL(accepted()), SLOT(addCondition()));
}

AddConditionDialog::~AddConditionDialog()
{
    delete ui;
}

void AddConditionDialog::addCondition()
{
    switch(ui->cbCondition->currentIndex())
    {
    case 0:
        *_result = new RelativePointsCondition(_botInstance, Conditions::PLAYER_HP_MORE_RELATIVE, 0.5);
        break;
    case 1:
        *_result = new RelativePointsCondition(_botInstance, Conditions::PLAYER_HP_LESS_RELATIVE, 0.5);
        break;
    case 2:
        *_result = new RelativePointsCondition(_botInstance, Conditions::PLAYER_MP_MORE_RELATIVE, 0.5);
        break;
    case 3:
        *_result = new RelativePointsCondition(_botInstance, Conditions::PLAYER_MP_LESS_RELATIVE, 0.5);
        break;
    case 4:
        *_result = new RelativePointsCondition(_botInstance, Conditions::PLAYER_CP_MORE_RELATIVE, 0.5);
        break;
    case 5:
        *_result = new RelativePointsCondition(_botInstance, Conditions::PLAYER_CP_LESS_RELATIVE, 0.5);
        break;
    case 6:
        *_result = new EffectCondition(_botInstance, Conditions::PLAYER_HAS_EFFECT, _id);
        break;
    case 7:
        *_result = new EffectCondition(_botInstance, Conditions::PLAYER_DOESNT_HAVE_EFFECT, _id);
        break;
    case 8:
        *_result = new EffectCondition(_botInstance, Conditions::TARGET_HAS_EFFECT, _id);
        break;
    case 9:
        *_result = new EffectCondition(_botInstance, Conditions::TARGET_DOESNT_HAVE_EFFECT, _id);
        break;
    case 10:
        *_result = new EffectDurationCondition(_botInstance, Conditions::PLAYER_EFFECT_TIME_LEFT, _id, 5);
        break;
    case 11:
        *_result = new BotStateCondition(_botInstance, Conditions::BOT_ATTACKING);
        break;
    case 12:
        *_result = new BotStateCondition(_botInstance, Conditions::BOT_STANDING);
        break;
    case 13:
        *_result = new BotStateCondition(_botInstance, Conditions::BOT_PICKINGUP);
        break;
    }
}
