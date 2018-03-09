#ifndef MAPCONTROLSWIDGET_H
#define MAPCONTROLSWIDGET_H

#include <QWidget>

namespace Ui {
class MapControlsWidget;
}

class MapControlsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MapControlsWidget(QWidget *parent = 0);
    ~MapControlsWidget();

private:
    Ui::MapControlsWidget *ui;
};

#endif // MAPCONTROLSWIDGET_H
