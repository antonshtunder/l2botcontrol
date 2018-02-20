#ifndef LINEAGEPAINTER_H
#define LINEAGEPAINTER_H

#include <QPainter>
#include "botinstance.h"

class LineagePainter
{
public:
    static LineagePainter *instance();

    void drawMap(QRectF drawingArea, double pixelsPerUnit, double scaleFactor, QPainter *painter);

private:
    LineagePainter();

    void drawCharacter();

    QPointF getCoordinates(QPointF source);
    bool checkIfContains(QPointF pos);

    QRectF _area;
    double _ppu;
    double _sf;
    QPainter *_painter;
    LineageRepresentation _l2r;

    static LineagePainter* _instance;
};

#endif // LINEAGEPAINTER_H
