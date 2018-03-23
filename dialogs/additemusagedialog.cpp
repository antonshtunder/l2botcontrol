#include "additemusagedialog.h"
#include "ui_additemusagedialog.h"
#include "dialogs/addconditiondialog.h"
#include "botcommands/skillusage.h"
#include <QLabel>
#include <QLineEdit>
#include <QDebug>
#include "widgets/conditionwidget.h"
#include <bot/botmanager.h>

AddItemUsageDialog::AddItemUsageDialog(ItemUsage *itemUsage, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddItemUsageDialog),
    _itemUsage(itemUsage)
{
    ui->setupUi(this);
    connect(ui->buttons, SIGNAL(accepted()), SLOT(saveItemUsage()));
    connect(ui->btnAddCondition, SIGNAL(pressed()), SLOT(addCondition()));
    ui->checkEnabled->setChecked(itemUsage->isEnabled());
    ui->sbId->setValue(itemUsage->getId());
    ui->txtName->setText(itemUsage->getName());
    ui->conditionsLayout->setAlignment(Qt::AlignTop);

    for(auto condition : _itemUsage->getConditions())
    {
        ConditionWidget *wgt = new ConditionWidget(_itemUsage, condition.get());
        ui->conditionsLayout->addWidget(wgt);
    }
}

AddItemUsageDialog::~AddItemUsageDialog()
{
    delete ui;
}



void AddItemUsageDialog::saveItemUsage()
{
    _itemUsage->setEnabled(ui->checkEnabled->isChecked());
    auto size = ui->conditionsLayout->count();
    qDebug() << size;
    for(int i = 0; i < size; ++i)
    {
        reinterpret_cast<ConditionWidget*>(ui->conditionsLayout->itemAt(i)->widget())->updateCondition();
    }
    _itemUsage->setItem(ui->sbId->value());
    _itemUsage->setName(ui->txtName->text());
}

void AddItemUsageDialog::addCondition()
{
    Condition *newCondition = NULL;
    auto dialog = new AddConditionDialog(ui->sbId->value(), BotManager::instance()->getCurrentBotInstance(), &newCondition, this);
    dialog->exec();
    if(newCondition != NULL)
    {
        _itemUsage->getConditions().push_back(std::shared_ptr<Condition>(newCondition));
        ConditionWidget *wgt = new ConditionWidget(_itemUsage, newCondition);
        ui->conditionsLayout->addWidget(wgt);
    }
}
