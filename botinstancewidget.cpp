#include "botinstancewidget.h"
#include "ui_botinstancewidget.h"

BotInstanceWidget::BotInstanceWidget(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::BotInstanceWidget)
{
    ui->setupUi(this);
}

BotInstanceWidget::~BotInstanceWidget()
{
    delete ui;
}
