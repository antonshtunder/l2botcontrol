#ifndef GEODATASQUARE_H
#define GEODATASQUARE_H


class GeodataSquare
{
public:
    GeodataSquare();
    virtual ~GeodataSquare();

    virtual short getHeight(float x, float y, float z) = 0;
};

#endif // GEODATASQUARE_H
