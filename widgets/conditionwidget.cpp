#include "conditionwidget.h"
#include "ui_conditionwidget.h"
#include <QDebug>
/*
ConditionWidget::ConditionWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ConditionWidget)
{
    ui->setupUi(this);
}
*/
ConditionWidget::ConditionWidget(SkillUsage *skillUsage, Condition *condition, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ConditionWidget),
    _skillUsage(skillUsage),
    _condition(condition)
{
    ui->setupUi(this);
    ui->lblConditionName->setText(condition->getName());
    ui->horizontalLayout->addWidget(condition->createInputWidget());
    connect(ui->btnRemove, SIGNAL(pressed()), SLOT(deleteCondition()));
    _deleted = false;
}

ConditionWidget::~ConditionWidget()
{
    delete ui;
    qDebug() << "dead";
}

void ConditionWidget::updateCondition()
{
    if(_deleted)
    {
        qDebug() << "deleted";
        qDebug() << _skillUsage;
        qDebug() << _condition;
        auto &conditions = _skillUsage->getConditions();
        for(int i = 0; i < conditions.size(); ++i)
        {
            if(conditions.at(i).get() == _condition)
            {
                conditions.removeAt(i);
                break;
            }
        }
        //qDebug() << _skillUsage->getConditions().removeOne(std::shared_ptr(_condition));
    }
    else
    {
        qDebug() << "updated";
        _condition->retrieveInput();
    }
}

void ConditionWidget::deleteCondition()
{
    qDebug() << "delete";
    _deleted = true;
    hide();
}
