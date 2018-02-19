#ifndef BOTINSTANCEWIDGET_H
#define BOTINSTANCEWIDGET_H

#include <QFrame>

namespace Ui {
class BotInstanceWidget;
}

class BotInstanceWidget : public QFrame
{
    Q_OBJECT

public:
    explicit BotInstanceWidget(QWidget *parent = 0);
    ~BotInstanceWidget();

private:
    Ui::BotInstanceWidget *ui;
};

#endif // BOTINSTANCEWIDGET_H
