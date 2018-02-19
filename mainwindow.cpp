#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "lineageipc.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    _optionsWindow = new OptionsWindow;


    ui->botsCointainer->setLayout(&_botsLayout);
    _botsLayout.setAlignment(Qt::AlignTop);
    _botsLayout.addWidget(new BotInstanceWidget(ui->botsCointainer));
    _botsLayout.addWidget(new BotInstanceWidget(ui->botsCointainer));
    ui->gameInfoContainer->setCurrentIndex(1);

    connectSlotsAndSignals();
}



MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::connectSlotsAndSignals()
{
    QObject::connect(ui->actionOptions, SIGNAL(triggered(bool)), _optionsWindow, SLOT(show()));
}
