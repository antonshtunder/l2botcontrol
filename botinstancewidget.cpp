#include "botinstancewidget.h"
#include "ui_botinstancewidget.h"
#include "botinstance.h"
#include "botmanager.h"
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
    connect(ui->btnStart, SIGNAL(pressed()), SLOT(startBotting()));
    connect(ui->btnStop, SIGNAL(pressed()), SLOT(stopBotting()));
    connect(ui->btnDetach, SIGNAL(pressed()), SLOT(detach()));

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
