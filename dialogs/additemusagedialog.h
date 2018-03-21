#ifndef ADDITEMUSAGEDIALOG_H
#define ADDITEMUSAGEDIALOG_H

#include <QDialog>
#include <botcommands/itemusage.h>

namespace Ui {
class AddItemUsageDialog;
}

class AddItemUsageDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddItemUsageDialog(QWidget *parent = 0);
    ~AddItemUsageDialog();

private:
    Ui::AddItemUsageDialog *ui;

    ItemUsage *_itemUsage;
};

#endif // ADDITEMUSAGEDIALOG_H
