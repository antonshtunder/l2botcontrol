#include "skilllistwidget.h"
#include "ui_skilllistwidget.h"

SkillListWidget::SkillListWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SkillListWidget)
{
    ui->setupUi(this);
}

SkillListWidget::~SkillListWidget()
{
    delete ui;
}
