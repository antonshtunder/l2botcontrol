#include "botinstancewidget.h"
#include "ui_botinstancewidget.h"
#include "botinstance.h"
#include "botmanager.h"

BotInstanceWidget::BotInstanceWidget(BotInstance *botInstance, QWidget *parent) :
    QFrame(parent),
    ui(new Ui::BotInstanceWidget),
    _botInstance(botInstance)
{
    ui->setupUi(this);
}

BotInstanceWidget::~BotInstanceWidget()
{
    delete ui;
}

void BotInstanceWidget::updateInfo()
{
    if(_botInstance->isInGame())
    {
        qDebug("inGame3");
        ui->lblMessage->setText(QString::fromUtf16(_botInstance->l2representation.character.name));
        qDebug("inGame4");
    }
    else
    {
        ui->lblMessage->setText("Not in game");
    }
}

void BotInstanceWidget::mousePressEvent(QMouseEvent*)
{
    BotManager::instance()->setBotInstance(_botInstance);
}
