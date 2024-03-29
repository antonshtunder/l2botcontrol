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

public slots:
    void update(BotInstance *botInstance, bool force = true);

private slots:
    void addUsage();

private:
    Ui::ItemsWidget *ui;

    BotInstance *_lastBotInstance;
};

#endif // ITEMSWIDGET_H
