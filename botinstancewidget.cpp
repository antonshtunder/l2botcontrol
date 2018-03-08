#include "botinstancewidget.h"
#include "ui_botinstancewidget.h"
#include "bot/botinstance.h"
#include "bot/botmanager.h"
#include "mainwindow.h"

BotInstanceWidget::BotInstanceWidget(BotInstance *botInstance, QWidget *parent) :
    QFrame(parent),
    ui(new Ui::BotInstanceWidget),
    _botInstance(botInstance),
    _contextMenu(tr("Context menu"), this),
    _startAction("Start botting", this),
    _stopAction("Stop botting", this),
    _detachAction("Detach bot", this)
{
    ui->setupUi(this);

    connect(&_startAction, SIGNAL(triggered()), SLOT(startBotting()));
    _contextMenu.addAction(&_startAction);

    connect(&_stopAction, SIGNAL(triggered()), SLOT(stopBotting()));
    _contextMenu.addAction(&_stopAction);

    connect(&_detachAction, SIGNAL(triggered()), SLOT(detach()), Qt::QueuedConnection);
    _contextMenu.addAction(&_detachAction);

    setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, SIGNAL(customContextMenuRequested(const QPoint &)),
            this, SLOT(showContextMenu(const QPoint &)));
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
        ui->lblHP->setText(QString("%1/%2").arg(QString::number(_botInstance->l2representation.character.hp))
                           .arg(QString::number(_botInstance->l2representation.character.maxHp)));
        ui->lblMP->setText(QString("%1/%2").arg(QString::number(_botInstance->l2representation.character.mp))
                           .arg(QString::number(_botInstance->l2representation.character.maxMp)));
        ui->lblCP->setText(QString("%1/%2").arg(QString::number(_botInstance->l2representation.character.cp))
                           .arg(QString::number(_botInstance->l2representation.character.maxCp)));
    }
    else
    {
        ui->lblMessage->setText("Not in game");
    }
    if(_botInstance->isBotting())
    {
        ui->lblBotting->setText("botting");
    }
    else
    {
        ui->lblBotting->setText("not botting");
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

void BotInstanceWidget::detach()
{
    _botInstance->detach();
}

void BotInstanceWidget::showContextMenu(const QPoint &pos)
{
   _contextMenu.exec(mapToGlobal(pos));
}
