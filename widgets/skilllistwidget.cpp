#include "skilllistwidget.h"
#include "ui_skilllistwidget.h"
#include "botinstance.h"

#define ICON_SIZE 32

SkillListWidget::SkillListWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SkillListWidget)
{
    ui->setupUi(this);
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

    int activeSkillSizeDifference = _skillWidgets.size() - _botInstance->l2representation.activeSkills.size();
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
        _skillWidgets.at(i)->update(_botInstance->l2representation.activeSkills.at(i));
        _skillWidgetLayout->addWidget(_skillWidgets.at(i), i / rowNum, i % rowNum);
    }
}

void SkillListWidget::clearLayout()
{
    if(_skillWidgetLayout != NULL)
    {
        auto layoutChildren = _skillWidgetLayout->children();
        for(auto child : layoutChildren)
        {
            _skillWidgetLayout->removeWidget(qobject_cast<QWidget*>(child));
        }
        delete _skillWidgetLayout;
    }
    _skillWidgetLayout = new QGridLayout;
    _skillWidgetLayout->setAlignment(Qt::AlignTop);
    _skillWidgetLayout->setSpacing(0);
    _skillWidgetLayout->setMargin(0);
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
    update(_botInstance);
}
