#include "skillwidget.h"
#include "ui_skillwidget.h"
#include "bot/botinstance.h"
#include "instanceinfo/instanceinfobank.h"
#include "dialogs/skillusagedialog.h"

SkillWidget::SkillWidget(BotInstance *botInstance, QWidget *parent) :
    QLabel(parent),
    ui(new Ui::SkillWidget),
    _botInstance(botInstance)
{
    ui->setupUi(this);
}

SkillWidget::~SkillWidget()
{
    delete ui;
}

void SkillWidget::update(SkillRepresentation skill, BotInstance *botInstance)
{
    _botInstance = botInstance;
    SkillInfo &skillInfo = InstanceInfoBank::instance()->getSkillInfo(skill.id);
    _skill = skill;
    setPixmap(skillInfo.getIcon());

    setToolTip(QString("Id = %1\nLevel = %2\nName = %3").arg(skill.id).arg(skill.level).arg(skillInfo.getName()));
}

void SkillWidget::mousePressEvent(QMouseEvent *event)
{
    if(!_botInstance->isInGame())
        return;
    if(event->buttons() == Qt::LeftButton)
    {
        _botInstance->useSkill(_skill.id);
        qDebug() << "use skill, mpCost = " << InstanceInfoBank::instance()->getSkillInfo(_skill.id).getMpCost(_skill.level);
    }
    else if(event->buttons() == Qt::RightButton)
    {
        qDebug() << _botInstance->getDataManager().l2representation.character.hp;
        SkillUsageDialog suDialog(_botInstance->getConfiguration().getSkillUsage(_skill), this);
        suDialog.exec();
    }
}
