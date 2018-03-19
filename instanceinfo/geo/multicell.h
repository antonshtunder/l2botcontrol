#ifndef MULTICELL_H
#define MULTICELL_H

#include <vector>
#include <QFile>

class MultiCell
{
public:
    MultiCell(QFile &file);
    MultiCell();
    MultiCell &operator=(QFile &file);

    std::vector<short> &cells();

private:
    char layerNum;
    std::vector<short> _cells;
};

#endif // MULTICELL_H
