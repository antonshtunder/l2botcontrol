#include "effectlist.h"
#include "ui_effectlist.h"
#include "bot/botinstance.h"
#include "misc/utils.h"

#define ICON_SIZE 32

EffectList::EffectList(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EffectList)
{
    ui->setupUi(this);
    connect(&_resizeTimer, SIGNAL(timeout()), SLOT(resizeEnded()));
    qDebug() << (LPVOID)ui->gbPlayerEffects->layout();
}

EffectList::~EffectList()
{
    delete ui;
}

void EffectList::update(BotInstance *botInstance)
{
    _botInstance = botInstance;
    auto l2representation = _botInstance->getDataManager().lockRepresentation();
    updateWidgets(_playerEffectWidgets, ui->gbPlayerEffects, _playerEffectWidgetLayout, l2representation->playerEffects);
    updateWidgets(_targetEffectWidgets, ui->gbTargetEffects, _targetEffectWidgetLayout, l2representation->targetEffects);
    _botInstance->getDataManager().unlockRepresentation();
}

void EffectList::updateWidgets(QVector<EffectWidget *> &_effectWidgets, QGroupBox *gb,
                               QGridLayout *_effectWidgetLayout, std::vector<EffectRepresentation> &effectRepresentations)
{
    clearGridLayout(&_effectWidgetLayout);
    delete gb->layout();
    gb->setLayout(_effectWidgetLayout);

    if(_botInstance == NULL)
        return;

    int effectSizeDifference = _effectWidgets.size() - effectRepresentations.size();
    if(effectSizeDifference < 0)
    {
        for(int i = 0; i < qAbs(effectSizeDifference); ++i)
        {
            auto effectWgt = new EffectWidget(_botInstance);
            _effectWidgets.push_back(effectWgt);
        }
    }
    else if(effectSizeDifference > 0)
    {
        for(int i = 0; i < effectSizeDifference; ++i)
        {
            auto effectWgt = _effectWidgets.takeLast();
            delete effectWgt;
        }
    }

    int rowNum = gb->width() / ICON_SIZE;
    for(int i = 0; i < _effectWidgets.size(); ++i)
    {
        _effectWidgets.at(i)->update(effectRepresentations.at(i));
        _effectWidgetLayout->addWidget(_effectWidgets.at(i), i / rowNum, i % rowNum);
    }
}

void EffectList::resizeEvent(QResizeEvent *event)
{
    if(_botInstance == NULL)
        return;

    _resizeTimer.start(200);
    setMinimumWidth(ICON_SIZE * 6);
}

void EffectList::mouseMoveEvent(QMouseEvent *event)
{
}

void EffectList::resizeEnded()
{
    update(_botInstance);
}
