#ifndef ITEMUSAGEWIDGET_H
#define ITEMUSAGEWIDGET_H

#include <QWidget>
#include <botcommands/itemusage.h>

namespace Ui {
class ItemUsageWidget;
}

class ItemUsageWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ItemUsageWidget(ItemUsage *usage, QWidget *parent = 0);
    ~ItemUsageWidget();

private:
    Ui::ItemUsageWidget *ui;
    ItemUsage *_itemUsage;

private slots:
    void edit();
    void remove();

signals:
    void update(BotInstance *botInstance);
};

#endif // ITEMUSAGEWIDGET_H
