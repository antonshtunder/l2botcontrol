#include "mapwidget.h"
#include "ui_mapwidget.h"

MapWidget::MapWidget(QWidget *parent) :
    QScrollArea(parent),
    ui(new Ui::MapWidget),
    _imageLabel(new QLabel)
{
    ui->setupUi(this);
    _imageLabel->setBackgroundRole(QPalette::Base);
    _imageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    _imageLabel->setScaledContents(true);
    setBackgroundRole(QPalette::Dark);
    setWidget(_imageLabel);
    setVisible(false);
}

MapWidget::~MapWidget()
{
    delete ui;
}

void MapWidget::updateInfo(BotInstance *botInstance)
{

}
