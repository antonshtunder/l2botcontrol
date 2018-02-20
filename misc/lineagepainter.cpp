#include "lineagepainter.h"
#include "botmanager.h"

#define X_UNITS_OFFSET 327680.0
#define Y_UNITS_OFFSET 261400.0

LineagePainter *LineagePainter::_instance = nullptr;

LineagePainter *LineagePainter::instance()
{
    if(_instance == nullptr)
    {
        _instance = new LineagePainter;
    }
    return _instance;
}

void LineagePainter::drawMap(QRectF drawingArea, double pixelsPerUnit, double scaleFactor, QPainter *painter)
{
    auto instance = BotManager::instance()->getCurrentBotInstance();
    if(instance == 0 || !instance->isInGame())
        return;

    painter->setBrush(Qt::NoBrush);
    _area = drawingArea;
    _ppu = pixelsPerUnit;
    _sf = scaleFactor;
    _painter = painter;
    _l2r = instance->l2representation;

    drawCharacter();
}

LineagePainter::LineagePainter()
{}

void LineagePainter::drawCharacter()
{
    _painter->setPen(Qt::white);
    QPointF charPos = translateCoordinates({_l2r.character.x, _l2r.character.y});
    qDebug() << _ppu << endl;
    qDebug() << charPos << endl;
    qDebug() << _area << endl;
    if(checkIfContains(charPos))
    {
        _painter->drawRect(charPos.x() - _area.x() - 1.0, charPos.y() - _area.y() - 1.0, 3.0, 3.0);
    }
}

QPointF LineagePainter::translateCoordinates(QPointF source)
{
    QPointF result = {(source.x() + X_UNITS_OFFSET) * _ppu, (source.y() + Y_UNITS_OFFSET) * _ppu};
    return result;
}

bool LineagePainter::checkIfContains(QPointF pos)
{
    return _area.contains(pos);
}
