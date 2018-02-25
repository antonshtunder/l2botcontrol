#include "skillwidget.h"
#include "ui_skillwidget.h"

SkillWidget::SkillWidget(SkillRepresentation skill, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SkillWidget)
{
    ui->setupUi(this);
    update(skill);
}

SkillWidget::~SkillWidget()
{
    delete ui;
}

void SkillWidget::update(SkillRepresentation skill)
{
    _skill = skill;
    ui->lblId->setText(QString::number(skill.id));
    ui->lblLevel->setText(QString::number(skill.level));
}
