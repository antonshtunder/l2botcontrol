#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "lineageipc.h"
#include "bot/botmanager.h"

MainWindow *MainWindow::_instance = NULL;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    _skillListWidget(new SkillListWidget()),
    _effectList(new EffectList()),
    _testClientsTimer(this)
{
    ui->setupUi(this);
    _instance = this;

    _optionsWindow = new OptionsWindow;
    _mapWidget = new MapWidget;

    QVBoxLayout *mapTabLayout = new QVBoxLayout;
    mapTabLayout->addWidget(_mapWidget);
    ui->mapTab->setLayout(mapTabLayout);

    ui->botsCointainer->setLayout(&_botsLayout);
    _botsLayout.setAlignment(Qt::AlignTop);
    ui->skillsLayout->addWidget(_skillListWidget);

    ui->effectsTab->layout()->addWidget(_effectList);

    connectSlotsAndSignals();

    _testClientsTimer.start(200);
    _refreshDataTimer.start(200);
}

MainWindow *MainWindow::instance()
{
    return _instance;
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
    QObject::connect(BotManager::instance(), SIGNAL(clientDisconnected(BotInstance*)), SLOT(clientDisconnected(BotInstance*)));

    QObject::connect(&_testClientsTimer, SIGNAL(timeout()), BotManager::instance(), SLOT(testClients()));
    QObject::connect(&_refreshDataTimer, SIGNAL(timeout()), BotManager::instance(), SLOT(refreshData()));

    connect(ui->actionSaveBotConfiguration, SIGNAL(triggered(bool)), SLOT(saveConfigurationSlot()));
    connect(ui->actionLoadBotConfiguration, SIGNAL(triggered(bool)), SLOT(loadConfigurationSlot()));
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
    auto botInstances = BotManager::instance()->getBotInstances();
    if(botInstances.isEmpty())
    {
        ui->lblBotInstance->setText("no bot instance");
    }
    else
    {
        ui->lblBotInstance->setText(BotManager::instance()->getCurrentBotInstance()->name);
        for(auto instance : botInstances)
        {
            auto instanceWidget = instance->getWidget();
            if(instanceWidget->parent() == NULL)
            {
                _botsLayout.addWidget(instanceWidget);
            }
            instanceWidget->updateInfo();
        }
        auto currentBotInstance = BotManager::instance()->getCurrentBotInstance();
        _skillListWidget->update(currentBotInstance);
        _effectList->update(currentBotInstance);
        _mapWidget->updateInfo();
    }
}

void MainWindow::saveConfigurationSlot()
{
    auto botInstance = BotManager::instance()->getCurrentBotInstance();
    if(botInstance == NULL)
        return;

    auto path = QFileDialog::getSaveFileName(this, "Configuration text file", "C:/", "Text file (*.txt)");
    if(!path.isEmpty())
    {
        botInstance->getConfiguration().saveConfiguration(path);
    }
}

void MainWindow::loadConfigurationSlot()
{
    auto botInstance = BotManager::instance()->getCurrentBotInstance();
    if(botInstance == NULL)
        return;

    auto path = QFileDialog::getOpenFileName(this, "Configuration text file", "C:/", "Text file (*.txt)");
    if(!path.isEmpty())
    {
        botInstance->getConfiguration().loadConfiguration(path);
    }
}

void MainWindow::clientDisconnected(BotInstance *botInstance)
{
    _botsLayout.removeWidget(botInstance->getWidget());
    delete botInstance;
    updateUI();
}
