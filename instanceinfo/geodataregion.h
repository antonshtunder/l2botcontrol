#ifndef GEODATAINFO_H
#define GEODATAINFO_H

#include <QString>
#include "geo/geodatasquare.h"


#define GEO_LEFT_BORDER -327680.0f
#define GEO_TOP_BORDER -262144.0f
#define GEO_REGION 32768.0f
#define GEO_SQUARE 128.0f
#define GEO_CELL 16.0f

enum GeodataType
{
    FLAT = 0,
    COMPLEX = 1,
    MULTI = 2
};

class GeodataRegion
{
public:
    GeodataRegion(const QString &name);
    GeodataRegion();

    short getHeight(float x, float y, float z);

private:
    GeodataSquare *_squares[256][256];
};

#endif // GEODATAINFO_H
