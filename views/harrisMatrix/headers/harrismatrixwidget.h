#ifndef HARRISMATRIXWIDGET_H
#define HARRISMATRIXWIDGET_H

#include <QWidget>
#include <QtWidgets>
#include <QtGui>
#include <QtCore>

class HarrisMatrixWidget : public QGraphicsView
{
    Q_OBJECT
public:
    explicit HarrisMatrixWidget(QWidget *parent = nullptr, QString filePath = nullptr);
    void createScene();
    void addLayerToList(int layerId, QPoint point);

private:
    QString filePath;
    //Create a list that contains pairs associating a layer with an x
    QList<QPair<int, QPoint>> layerPositions;
    QPoint getLayerXPos(int layerId);
protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void contextMenuEvent(QContextMenuEvent *event);


signals:
    void openVL(int layerId);

public slots:
    void zoomIn();
    void zoomOut();
};

#endif // HARRISMATRIXWIDGET_H
