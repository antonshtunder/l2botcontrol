#ifndef CONDITIONWIDGET_H
#define CONDITIONWIDGET_H

#include <QWidget>
#include "conditions/condition.h"
#include "botcommands/skillusage.h"

namespace Ui {
class ConditionWidget;
}

class ConditionWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ConditionWidget(SkillUsage *skillUsage, Condition *condition, QWidget *parent = 0);
    ~ConditionWidget();

    void updateCondition();

private:
    Ui::ConditionWidget *ui;
    SkillUsage *_skillUsage;
    Condition *_condition;
    bool _deleted = false;

private slots:
    void deleteCondition();
};

#endif // CONDITIONWIDGET_H
