#include "geomultisquare.h"
#include <QtMath>
#include <cstring>
#include <QDebug>

GeoMultiSquare::GeoMultiSquare(MultiCell cells[8][8])
{
    for(int i = 0; i < 8; ++i)
    {
        for(int j = 0; j < 8; ++j)
        {
            _cells[i][j] = cells[i][j];
        }
    }
}

GeoMultiSquare &GeoMultiSquare::operator=(GeoMultiSquare &gms)
{
    memcpy(_cells, gms._cells, sizeof(MultiCell) * 8 * 8);
    return *this;
}

GeoMultiSquare::GeoMultiSquare(const GeoMultiSquare &gms)
{
}

short GeoMultiSquare::getHeight(float x, float y, float z)
{
    size_t xCell = static_cast<size_t>(x) / 16;
    size_t yCell = static_cast<size_t>(y) / 16;

    short bestHeight = 5000;
    float closestGap = 99999.9f;
    auto cellLayers = _cells[xCell][yCell].cells();
    for(auto layer : cellLayers)
    {
        if(qAbs(layer - z) <= closestGap)
        {
            bestHeight = layer;
            closestGap = qAbs(layer - z);
        }
    }
    return bestHeight;
}
