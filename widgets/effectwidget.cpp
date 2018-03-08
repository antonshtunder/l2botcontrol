#include "effectwidget.h"
#include "ui_effectwidget.h"
#include "bot/botinstance.h"
#include "instanceinfo/instanceinfobank.h"
#include "dialogs/skillusagedialog.h"

EffectWidget::EffectWidget(BotInstance *botInstance, QWidget *parent) :
    QLabel(parent),
    ui(new Ui::EffectWidget),
    _botInstance(botInstance)
{
    ui->setupUi(this);
}

EffectWidget::~EffectWidget()
{
    delete ui;
}

void EffectWidget::update(EffectRepresentation Effect)
{
    SkillInfo &effectInfo = InstanceInfoBank::instance()->getSkillInfo(Effect.id);
    _Effect = Effect;
    setPixmap(effectInfo.getIcon());

    setToolTip(QString("Id = %1\nLevel = %2\nName = %3").arg(Effect.id).arg(Effect.level).arg(effectInfo.getName()));
}
