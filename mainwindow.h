#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include "botinstancewidget.h"
#include "dllinjector.h"
#include "optionswindow.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    void connectSlotsAndSignals();

    Ui::MainWindow *ui;

    OptionsWindow *_optionsWindow;

    QVBoxLayout _botsLayout;
    QList<BotInstanceWidget*> _bots;
    DllInjector _injector;

    QTimer _testClientsTimer;
    QTimer _refreshDataTimer;

private slots:
    void attach();
    void updateUI();
    void clientDisconnected(BotInstance* botInstance);
};

#endif // MAINWINDOW_H
