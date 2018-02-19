#ifndef OPTIONSWINDOW_H
#define OPTIONSWINDOW_H

#include <QWidget>
#include "options.h"

namespace Ui {
class OptionsWindow;
}

class OptionsWindow : public QWidget
{
    Q_OBJECT

public:
    explicit OptionsWindow(QWidget *parent = 0);
    ~OptionsWindow();

    void showEvent(QShowEvent *event) override;

private:
    void connectSignalsAndSlots();

    Ui::OptionsWindow *ui;

private slots:
    void saveState();
};

#endif // OPTIONSWINDOW_H
