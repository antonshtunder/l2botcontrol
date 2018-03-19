#include "actionconfigurationwidget.h"
#include "ui_actionconfigurationwidget.h"

#include <bot/botmanager.h>

ActionConfigurationWidget::ActionConfigurationWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ActionConfigurationWidget)
{
    ui->setupUi(this);
    connect(ui->btnAssist, SIGNAL(pressed()), SLOT(assist()));
    connect(ui->btnUpdate, SIGNAL(pressed()), SLOT(updateSlot()));
    connect(ui->btnRevert, SIGNAL(pressed()), SLOT(revertSlot()));
    connect(ui->btnAcceptAction, SIGNAL(pressed()), SLOT(acceptAction()));
    connect(ui->btnNpcChat, SIGNAL(pressed()), SLOT(npcChatSlot()));
}

ActionConfigurationWidget::~ActionConfigurationWidget()
{
    delete ui;
}

void ActionConfigurationWidget::update(BotInstance *botInstance, bool force)
{
    if(!force && _botInstance == botInstance)
    {
        return;
    }
    _botInstance = botInstance;
    auto &configuration = botInstance->getConfiguration();
    switch(configuration.getTargeting())
    {
    case Targeting::ASSIST:
        ui->rbAssist->setChecked(true);
        break;
    case Targeting::MOB_IN_AREA:
        ui->rbMobInArea->setChecked(true);
        break;
    }
    ui->txtAssistPlayerName->setText(configuration.getAssistPlayerName());
}

void ActionConfigurationWidget::assist()
{
    auto bot = BotManager::instance()->getCurrentBotInstance();
    if(bot != NULL)
    {
        bot->assist(ui->txtAssistPlayerName->text());
    }
}

void ActionConfigurationWidget::updateSlot()
{
    auto &configuration = _botInstance->getConfiguration();
    if(ui->rbAssist->isChecked())
    {
        configuration.setTargeting(Targeting::ASSIST);
    }
    else if(ui->rbMobInArea->isChecked())
    {
        configuration.setTargeting(Targeting::MOB_IN_AREA);
    }
    configuration.setAssistPlayerName(ui->txtAssistPlayerName->text());
}

void ActionConfigurationWidget::revertSlot()
{
    update(_botInstance, true);
}

void ActionConfigurationWidget::npcChatSlot()
{
    _botInstance->npcChat(ui->spNpcChatId->value());
}

void ActionConfigurationWidget::acceptAction()
{
    _botInstance->acceptAction();
}
