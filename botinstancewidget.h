#ifndef BOTINSTANCEWIDGET_H
#define BOTINSTANCEWIDGET_H

#include <QFrame>
#include <QtWidgets>

namespace Ui {
class BotInstanceWidget;
}

class BotInstance;

class BotInstanceWidget : public QFrame
{
    Q_OBJECT

public:
    explicit BotInstanceWidget(BotInstance *botInstance, QWidget *parent = 0);
    ~BotInstanceWidget();

    void update();

protected:
    void mousePressEvent(QMouseEvent *event) override;

private:
    Ui::BotInstanceWidget *ui;
    BotInstance *_botInstance;

signals:
};

#endif // BOTINSTANCEWIDGET_H
