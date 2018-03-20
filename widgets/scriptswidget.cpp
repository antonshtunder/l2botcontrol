#include "scriptswidget.h"
#include "ui_scriptswidget.h"

#include <scripting/scriptingengine.h>

ScriptsWidget::ScriptsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ScriptsWidget)
{
    ui->setupUi(this);
    connect(ui->btnExecute, SIGNAL(pressed()), SLOT(execute()));
}

ScriptsWidget::~ScriptsWidget()
{
    delete ui;
}

void ScriptsWidget::execute()
{
    ScriptingEngine engine;
    engine.execute(ui->txtScript->toPlainText());
}
