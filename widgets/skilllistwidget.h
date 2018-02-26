#ifndef SKILLLISTWIDGET_H
#define SKILLLISTWIDGET_H

#include "skillwidget.h"

#include <QGridLayout>
#include <QWidget>
#include <QTimer>

class BotInstance;

namespace Ui {
class SkillListWidget;
}

class SkillListWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SkillListWidget(BotInstance *botInstance, QWidget *parent = 0);
    ~SkillListWidget();

    void update();
    void clearLayout();

private:
    Ui::SkillListWidget *ui;

    BotInstance *_botInstance;
    QVector<SkillWidget*> _skillWidgets;
    QGridLayout *_skillWidgetLayout = NULL;

    QTimer _resizeTimer;
protected:
    void resizeEvent(QResizeEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

private slots:
    void resizeEnded();
};

#endif // SKILLLISTWIDGET_H
