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
    Condition::fillConditionComboBox(ui->cbCondition);

    connect(this, SIGNAL(accepted()), SLOT(addCondition()));
}

AddConditionDialog::~AddConditionDialog()
{
    delete ui;
}

void AddConditionDialog::addCondition()
{
    *_result = Condition::processConditionComboBox(ui->cbCondition, _botInstance, _id);
}
