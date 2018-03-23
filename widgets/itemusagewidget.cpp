#include "itemusagewidget.h"
#include "ui_itemusagewidget.h"

#include <dialogs/additemusagedialog.h>

ItemUsageWidget::ItemUsageWidget(ItemUsage *usage, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ItemUsageWidget),
    _itemUsage(usage)
{
    ui->setupUi(this);
    ui->lblName->setText(_itemUsage->getName());
    connect(ui->pbEdit, SIGNAL(pressed()), SLOT(edit()));
}

ItemUsageWidget::~ItemUsageWidget()
{
    delete ui;
}

void ItemUsageWidget::edit()
{
    AddItemUsageDialog dlg(_itemUsage);
    if(dlg.exec() == QDialog::Accepted)
    {
        emit update(_itemUsage->getBotInstance());
    }
}
