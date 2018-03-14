#include "utils.h"
#include <QWidget>

using namespace std;

#define X_UNITS_OFFSET 327680.0
#define Y_UNITS_OFFSET 261400.0

QPointF translateGameToMap(QPointF source, double scaleFactor, double ppu)
{
    QPointF result = {(source.x() + X_UNITS_OFFSET) * ppu * scaleFactor,
                      (source.y() + Y_UNITS_OFFSET) * ppu * scaleFactor};
    return result;
}

QPointF translateMapToGame(QPointF source, double scaleFactor, double ppu)
{
    QPointF result = {source.x() / ppu / scaleFactor - X_UNITS_OFFSET,
                      source.y() / ppu / scaleFactor - Y_UNITS_OFFSET};
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

void clearGridLayout(QGridLayout **grid)
{
    if(*grid != NULL)
    {
        auto layoutChildren = (*grid)->children();
        for(auto child : layoutChildren)
        {
            (*grid)->removeWidget(qobject_cast<QWidget*>(child));
        }
        delete *grid;
    }
    *grid = new QGridLayout;
    (*grid)->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    (*grid)->setSpacing(0);
    (*grid)->setMargin(0);
}
