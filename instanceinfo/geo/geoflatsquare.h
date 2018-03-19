#ifndef GEOFLATSQUARE_H
#define GEOFLATSQUARE_H

#include "geodatasquare.h"

class GeoFlatSquare : public GeodataSquare
{
public:
    GeoFlatSquare(short height);

    short getHeight(float x, float y, float z) override;

private:
    short _height;
};

#endif // GEOFLATSQUARE_H
