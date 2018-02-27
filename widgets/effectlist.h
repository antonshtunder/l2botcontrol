#ifndef EFFECTLIST_H
#define EFFECTLIST_H

#include "effectwidget.h"

#include <QGridLayout>
#include <QWidget>
#include <QTimer>
#include <vector>
#include <QGroupBox>

class BotInstance;

namespace Ui {
class EffectList;
}

class EffectList : public QWidget
{
    Q_OBJECT

public:
    explicit EffectList(QWidget *parent = 0);
    ~EffectList();

    void clearLayout();
    void update(BotInstance *botInstance);

private:
    void updateWidgets(QVector<EffectWidget*>&, QGroupBox *gb, QGridLayout*, std::vector<EffectRepresentation> &effectRepresentations);

    Ui::EffectList *ui;

    BotInstance *_botInstance = NULL;
    QVector<EffectWidget*> _playerEffectWidgets;
    QVector<EffectWidget*> _targetEffectWidgets;
    QGridLayout *_playerEffectWidgetLayout = NULL;
    QGridLayout *_targetEffectWidgetLayout = NULL;

    QTimer _resizeTimer;
protected:
    void resizeEvent(QResizeEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

private slots:
    void resizeEnded();
};

#endif // EFFECTLIST_H
