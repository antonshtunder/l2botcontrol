#ifndef SKILLWIDGET_H
#define SKILLWIDGET_H

#include <QFrame>
#include <QWidget>
#include "skillrepresentation.h"

namespace Ui {
class SkillWidget;
}

class BotInstance;

class SkillWidget : public QFrame
{
    Q_OBJECT

public:
    explicit SkillWidget(BotInstance* botInstance, QWidget *parent = 0);
    ~SkillWidget();

    void update(SkillRepresentation skill);

private:
    Ui::SkillWidget *ui;
    BotInstance *_botInstance;
    SkillRepresentation _skill;

    // QWidget interface
protected:
    void mousePressEvent(QMouseEvent *event) override;
};

#endif // SKILLWIDGET_H
