#ifndef LINEAGEPAINTER_H
#define LINEAGEPAINTER_H

#include <QPainter>
#include "botinstance.h"

class LineagePainter
{
public:
    static LineagePainter *instance();

    void drawMap(QRectF drawingArea, double pixelsPerUnit, double scaleFactor, QPainter *painter);

    void mousePressed(QMouseEvent *event, QRectF area);

private:
    LineagePainter();

    void drawCharacter();
    void drawMobs();
    void drawItems();

    QPointF translateCoordinates(QPointF source);
    bool checkIfContains(QPointF pos);
    bool checkIfPressed(QPointF mouseLoc, QPointF sourcePos, double size, double offset);

    QRectF _area;
    double _ppu;
    double _sf;
    QPainter *_painter;
    LineageRepresentation _l2r;

    static LineagePainter* _instance;
    void drawSquareInstance(QPointF mobPos);
    void drawRoundInstance(QPointF itemPos);
};

#endif // LINEAGEPAINTER_H
