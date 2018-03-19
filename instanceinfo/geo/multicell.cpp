#include "multicell.h"
#include <QDebug>

MultiCell::MultiCell(QFile &file)
{
    file.read(&layerNum, 1);
    short height;
    for(int i = 0; i < layerNum; ++i)
    {
        file.read(reinterpret_cast<char*>(&height), 2);
        height = (height - height % 16) / 2;
        _cells.push_back(height);
    }
}

MultiCell::MultiCell()
{
    layerNum = 0;
}

MultiCell &MultiCell::operator=(QFile &file)
{
    file.read(&layerNum, 1);
    short height;
    for(int i = 0; i < layerNum; ++i)
    {
        file.read(reinterpret_cast<char*>(&height), 2);
        height = (height - height % 16) / 2;
        _cells.push_back(height);
    }
    return *this;
}

std::vector<short> &MultiCell::cells()
{
    return _cells;
}
