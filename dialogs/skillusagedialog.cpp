#include "skillusagedialog.h"
#include "ui_skillusagedialog.h"
#include "dialogs/addconditiondialog.h"
#include "botcommands/skillusage.h"
#include <QLabel>
#include <QLineEdit>

SkillUsageDialog::SkillUsageDialog(SkillUsage *skillUsage, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SkillUsageDialog),
    _skillUsage(skillUsage)
{
    ui->setupUi(this);
    ui->checkEnabled->setChecked(_skillUsage->isEnabled());

    for(auto condition : skillUsage->getConditions())
    {
        auto rows = ui->conditionsLayout->rowCount();
        ui->conditionsLayout->addWidget(new QLabel(condition->getName()), rows, 0);
        ui->conditionsLayout->addWidget(condition->createInputWidget(), rows, 1);
    }

    connect(ui->buttons, SIGNAL(accepted()), SLOT(saveSkillUsage()));
    connect(ui->btnAddCondition, SIGNAL(pressed()), SLOT(addCondition()));
}

SkillUsageDialog::~SkillUsageDialog()
{
    delete ui;
}

void SkillUsageDialog::saveSkillUsage()
{
    _skillUsage->setEnabled(ui->checkEnabled->isChecked());
    auto conditions = _skillUsage->getConditions();
    for(auto condition : conditions)
    {
        condition->retrieveInput();
    }
}

void SkillUsageDialog::addCondition()
{
    Condition *newCondition = NULL;
    auto dialog = new AddConditionDialog(_skillUsage->getBotInstance(), &newCondition, this);
    dialog->exec();
    if(newCondition != NULL)
    {
        _skillUsage->getConditions().push_back(std::shared_ptr<Condition>(newCondition));
        auto rows = ui->conditionsLayout->rowCount();
        ui->conditionsLayout->addWidget(new QLabel(newCondition->getName()), rows, 0);
        ui->conditionsLayout->addWidget(newCondition->createInputWidget(), rows, 1);
    }
}
