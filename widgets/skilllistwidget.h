#ifndef SKILLLISTWIDGET_H
#define SKILLLISTWIDGET_H

#include <QWidget>

namespace Ui {
class SkillListWidget;
}

class SkillListWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SkillListWidget(QWidget *parent = 0);
    ~SkillListWidget();

private:
    Ui::SkillListWidget *ui;
};

#endif // SKILLLISTWIDGET_H
