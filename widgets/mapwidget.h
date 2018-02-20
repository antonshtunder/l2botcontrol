#ifndef MAPWIDGET_H
#define MAPWIDGET_H

#include <QScrollArea>
#include "botinstance.h"

namespace Ui {
class MapWidget;
}

class MapWidget : public QScrollArea
{
    Q_OBJECT

public:
    explicit MapWidget(QWidget *parent = 0);
    ~MapWidget();

    void updateInfo(BotInstance *botInstance);

private:
    Ui::MapWidget *ui;
    QLabel *_imageLabel;
};

#endif // MAPWIDGET_H
