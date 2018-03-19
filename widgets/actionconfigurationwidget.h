#ifndef ACTIONCONFIGURATIONWIDGET_H
#define ACTIONCONFIGURATIONWIDGET_H

#include <QWidget>
#include "bot/botinstance.h"

namespace Ui {
class ActionConfigurationWidget;
}

class ActionConfigurationWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ActionConfigurationWidget(QWidget *parent = 0);
    ~ActionConfigurationWidget();

    void update(BotInstance *botInstance, bool force = false);

private:
    Ui::ActionConfigurationWidget *ui;

    BotInstance *_botInstance = NULL;

private slots:
    void assist();
    void updateSlot();
    void revertSlot();
    void npcChatSlot();
    void acceptAction();
};

#endif // ACTIONCONFIGURATIONWIDGET_H
