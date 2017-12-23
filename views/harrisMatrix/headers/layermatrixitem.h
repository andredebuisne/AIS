#ifndef LAYERMATRIXITEM_H
#define LAYERMATRIXITEM_H
#include <QtWidgets>

class LayerMatrixItem : public QGraphicsItem
{
public:
    LayerMatrixItem(int x = 0 , int y = 0,  QColor color = Qt::white);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void setText(QString text);
    QString getText();

private:
    QColor backgroundColor;
    QString text;

};

#endif // LAYERMATRIXITEM_H
