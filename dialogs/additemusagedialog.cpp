#include "additemusagedialog.h"
#include "ui_additemusagedialog.h"
#include "dialogs/addconditiondialog.h"
#include "botcommands/skillusage.h"
#include <QLabel>
#include <QLineEdit>
#include <QDebug>
#include "widgets/conditionwidget.h"

AddItemUsageDialog::AddItemUsageDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddItemUsageDialog)
{
    ui->setupUi(this);
}

AddItemUsageDialog::~AddItemUsageDialog()
{
    delete ui;
}

void AddItemUsageDialog::saveSkillUsage()
{
    _skillUsage->setEnabled(ui->checkEnabled->isChecked());
    auto size = ui->conditionsLayout->count();
    qDebug() << size;
    for(int i = 0; i < size; ++i)
    {
        reinterpret_cast<ConditionWidget*>(ui->conditionsLayout->itemAt(i)->widget())->updateCondition();
        /*qDebug() << i;
        qDebug() << ui->conditionsLayout->rowCount();
        qDebug() << ui->conditionsLayout->itemAtPosition(i + 1, 0)->widget()->isVisible();*/
    }
}

void AddItemUsageDialog::addCondition()
{
    Condition *newCondition = NULL;
    auto dialog = new AddConditionDialog(_skillUsage->getId(), _skillUsage->getBotInstance(), &newCondition, this);
    dialog->exec();
    if(newCondition != NULL)
    {
        _skillUsage->getConditions().push_back(std::shared_ptr<Condition>(newCondition));
        //auto rows = ui->conditionsLayout->rowCount();
        createWidgets(0, newCondition);
    }
}
