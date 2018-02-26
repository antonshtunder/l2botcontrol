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

    QMenu _contextMenu;
    QAction _startAction;
    QAction _stopAction;
    QAction _detachAction;
private slots:
    void startBotting();
    void stopBotting();
    void detach();
    void showContextMenu(const QPoint &);

signals:
    void detachSignal(BotInstance*);
};

#endif // BOTINSTANCEWIDGET_H
