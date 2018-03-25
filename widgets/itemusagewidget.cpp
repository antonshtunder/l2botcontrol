#include "itemusagewidget.h"
#include "ui_itemusagewidget.h"
#include "instanceinfo/instanceinfobank.h"
#include <dialogs/additemusagedialog.h>
#include "bot/botinstance.h"
#include <QMessageBox>

ItemUsageWidget::ItemUsageWidget(ItemUsage *usage, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ItemUsageWidget),
    _itemUsage(usage)
{
    ui->setupUi(this);
    ui->lblName->setText(_itemUsage->getName());
    ui->lblIcon->setPixmap(InstanceInfoBank::instance()->getItemInfo(_itemUsage->getId()).getIcon());
    ui->layoutLeft->setAlignment(Qt::AlignLeft);
    ui->layoutRight->setAlignment(Qt::AlignRight);
    ui->horizontalLayout->setAlignment(ui->layoutLeft, Qt::AlignLeft);
    ui->horizontalLayout->setAlignment(ui->layoutRight, Qt::AlignRight);
    connect(ui->pbEdit, SIGNAL(pressed()), SLOT(edit()));
    connect(ui->pbRemove, SIGNAL(pressed()), SLOT(remove()));
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

void ItemUsageWidget::remove()
{
    QMessageBox msgBox;
    msgBox.setText("Do you really wish to remove item usage");
    msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Ok);
    connect(msgBox.button(QMessageBox::Ok), SIGNAL(pressed()), &msgBox, SLOT(accept()));
    if(msgBox.exec() == QDialog::Accepted)
    {
        qDebug() << "accepted";
        auto bot = _itemUsage->getBotInstance();
        bot->getConfiguration().removeItemUsage(_itemUsage);
        emit update(bot);
    }
}
