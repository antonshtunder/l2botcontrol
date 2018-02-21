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
    qDebug() << "BotInstanceWidget()";
    QObject::connect(ui->btnStart, SIGNAL(pressed()), SLOT(startBotting()));
    QObject::connect(ui->btnStop, SIGNAL(pressed()), SLOT(stopBotting()));
}

BotInstanceWidget::~BotInstanceWidget()
{
    delete ui;
}

void BotInstanceWidget::updateInfo()
{
    if(_botInstance->isInGame())
    {
        ui->lblMessage->setText(QString::fromUtf16(_botInstance->l2representation.character.name));
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

void BotInstanceWidget::startBotting()
{
    _botInstance->startBotting();
}

void BotInstanceWidget::stopBotting()
{
    _botInstance->stopBotting();
}
