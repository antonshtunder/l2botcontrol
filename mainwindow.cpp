#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "lineageipc.h"
#include "bot/botmanager.h"
#include "misc/lineagemapcontroller.h"

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
    _mapControlsWidget = new MapControlsWidget;
    _scriptsWgt = new ScriptsWidget;
    _itemsWidget = new ItemsWidget;

    QVBoxLayout *mapTabLayout = new QVBoxLayout;
    mapTabLayout->setSpacing(0);

    _mapControls = new QToolBar;
    _mapControlsActionGroup = new QActionGroup(this);
    _mapControls->setOrientation(Qt::Horizontal);
    QAction *mapActionAction = new QAction("Action", _mapControlsActionGroup);
    mapActionAction->setCheckable(true);
    mapActionAction->setChecked(true);
    mapActionAction->setProperty("MapAction", MapAction::ACTION);
    QAction *mapAddNodeAction = new QAction("Add node", _mapControlsActionGroup);
    mapAddNodeAction->setCheckable(true);
    mapAddNodeAction->setProperty("MapAction", MapAction::ADD_NODE);
    QAction *mapMoveNodeAction = new QAction("Move node", _mapControlsActionGroup);
    mapMoveNodeAction->setCheckable(true);
    mapMoveNodeAction->setProperty("MapAction", MapAction::MOVE_NODE);
    QAction *mapRemoveNodeAction = new QAction("Remove node", _mapControlsActionGroup);
    mapRemoveNodeAction->setCheckable(true);
    mapRemoveNodeAction->setProperty("MapAction", MapAction::REMOVE_NODE);
    QAction *mapClearNodesAction = new QAction("Clear nodes");
    mapClearNodesAction->setCheckable(false);
    mapClearNodesAction->setProperty("MapAction", MapAction::CLEAR_NODES);

    _mapControls->addAction(mapActionAction);
    _mapControls->addAction(mapAddNodeAction);
    _mapControls->addAction(mapMoveNodeAction);
    _mapControls->addAction(mapRemoveNodeAction);
    _mapControls->addAction(mapClearNodesAction);
    connect(_mapControls, SIGNAL(actionTriggered(QAction*)), SLOT(mapControlSlot(QAction*)));

    mapTabLayout->addWidget(_mapControls);
    mapTabLayout->addWidget(_mapWidget);
    ui->mapTab->setLayout(mapTabLayout);

    ui->botsCointainer->setLayout(&_botsLayout);
    _botsLayout.setAlignment(Qt::AlignTop);
    ui->skillsLayout->addWidget(_skillListWidget);

    _actionConfWgt = new ActionConfigurationWidget(ui->actionsTab);

    ui->effectsTab->layout()->addWidget(_effectList);
    ui->scriptsTab->layout()->addWidget(_scriptsWgt);
    ui->itemsTab->layout()->addWidget(_itemsWidget);

    connectSlotsAndSignals();

    _testClientsTimer.start(200);
    _refreshDataTimer.start(100);
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

    }
    else
    {

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
        _itemsWidget->update(currentBotInstance, false);
        _actionConfWgt->update(currentBotInstance, false);
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

void MainWindow::mapControlSlot(QAction *action)
{
    auto bot = BotManager::instance()->getCurrentBotInstance();
    if(bot == NULL || !bot->isInGame())
    {
        return;
    }
    if(action->property("MapAction") == MapAction::CLEAR_NODES)
    {
        LineageMapController::instance()->clearNodes();
    }
    else
    {
        LineageMapController::instance()->setAction(static_cast<MapAction>(action->property("MapAction").toInt()));
    }
}

void MainWindow::clientDisconnected(BotInstance *botInstance)
{
    _botsLayout.removeWidget(botInstance->getWidget());
    delete botInstance;
    updateUI();
}
