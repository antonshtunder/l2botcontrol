#ifndef EFFECTWIDGET_H
#define EFFECTWIDGET_H

#include <QFrame>
#include <QLabel>
#include <QWidget>
#include "effectrepresentation.h"

namespace Ui {
class EffectWidget;
}

class BotInstance;

class EffectWidget : public QLabel
{
    Q_OBJECT

public:
    explicit EffectWidget(BotInstance* botInstance, QWidget *parent = 0);
    ~EffectWidget();

    void update(EffectRepresentation Effect);

private:
    Ui::EffectWidget *ui;
    BotInstance *_botInstance;
    EffectRepresentation _Effect;
};

#endif // EFFECTWIDGET_H
