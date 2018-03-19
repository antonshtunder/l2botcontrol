#include "geoflatsquare.h"

GeoFlatSquare::GeoFlatSquare(short height):
    _height(height)
{

}

short GeoFlatSquare::getHeight(float, float, float)
{
    return _height;
}
