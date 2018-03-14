#ifndef LINEAGEPAINTER_H
#define LINEAGEPAINTER_H

#include <QPainter>
#include "bot/botinstance.h"

enum MapAction
{
    ACTION,
    ADD_NODE,
    MOVE_NODE,
    REMOVE_NODE,
    CLEAR_NODES
};

class LineageMapController
{
public:
    static LineageMapController *instance();

    void drawMap(QRectF drawingArea, double pixelsPerUnit, double scaleFactor, QPainter *painter);

    void mousePressed(QMouseEvent *event, QRectF area);

    void setAction(const MapAction action);

    void clearNodes();

private:
    LineageMapController();

    void drawCharacter();
    void drawMobs();
    void drawItems();
    void drawNodes();
    void drawArrowUp(QPointF loc, double size);
    void drawArrowDown(QPointF loc, double size);

    void mouseAction(QMouseEvent *event, QRectF &area);
    void addNode(QMouseEvent *event, QRectF &area);
    void removeNode(QMouseEvent *event, QRectF &area);

    QPointF translateCoordinates(QPointF source);
    bool checkIfContains(QPointF pos);
    bool checkIfPressed(QPointF mouseLoc, QPointF sourcePos, double size, double offset);

    void drawSquareInstance(QPointF mobPos);
    void drawRoundInstance(QPointF itemPos);

    QRectF _area;
    double _ppu;
    double _sf;
    QPainter *_painter;
    LineageRepresentation _l2r;
    MapAction _action;

    static LineageMapController *_instance;
};

#endif // LINEAGEPAINTER_H
