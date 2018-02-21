#ifndef UTILS_H
#define UTILS_H

#include <QtCore>

QPointF translateCoordinates(QPointF source, double scaleFactor, double ppu);

double getDistance(QPointF a, QPointF b);

#endif // UTILS_H
