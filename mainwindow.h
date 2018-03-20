#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include "botinstancewidget.h"
#include "dllinjector.h"
#include "optionswindow.h"
#include "widgets/mapwidget.h"
#include "widgets/effectlist.h"
#include "widgets/mapcontrolswidget.h"
#include "widgets/actionconfigurationwidget.h"
#include "widgets/scriptswidget.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    static MainWindow *instance();
    ~MainWindow();

private:
    void connectSlotsAndSignals();

    Ui::MainWindow *ui;
    static MainWindow *_instance;

    OptionsWindow *_optionsWindow;
    MapWidget *_mapWidget;
    MapControlsWidget *_mapControlsWidget;
    SkillListWidget *_skillListWidget;
    EffectList *_effectList;
    ActionConfigurationWidget *_actionConfWgt;
    ScriptsWidget *_scriptsWgt;

    QToolBar *_mapControls;
    QActionGroup *_mapControlsActionGroup;

    QVBoxLayout _botsLayout;
    QList<BotInstanceWidget*> _bots;
    DllInjector _injector;

    QTimer _testClientsTimer;
    QTimer _refreshDataTimer;

public slots:
    void clientDisconnected(BotInstance* botInstance);

private slots:
    void attach();
    void updateUI();
    void saveConfigurationSlot();
    void loadConfigurationSlot();
    void mapControlSlot(QAction *action);
};

#endif // MAINWINDOW_H
