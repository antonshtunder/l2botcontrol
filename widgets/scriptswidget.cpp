#include "scriptswidget.h"
#include "ui_scriptswidget.h"

ScriptsWidget::ScriptsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ScriptsWidget)
{
    ui->setupUi(this);
}

ScriptsWidget::~ScriptsWidget()
{
    delete ui;
}
