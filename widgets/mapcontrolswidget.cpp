#include "mapcontrolswidget.h"
#include "ui_mapcontrolswidget.h"

MapControlsWidget::MapControlsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MapControlsWidget)
{
    ui->setupUi(this);
    ui->horizontalLayout->setAlignment(Qt::AlignLeft);
    ui->horizontalLayout->setMargin(0);
}

MapControlsWidget::~MapControlsWidget()
{
    delete ui;
}
