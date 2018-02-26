#include "skillwidget.h"
#include "ui_skillwidget.h"
#include "botinstance.h"
#include "instanceinfo/instanceinfobank.h"

SkillWidget::SkillWidget(BotInstance *botInstance, QWidget *parent) :
    QFrame(parent),
    ui(new Ui::SkillWidget),
    _botInstance(botInstance)
{
    ui->setupUi(this);
}

SkillWidget::~SkillWidget()
{
    delete ui;
}

void SkillWidget::update(SkillRepresentation skill)
{
    SkillInfo &skillInfo = InstanceInfoBank::instance()->getSkillInfo(skill.id);
    _skill = skill;
    ui->lblIcon->setPixmap(skillInfo.getIcon());

    setToolTip(QString("Id = %1\nLevel = %2\nName = %3").arg(skill.id).arg(skill.level).arg(skillInfo.getName()));
}

void SkillWidget::mousePressEvent(QMouseEvent *event)
{
    _botInstance->useSkill(_skill.id);
    qDebug() << "use skill, id = " << _skill.id;
}
