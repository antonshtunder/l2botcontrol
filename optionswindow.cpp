#include "optionswindow.h"
#include "ui_optionswindow.h"

OptionsWindow::OptionsWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OptionsWindow)
{
    ui->setupUi(this);

    connectSignalsAndSlots();
}

OptionsWindow::~OptionsWindow()
{
    delete ui;
}

void OptionsWindow::showEvent(QShowEvent*)
{
    ui->txtDllPath->setText(Options::instance.dllPath());
    ui->txtProcName->setText(Options::instance.processName());
}

void OptionsWindow::connectSignalsAndSlots()
{
    connect(ui->btnOK, SIGNAL(pressed()), SLOT(saveState()));
    connect(ui->btnOK, SIGNAL(pressed()), SLOT(hide()));
    connect(ui->btnCancel, SIGNAL(pressed()), SLOT(hide()));
}

void OptionsWindow::saveState()
{
    Options::instance.setDllPath(ui->txtDllPath->text());
    Options::instance.setProcessName(ui->txtProcName->text());
}
