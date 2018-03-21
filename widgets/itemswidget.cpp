#include "itemswidget.h"
#include "ui_itemswidget.h"
#include "bot/botinstance.h"

ItemsWidget::ItemsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ItemsWidget)
{
    ui->setupUi(this);
    _lastBotInstance = NULL;
}

ItemsWidget::~ItemsWidget()
{
    delete ui;
}

void ItemsWidget::update(BotInstance *botInstance)
{
    if(_lastBotInstance == botInstance)
    {
        return;
    }
    _lastBotInstance = botInstance;


}
