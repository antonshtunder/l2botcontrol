#ifndef GEOMULTISQUARE_H
#define GEOMULTISQUARE_H

#include "geodatasquare.h"
#include "multicell.h"
#include <vector>

class GeoMultiSquare : public GeodataSquare
{
public:
    GeoMultiSquare(MultiCell cells[8][8]);
    GeoMultiSquare &operator=(GeoMultiSquare &gms);
    GeoMultiSquare(const GeoMultiSquare &gms);

    short getHeight(float x, float y, float z) override;

private:
    MultiCell _cells[8][8];
};

#endif // GEOMULTISQUARE_H
