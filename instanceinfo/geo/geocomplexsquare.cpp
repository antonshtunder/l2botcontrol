#include "geocomplexsquare.h"
#include <cstring>
#include <QDebug>

GeoComplexSquare::GeoComplexSquare(short cells[8][8])
{
    memcpy(_cells, cells, sizeof(short) * 8 * 8);
    for(int i = 0; i < 8; ++i)
    {
        for(int j = 0; j < 8; ++j)
        {
            _cells[i][j] = (_cells[i][j] - _cells[i][j] % 16) / 2;
        }
    }
}

short GeoComplexSquare::getHeight(float x, float y, float z)
{
    size_t xCell = static_cast<size_t>(x) / 16;
    size_t yCell = static_cast<size_t>(y) / 16;
    return _cells[xCell][yCell];
}
