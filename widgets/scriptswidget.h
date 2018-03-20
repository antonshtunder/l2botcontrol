#ifndef SCRIPTSWIDGET_H
#define SCRIPTSWIDGET_H

#include <QWidget>

namespace Ui {
class ScriptsWidget;
}

class ScriptsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ScriptsWidget(QWidget *parent = 0);
    ~ScriptsWidget();

private:
    Ui::ScriptsWidget *ui;

private slots:
    void execute();
};

#endif // SCRIPTSWIDGET_H
