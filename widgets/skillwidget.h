#ifndef SKILLWIDGET_H
#define SKILLWIDGET_H

#include <QWidget>
#include "skillrepresentation.h"

namespace Ui {
class SkillWidget;
}

class SkillWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SkillWidget(SkillRepresentation skill, QWidget *parent = 0);
    ~SkillWidget();

    void update(SkillRepresentation skill);

private:
    Ui::SkillWidget *ui;

    SkillRepresentation _skill;
};

#endif // SKILLWIDGET_H
