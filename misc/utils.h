#ifndef UTILS_H
#define UTILS_H

#include <QtCore>
#include <vector>

QPointF translateCoordinates(QPointF source, double scaleFactor, double ppu);

double getDistance(QPointF a, QPointF b);

std::vector<int> strToIntVector(const QString &str);

#endif // UTILS_H
