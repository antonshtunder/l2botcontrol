#include "geodataregion.h"

#include <QFile>
#include <QDebug>
#include <vector>
#include "geo/geoflatsquare.h"
#include "geo/geocomplexsquare.h"
#include "geo/geomultisquare.h"

using namespace std;

static QString geodataLocation = "C:/l2data/geodata/";

GeodataRegion::GeodataRegion(const QString &name)
{
    QString fileName = QString("%1%2.l2j").arg(geodataLocation).arg(name);
    QFile geodataFile(fileName);
    if(geodataFile.open(QIODevice::ReadOnly))
    {
        qDebug() << "Successfully opened file with name - " << fileName;
        size_t i = 0;
        while(!geodataFile.atEnd())
        {
            char type;
            short height;
            short complexCells[8][8] = {{0x0}};
            MultiCell multiCells[8][8];
            GeodataSquare *geoSquare;
            geodataFile.read(&type, 1);

            switch(static_cast<GeodataType>(type))
            {
            case GeodataType::FLAT:
                geodataFile.read(reinterpret_cast<char*>(&height), 2);
                geoSquare = new GeoFlatSquare(height);
                break;
            case GeodataType::COMPLEX:
                geodataFile.read(reinterpret_cast<char*>(complexCells), sizeof(complexCells));
                geoSquare = new GeoComplexSquare(complexCells);
                break;
            case GeodataType::MULTI:
                for(int i = 0; i < 8; ++i)
                {
                    for(int j = 0; j < 8; ++j)
                    {
                        multiCells[i][j] = geodataFile;
                    }
                }
                geoSquare = new GeoMultiSquare(multiCells);
                break;
            }
            _squares[i / 256][i % 256] = geoSquare;
            ++i;
        }
    }
    else
    {
        qDebug() << "Failed to open geodata file with name - " << fileName;
    }
}

GeodataRegion::GeodataRegion()
{

}

short GeodataRegion::getHeight(float x, float y, float z)
{
    size_t squareXNum = static_cast<size_t>(x / GEO_SQUARE);
    size_t squareYNum = static_cast<size_t>(y / GEO_SQUARE);
    float squareX = x - squareXNum * GEO_SQUARE;
    float squareY = y - squareYNum * GEO_SQUARE;
    return _squares[squareXNum][squareYNum]->getHeight(squareX, squareY, z);
}
