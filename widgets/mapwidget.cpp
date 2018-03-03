#include "mapwidget.h"
#include "ui_mapwidget.h"
#include "botmanager.h"
#include "misc/lineagepainter.h"
#include "misc/utils.h"
#include "options.h"

#define MAP_WIDTH 558500.0

MapWidget::MapWidget(QWidget *parent) :
    QScrollArea(parent),
    ui(new Ui::MapWidget),
    _imageLabel(new QLabel),
    _image("C:/l2map.gif")
{
    ui->setupUi(this);
    qDebug() << _image << endl;
    _pixelsPerUnit = _image.width() / MAP_WIDTH;
    _imageLabel->setBackgroundRole(QPalette::Base);
    _imageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    _imageLabel->setScaledContents(true);
    setBackgroundRole(QPalette::Dark);
    setWidget(_imageLabel);
}

MapWidget::~MapWidget()
{
    delete ui;
}

void MapWidget::updateInfo()
{
    paintMap();
}

void MapWidget::mousePressEvent(QMouseEvent *event)
{
    if(event->buttons() == Qt::RightButton)
    {
        _previousMousePos = event->screenPos();
    }
    else
    {
        LineagePainter::instance()->mousePressed(event, getDrawingArea());
    }
}

void MapWidget::dragMoveEvent(QDragMoveEvent *)
{
}

void MapWidget::wheelEvent(QWheelEvent *event)
{
    auto deltaScale = event->delta() / 2000.0;
    auto newScale = _scaleFactor * (1.0 + deltaScale);

    if(newScale < 1.0 || newScale > 12.0)
        return;

    auto pos = event->posF();
    auto deltaWidth = (width() / _scaleFactor) - width() / newScale;
    auto deltaHeight = (height() / _scaleFactor) - height() / newScale;

    auto xFactor = pos.x() / width();
    auto yFactor = pos.y() / height();
    moveMap(xFactor * deltaWidth, yFactor * deltaHeight);
    scaleMap(1.0 + deltaScale);
}

void MapWidget::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons() == Qt::RightButton)
    {
        double dx = (_previousMousePos.x() - event->screenPos().x()) / _scaleFactor;
        double dy = (_previousMousePos.y() - event->screenPos().y()) / _scaleFactor;
        moveMap(dx, dy);
        adjustMapDimensions();
        _previousMousePos = event->screenPos();
    }
}

void MapWidget::mouseReleaseEvent(QMouseEvent *event)
{
    //_previousMousePos = _noPreviousMousePos;
}

void MapWidget::resizeEvent(QResizeEvent *event)
{
    adjustMapDimensions();
}

void MapWidget::mouseDoubleClickEvent(QMouseEvent *event)
{
    if(event->buttons() == Qt::RightButton)
    {
        auto botInstance = BotManager::instance()->getCurrentBotInstance();
        if(botInstance == NULL)
            return;

        QPointF charOrigPos(botInstance->l2representation.character.x, botInstance->l2representation.character.y);
        auto charMapPos = translateCoordinates(charOrigPos, _scaleFactor, _pixelsPerUnit);
        _imageX = (charMapPos.x() - width() / 2.0) / _scaleFactor;
        _imageY = (charMapPos.y() - height() / 2.0) / _scaleFactor;
        adjustMapDimensions();
    }
}

void MapWidget::scaleMap(double factor)
{
    _scaleFactor *= factor;
    adjustMapDimensions();

}

void MapWidget::adjustMapDimensions()
{
    double maxX = _image.width() -  width() / _scaleFactor;
    double maxY = _image.height() - height() / _scaleFactor;

    if(_imageX < 0.0)
        _imageX = 0.0;
    else if(_imageX > maxX)
        _imageX = maxX;

    if(_imageY < 0.0)
        _imageY = 0.0;
    else if(_imageY > maxY)
        _imageY = maxY;

    paintMap();
}

void MapWidget::moveMap(double deltaX, double deltaY)
{
    _imageX += deltaX;
    _imageY += deltaY;
}

QRectF MapWidget::getDrawingArea()
{
    QRectF drawingArea = {_imageX * _scaleFactor, _imageY * _scaleFactor,
                          static_cast<qreal>(_imageLabel->width()), static_cast<qreal>(_imageLabel->height())};

    return drawingArea;
}

void MapWidget::paintMap()
{
    _pixelsPerUnit = _image.width() / Options::instance.mapWidth();
    QPixmap map = QPixmap(_imageLabel->width(), _imageLabel->height());
    QPainter painter(&map);

    QPixmap mapImagePiece = _image.copy(_imageX, _imageY,
                                        _imageLabel->width() / _scaleFactor,
                                        _imageLabel->height() / _scaleFactor);
    painter.drawPixmap(map.rect(), mapImagePiece);
    QRectF drawingArea = getDrawingArea();
    LineagePainter::instance()->drawMap(drawingArea, _pixelsPerUnit, _scaleFactor, &painter);

    _imageLabel->setPixmap(map);
}

void MapWidget::drawMapState(QPainter &painter)
{
    /*painter.setBrush(Qt::NoBrush);
    QRectF drawingArea = {_imageX, _imageY, _imageX + width() / _scaleFactor, _imageY + height() / _scaleFactor};
    LineageRepresentation l2rep = BotManager::instance()->getCurrentBotInstance()->l2representation;
    if(drawingArea.contains(l2rep.character.x * _pixelsPerUnit, l2rep.character.y * _pixelsPerUnit))
    {

    }*/
}
