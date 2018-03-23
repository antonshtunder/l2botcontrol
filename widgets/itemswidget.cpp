#include "itemswidget.h"
#include "itemusagewidget.h"
#include "ui_itemswidget.h"
#include "bot/botinstance.h"

#include <bot/botmanager.h>

#include <dialogs/additemusagedialog.h>

ItemsWidget::ItemsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ItemsWidget)
{
    ui->setupUi(this);
    _lastBotInstance = NULL;
    connect(ui->btnAddUsage, SIGNAL(pressed()), SLOT(addUsage()));
}

ItemsWidget::~ItemsWidget()
{
    delete ui;
}

void ItemsWidget::update(BotInstance *botInstance, bool force)
{
    if(!force)
    {
        if(_lastBotInstance == botInstance)
        {
            return;
        }
        _lastBotInstance = botInstance;
    }

    qDebug() << "ItemsWidget::update()";

    QWidget *itemUsagesWgt = new QWidget;
    QVBoxLayout *itemUsageContainer = new QVBoxLayout;
    itemUsageContainer->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    for(auto itemUsage : botInstance->getConfiguration().getItemUsages())
    {
        auto itemUsageWgt = new ItemUsageWidget(itemUsage.get());
        itemUsageContainer->addWidget(itemUsageWgt);
        connect(itemUsageWgt, SIGNAL(update(BotInstance*)), SLOT(update(BotInstance*)));
    }
    itemUsagesWgt->setLayout(itemUsageContainer);
    ui->scrollArea->setWidget(itemUsagesWgt);
}

void ItemsWidget::addUsage()
{
    auto bot = BotManager::instance()->getCurrentBotInstance();
    if(bot == NULL || !bot->isInGame())
        return;

    ItemRepresentation tmp;
    ItemUsage *usage = new ItemUsage(bot, tmp);
    AddItemUsageDialog iuDialog(usage, this);
    auto result = iuDialog.exec();
    if(result == QDialog::Accepted)
    {
        bot->getConfiguration().getItemUsages().append(std::shared_ptr<ItemUsage>(usage));
        update(bot);
        qDebug() << "item usage added";
    }
    else
    {
        qDebug() << "no item usage added";
        delete usage;
    }
    bot->getConfiguration().getItemUsages();
}
