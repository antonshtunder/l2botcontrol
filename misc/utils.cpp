#include "utils.h"

using namespace std;

#define X_UNITS_OFFSET 327680.0
#define Y_UNITS_OFFSET 261400.0

QPointF translateCoordinates(QPointF source, double scaleFactor, double ppu)
{
    QPointF result = {(source.x() + X_UNITS_OFFSET) * ppu * scaleFactor,
                      (source.y() + Y_UNITS_OFFSET) * ppu * scaleFactor};
    return result;
}

double getDistance(QPointF a, QPointF b)
{
    return qSqrt(qPow(a.x() - b.x(), 2.0) + qPow(a.y() - b.y(), 2.0));
}


vector<int> strToIntVector(const QString &str)
{
    auto strInts = str.split(" ");
    vector<int> result;
    for(auto strInt : strInts)
    {
        result.push_back(strInt.toInt());
    }
    return result;
}
