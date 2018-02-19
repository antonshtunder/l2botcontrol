#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "lineageipc.h"
#include "botmanager.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    _optionsWindow = new OptionsWindow;

    ui->botsCointainer->setLayout(&_botsLayout);
    _botsLayout.setAlignment(Qt::AlignTop);

/*
    _botsLayout.addWidget(new BotInstanceWidget(ui->botsCointainer));
    _botsLayout.addWidget(new BotInstanceWidget(ui->botsCointainer));
    ui->gameInfoContainer->setCurrentIndex(1);
*/
    connectSlotsAndSignals();
}



MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::connectSlotsAndSignals()
{
    QObject::connect(ui->actionOptions, SIGNAL(triggered(bool)), _optionsWindow, SLOT(show()));
    QObject::connect(ui->actionAttach, SIGNAL(triggered(bool)), SLOT(attach()));
    QObject::connect(ui->btnAttack, SIGNAL(pressed()), BotManager::instance(), SLOT(attack()));
    QObject::connect(BotManager::instance(), SIGNAL(updateUISignal()), SLOT(updateUI()));
}

void MainWindow::attach()
{
    if(!_injector.InjectToProcess(Options::instance.processName().toStdWString().c_str(),
                              Options::instance.dllPath().toStdWString().c_str()))
    {
        QErrorMessage message;
        message.showMessage("Injection failed");
    }
}

void MainWindow::updateUI()
{

}
