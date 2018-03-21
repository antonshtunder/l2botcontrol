#include "skilllistwidget.h"
#include "ui_skilllistwidget.h"
#include "bot/botinstance.h"
#include "misc/utils.h"

#define ICON_SIZE 32

SkillListWidget::SkillListWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SkillListWidget)
{
    ui->setupUi(this);
    _resizeTimer.setSingleShot(true);
    connect(&_resizeTimer, SIGNAL(timeout()), SLOT(resizeEnded()));
}

SkillListWidget::~SkillListWidget()
{
    delete ui;
}

void SkillListWidget::update(BotInstance *botInstance)
{
    _botInstance = botInstance;

    clearLayout();

    if(_botInstance == NULL)
        return;

    auto l2representation = _botInstance->getDataManager().lockRepresentation();

    int activeSkillSizeDifference = _skillWidgets.size() - l2representation->activeSkills.size();
    if(activeSkillSizeDifference < 0)
    {
        for(int i = 0; i < qAbs(activeSkillSizeDifference); ++i)
        {
            auto skillWgt = new SkillWidget(_botInstance);
            _skillWidgets.push_back(skillWgt);
        }
    }
    else if(activeSkillSizeDifference > 0)
    {
        for(int i = 0; i < activeSkillSizeDifference; ++i)
        {
            auto skillWgt = _skillWidgets.takeLast();
            delete skillWgt;
        }
    }

    int rowNum = width() / ICON_SIZE;
    for(int i = 0; i < _skillWidgets.size(); ++i)
    {
        _skillWidgets.at(i)->update(l2representation->activeSkills.at(i), _botInstance);
        _skillWidgetLayout->addWidget(_skillWidgets.at(i), i / rowNum, i % rowNum);
    }
    _botInstance->getDataManager().unlockRepresentation();
}

void SkillListWidget::clearLayout()
{
    clearGridLayout(&_skillWidgetLayout);
    setLayout(_skillWidgetLayout);
}

void SkillListWidget::resizeEvent(QResizeEvent *event)
{
    if(_botInstance == NULL)
        return;

    _resizeTimer.start(200);
    setMinimumWidth(ICON_SIZE * 6);
}

void SkillListWidget::mouseMoveEvent(QMouseEvent *event)
{
}

void SkillListWidget::resizeEnded()
{
    qDebug() << "resize ended";
    update(_botInstance);
}
