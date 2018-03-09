#include "lineagepainter.h"
#include "bot/botmanager.h"
#include "utils.h"

#define SQUARE_SIZE 9.0
#define SQUARE_OFFSET -(SQUARE_SIZE - 1.0) / 2.0
#define ROUND_SIZE 7.0
#define ROUND_OFFSET -(ROUND_SIZE - 1.0) / 2.0

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

    drawMobs();
    drawCharacter();
    drawItems();
}

void LineagePainter::mousePressed(QMouseEvent *event, QRectF area)
{
    if(event->buttons() == Qt::LeftButton)
    {
        auto instance = BotManager::instance()->getCurrentBotInstance();
        if(instance == 0 || !instance->isInGame())
            return;
        _l2r = instance->l2representation;
        auto mouseLoc = area.topLeft() + event->localPos();
        for(auto mob : _l2r.mobs)
        {
            if(checkIfPressed(mouseLoc, {mob.x, mob.y}, SQUARE_SIZE, SQUARE_OFFSET))
            {
                instance->stopBotting();
                instance->performActionOn(mob.id, mob.address, Representations::MOB);
                qDebug() << "mob pressed1";
            }
        }

        for(auto item : _l2r.droppedItems)
        {
            if(checkIfPressed(mouseLoc, {item.x, item.y}, ROUND_SIZE, ROUND_OFFSET))
            {
                instance->stopBotting();
                instance->performActionOn(item.id, item.address, Representations::DROPPED_ITEM);
                qDebug() << "item pressed";
            }
        }
    }
}

LineagePainter::LineagePainter()
{}

void LineagePainter::drawCharacter()
{
    _painter->setBrush(Qt::white);
    _painter->setPen(Qt::yellow);

    auto pos = translateCoordinates({_l2r.character.x, _l2r.character.y});
    if(checkIfContains(pos))
    {
        drawSquareInstance(pos);
    }
}

void LineagePainter::drawSquareInstance(QPointF pos)
{
        _painter->drawRect(pos.x() - _area.x() + SQUARE_OFFSET,
                           pos.y() - _area.y() + SQUARE_OFFSET,
                           SQUARE_SIZE, SQUARE_SIZE);

}

void LineagePainter::drawRoundInstance(QPointF pos)
{
    _painter->drawEllipse(pos.x() - _area.x() + ROUND_OFFSET,
                       pos.y() - _area.y() + ROUND_OFFSET,
                       ROUND_SIZE, ROUND_SIZE);
}

void LineagePainter::drawMobs()
{
    _painter->setBrush(Qt::NoBrush);
    auto charZ = _l2r.character.z;
    for(auto mobRep : _l2r.mobs)
    {
        switch(mobRep.mobType)
        {
        case MobType::MONSTER:
            _painter->setPen(Qt::red);
            break;
        case MobType::QUEST_MONSTER:
            _painter->setPen(QColor::fromRgb(255, 150, 0));
            break;
        case MobType::NPC:
            _painter->setPen(Qt::blue);
            break;
        case MobType::PLAYER:
            _painter->setPen(Qt::yellow);
            break;
        case MobType::PET:
            _painter->setPen(Qt::green);
            break;
        }
        auto pos = translateCoordinates({mobRep.x, mobRep.y});
        if(checkIfContains(pos))
        {
            drawSquareInstance(pos);
            if(charZ - mobRep.z < -1000.0)
            {
                drawArrowUp(pos, SQUARE_SIZE);
            }
            else if(charZ - mobRep.z > 1000.0)
            {
                drawArrowDown(pos, SQUARE_SIZE);
            }
        }
    }
}

void LineagePainter::drawItems()
{
    auto charZ = _l2r.character.z;
    _painter->setPen(Qt::blue);
    QColor defColor = QColor::fromRgb(108, 209, 41);
    for(auto droppedItemRep : _l2r.droppedItems)
    {
        if(droppedItemRep.typeID == 57)
        {
            _painter->setBrush(Qt::yellow);
        }
        else
        {
            _painter->setBrush(defColor);
        }
        QPointF pos = translateCoordinates({droppedItemRep.x, droppedItemRep.y});
        if(checkIfContains(pos))
        {
            drawRoundInstance(pos);
            _painter->drawText(pos, QString::number(droppedItemRep.id, 16));
            if(charZ - droppedItemRep.z < -1000.0)
            {
                drawArrowUp(pos, ROUND_SIZE);
            }
            else if(charZ - droppedItemRep.z > 1000.0)
            {
                drawArrowDown(pos, ROUND_SIZE);
            }
        }
    }
}

void LineagePainter::drawArrowUp(QPointF loc, double size)
{
    size += 1.0;
    auto offset = -(size - 1.0) / 2.0;
    auto drawX = loc.x() - _area.x() + offset;
    auto drawY = loc.y() - _area.y() + offset;
    _painter->drawLine(drawX, drawY + size, drawX - offset, drawY);
    _painter->drawLine(drawX - offset, drawY, drawX + size, drawY + size);
}

void LineagePainter::drawArrowDown(QPointF loc, double size)
{
    auto offset = -(size - 1.0) / 2.0;
    auto drawX = loc.x() - _area.x() + offset;
    auto drawY = loc.y() - _area.y() + offset;
    _painter->drawLine(drawX, drawY, drawX - offset, drawY + size);
    _painter->drawLine(drawX - offset, drawY + size, drawX + size, drawY);
}

QPointF LineagePainter::translateCoordinates(QPointF source)
{
    return ::translateGameToMap(source, _sf, _ppu);
}

bool LineagePainter::checkIfContains(QPointF pos)
{
    return _area.contains(pos);
}

bool LineagePainter::checkIfPressed(QPointF mouseLoc, QPointF sourcePos, double size, double offset)
{
    auto pos = translateCoordinates(sourcePos);
    QRectF instanceRect = {pos + QPointF(offset, offset), QSizeF(size, size)};
    return instanceRect.contains(mouseLoc);
}
