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
    explicit ConditionWidget(Usage *usage, Condition *condition, QWidget *parent = 0);
    ~ConditionWidget();

    void updateCondition();

private:
    Ui::ConditionWidget *ui;
    Usage *_usage;
    Condition *_condition;
    bool _deleted = false;

private slots:
    void deleteCondition();
};

#endif // CONDITIONWIDGET_H
