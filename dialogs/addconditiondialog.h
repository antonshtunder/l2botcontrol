#ifndef ADDCONDITIONDIALOG_H
#define ADDCONDITIONDIALOG_H

#include <QDialog>
#include "conditions/relativepointscondition.h"

namespace Ui {
class AddConditionDialog;
}

class AddConditionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddConditionDialog(BotInstance *botInstance, Condition **result, QWidget *parent = 0);
    ~AddConditionDialog();

private:
    Ui::AddConditionDialog *ui;

    Condition **_result;
    BotInstance *_botInstance;

private slots:
    void addCondition();
};

#endif // ADDCONDITIONDIALOG_H
