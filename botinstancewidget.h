#ifndef BOTINSTANCEWIDGET_H
#define BOTINSTANCEWIDGET_H

#include <QFrame>
#include <QtWidgets>

namespace Ui {
class BotInstanceWidget;
}

class BotInstance;
class MainWindow;

class BotInstanceWidget : public QFrame
{
    Q_OBJECT

public:
    explicit BotInstanceWidget(BotInstance *botInstance, QWidget *parent = 0);
    ~BotInstanceWidget();

    void updateInfo();

protected:
    void mousePressEvent(QMouseEvent *event) override;

private:
    Ui::BotInstanceWidget *ui;
    BotInstance *_botInstance;

private slots:
    void startBotting();
    void stopBotting();
    void detach();

signals:
    void detachSignal(BotInstance*);
};

#endif // BOTINSTANCEWIDGET_H
