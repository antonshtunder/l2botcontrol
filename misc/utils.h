#ifndef UTILS_H
#define UTILS_H

#include <QGridLayout>
#include <QtCore>
#include <vector>

QPointF translateGameToMap(QPointF source, double scaleFactor, double ppu);
QPointF translateMapToGame(QPointF source, double scaleFactor, double ppu);

double getDistance(QPointF a, QPointF b);

std::vector<int> strToIntVector(const QString &str);

void clearGridLayout(QGridLayout **grid);

#endif // UTILS_H
