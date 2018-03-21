#ifndef ITEMSWIDGET_H
#define ITEMSWIDGET_H

#include <QWidget>

namespace Ui {
class ItemsWidget;
}

class BotInstance;

class ItemsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ItemsWidget(QWidget *parent = 0);
    ~ItemsWidget();

    void update(BotInstance *botInstance);

private:
    Ui::ItemsWidget *ui;

    BotInstance *_lastBotInstance;
};

#endif // ITEMSWIDGET_H
