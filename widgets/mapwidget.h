#ifndef MAPWIDGET_H
#define MAPWIDGET_H

#include <QScrollArea>
#include "bot/botinstance.h"

namespace Ui {
class MapWidget;
}

class MapWidget : public QScrollArea
{
    Q_OBJECT

public:
    explicit MapWidget(QWidget *parent = 0);
    ~MapWidget();

    void updateInfo();


protected:
    void mousePressEvent(QMouseEvent*) override;
    void dragMoveEvent(QDragMoveEvent*) override;
    void wheelEvent(QWheelEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    void mouseDoubleClickEvent(QMouseEvent *event) override;

private:
    void scaleMap(double factor);
    void adjustMapDimensions();
    void moveMap(double deltaX, double deltaY);
    void paintMap();
    QRectF getDrawingArea();

    Ui::MapWidget *ui;
    QLabel *_imageLabel;

    double _scaleFactor = 1.0;
    double _imageX = 2000.0, _imageY = 2000.0;
    double _pixelsPerUnit;
    QPixmap _image;
    QPointF _previousMousePos;
    const QPointF _noPreviousMousePos = {-1.0e10, -1.0e10};
};

#endif // MAPWIDGET_H
