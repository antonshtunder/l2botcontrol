#ifndef GEOCOMPLEXSQUARE_H
#define GEOCOMPLEXSQUARE_H

#include "geodatasquare.h"

class GeoComplexSquare : public GeodataSquare
{
public:
    GeoComplexSquare(short cells[8][8]);

    short getHeight(float x, float y, float z) override;

private:
    short _cells[8][8];
};

#endif // GEOCOMPLEXSQUARE_H
