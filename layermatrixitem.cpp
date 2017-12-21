#include "layermatrixitem.h"

LayerMatrixItem::LayerMatrixItem(int x, int y, QColor color)
{
    setX(x);
    setY(y);
    backgroundColor = color;
}

QRectF LayerMatrixItem::boundingRect() const
{
    return QRectF(0 , 0, 30, 30);
}

void LayerMatrixItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF rec = boundingRect();
    QBrush brush(backgroundColor);

    painter->fillRect(rec, brush);
    painter->drawRect(rec);

}


void LayerMatrixItem::setText(QString text)
{
    this->text = text;
    QGraphicsTextItem *textItem = new QGraphicsTextItem(this);
    textItem->setPlainText(text);
    int xPos = textItem->boundingRect().center().x();
    int yPos = textItem->boundingRect().center().y();

    //textItem->setPos(xPos, yPos);

    textItem->setTextWidth(textItem->boundingRect().width()); //Avoid text overflow
}

QString LayerMatrixItem::getText()
{
    return this->text;
}

