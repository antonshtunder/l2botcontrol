#include "addconditiondialog.h"
#include "ui_addconditiondialog.h"

AddConditionDialog::AddConditionDialog(BotInstance *botInstance, Condition **result, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddConditionDialog),
    _result(result),
    _botInstance(botInstance)
{
    ui->setupUi(this);
    auto cb = ui->cbCondition;
    cb->addItem(RelativePointsCondition::getName(Conditions::PLAYER_HP_MORE_RELATIVE));
    cb->addItem(RelativePointsCondition::getName(Conditions::PLAYER_HP_LESS_RELATIVE));
    cb->addItem(RelativePointsCondition::getName(Conditions::PLAYER_MP_MORE_RELATIVE));
    cb->addItem(RelativePointsCondition::getName(Conditions::PLAYER_MP_LESS_RELATIVE));
    cb->addItem(RelativePointsCondition::getName(Conditions::PLAYER_CP_MORE_RELATIVE));
    cb->addItem(RelativePointsCondition::getName(Conditions::PLAYER_CP_LESS_RELATIVE));

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
    }
}
