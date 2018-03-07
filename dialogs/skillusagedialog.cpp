#include "skillusagedialog.h"
#include "ui_skillusagedialog.h"
#include "dialogs/addconditiondialog.h"
#include "botcommands/skillusage.h"
#include <QLabel>
#include <QLineEdit>
#include <QDebug>
#include "widgets/conditionwidget.h"

SkillUsageDialog::SkillUsageDialog(SkillUsage *skillUsage, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SkillUsageDialog),
    _skillUsage(skillUsage)
{
    ui->setupUi(this);
    ui->checkEnabled->setChecked(_skillUsage->isEnabled());

    ui->conditionsLayout->setAlignment(Qt::AlignTop);

    for(auto condition : skillUsage->getConditions())
    {
        qDebug() << "ugu";
        createWidgets(0, condition.get());
    }

    connect(ui->buttons, SIGNAL(accepted()), SLOT(saveSkillUsage()));
    connect(ui->btnAddCondition, SIGNAL(pressed()), SLOT(addCondition()));
}

SkillUsageDialog::~SkillUsageDialog()
{
    delete ui;
}

void SkillUsageDialog::createWidgets(int row, Condition *condition)
{
    ConditionWidget *wgt = new ConditionWidget(_skillUsage, condition);
    ui->conditionsLayout->addWidget(wgt);
    /*QWidget *conditionWgt = new QWidget;
    QHBoxLayout *conditionLayout = new QHBoxLayout;
    QPushButton *deleteSkillUsageBtn = new QPushButton;
    deleteSkillUsageBtn->setProperty("rowNum", row);
    deleteSkillUsageBtn->setIcon(QIcon("C:/l2data/remove.ico"));
    deleteSkillUsageBtn->setMaximumWidth(26);
    conditionLayout->addWidget(deleteSkillUsageBtn);
    conditionLayout->addWidget(new QLabel(condition->getName()));
    conditionLayout->addWidget(condition->createInputWidget());
    conditionWgt->setLayout(conditionLayout);
    ui->conditionsLayout->addWidget(conditionWgt, row, 0);
    QObject::connect(deleteSkillUsageBtn, SIGNAL(pressed()), conditionWgt, SLOT(hide()));*/
}

void SkillUsageDialog::saveSkillUsage()
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

void SkillUsageDialog::addCondition()
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
