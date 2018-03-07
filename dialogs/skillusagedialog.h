#ifndef SKILLUSAGEDIALOG_H
#define SKILLUSAGEDIALOG_H

#include <QDialog>

namespace Ui {
class SkillUsageDialog;
}

class SkillUsage;
class Condition;

class SkillUsageDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SkillUsageDialog(SkillUsage *skillUsage, QWidget *parent = 0);
    ~SkillUsageDialog();

private:
    void createWidgets(int row, Condition *condition);

    Ui::SkillUsageDialog *ui;

    SkillUsage *_skillUsage;

private slots:
    void saveSkillUsage();
    void addCondition();
};

#endif // SKILLUSAGEDIALOG_H
