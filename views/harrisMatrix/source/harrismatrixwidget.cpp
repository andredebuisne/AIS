#include "views/harrisMatrix/headers/harrismatrixwidget.h"
#include "classes/headers/site.h"
#include "services/headers/siteservice.h"
#include "services/headers/horizonservice.h"
#include "views/harrisMatrix/headers/layermatrixitem.h"
#include "services/headers/relationshipservice.h"
/* Harris matrix *algorithm*
    For each layer, get the layers that are below it :
        - If no layers below, then create a simple line with the layer above
        - If there are layers below :
             - For each layer below, create a branch (this is a struct here)

A layer can be :
    * The top layer (no layer above, with one or more layers below)
    * The bottom layer (no layers below, with layers below)
    * A branch master (more than one layer below)
    * A branch end (more than one layer above)
    * An ordinary layer (one layer above, one layer below)

    TODO : determine this for each layer

TODO : determine if the matrix can be drawn or not!
*/

HarrisMatrixWidget::HarrisMatrixWidget(QWidget *parent, QString filePath) : QGraphicsView(parent)
{
    this->filePath = filePath;
    setFixedWidth(200);
    createScene();
    setMouseTracking(true); //Enable this for cursor change
}

void HarrisMatrixWidget::createScene()
{
    RelationshipService service(filePath);
    QGraphicsScene *scene = new QGraphicsScene(this);
    Site site(filePath);
    SiteService sService(filePath);
    HorizonService hService(filePath);
    site = sService.loadSite();

    int x = 0;
    int y = 0;

    for(int i = 0; i < site.getRelationships().size(); i++){
            Relationship relationship = site.getRelationships().at(i);
            int layerId = relationship.getLayerId();
            QList<Relationship> lowerLayers = service.findLowerLayers(layerId);
            QList<Relationship> upperLayers = service.findUpperLayers(layerId);


        if(upperLayers.size() == 0){ //The layer is on the very top
            //Add the layer to the matrix, it will be added in the center
            if(getLayerXPos(layerId).x() != -1){ //Make sure the layer is not already on the scence
                QString text = QString("%1").arg(QString::number(layerId));
                LayerMatrixItem *layerRect = new LayerMatrixItem(x, y, Qt::white);
                layerRect->setData(0, layerId);
                layerRect->setText(text);
                scene->addItem(layerRect);
                addLayerToList(layerId, QPoint(x, y));
            }

            y += 35; //We added a new layer, the next ones need to be under

            //Is there more than one layer below?
            if(lowerLayers.size() > 1){//Yes
                //Create the branches
                //If there is a pair number of branches, split them in half
                if(lowerLayers.size() %2 ==0){
                    x -= 35; //Start laying out on the left
                    for(int i = 0; i < lowerLayers.size(); i++){
                        QString text = QString("%1").arg(QString::number(lowerLayers.at(i).getLayerId()));
                        LayerMatrixItem *layerRect = new LayerMatrixItem(x, y, Qt::white);
                        layerRect->setData(0, lowerLayers.at(i).getLayerId());
                        layerRect->setText(text);
                        scene->addItem(layerRect);
                        addLayerToList(lowerLayers.at(i).getLayerId(), QPoint(x, y));

                        //DRAW THE CONNECTION
                        scene->addLine(x + 15, y, x + 15 , y-20); //Verical line

                        if( x > 0){
                            scene->addLine(x+15, y-20, x-5, y-20); //Horizontal line  to the right
                            //NOT RELATIVE HERE!
                        }else if( x < 0){
                            scene->addLine(x+15, y-20, x+35, y-20); //Horizontal line  to the left
                            //NOT RELATIVE HERE EITHER!
                        }

                        //Set the x accordingly for the next layer
                        if(i%2 == 1 && x >= 0){
                            x += 35;
                        }else if(i%2 == 1 && x < 0){
                            x -= 35;
                        }

                        x *= -1; //So we add to each side each time!
                    }
                    x = 0;
                    y+=35;
                }
                //Odd number of branches, the center one is below the upper branch, the others are split alongside
                else if(lowerLayers.size() %2 ==1){


                }
            }else{ //No, there is only one layer below

            }


        }else if(lowerLayers.size() == 0 ){ //The layer is on the very bottom
            //Put the layer using the upper layers y and x
            int xTotal;
            int numUpperLayers = upperLayers.size();
            for(int i = 0; i < numUpperLayers ; i++){
                xTotal += getLayerXPos(upperLayers.at(i).getLayerId()).x();
                if(getLayerXPos(upperLayers.at(i).getLayerId()).y() > y){ //Put the last layer below the lowest upper layer
                    y = getLayerXPos(upperLayers.at(i).getLayerId()).y();
                }
            }
            x = xTotal / numUpperLayers; //This might not be round, but as an integer it is ok

            QString text = QString("%1").arg(QString::number(layerId));
            LayerMatrixItem *layerRect = new LayerMatrixItem(x, y, Qt::white);
            layerRect->setData(0, layerId);
            layerRect->setText(text);
            scene->addItem(layerRect);
            addLayerToList(layerId, QPoint(x, y));

            //DRAW THE CONNECTION(s)
            for(int i = 0; i < numUpperLayers; i++){
                //Connect each upper layer to this bottom layer
                QPoint pos = getLayerXPos(upperLayers.at(i).getLayerId());

                //Draw a horizontal line
                if(pos.x() < 0 ){
                    scene->addLine(x, y+15, pos.x() + 15, pos.y() + 50);
                }else if(pos.x() > 0){
                    scene->addLine(x+ 30, y+15, pos.x() + 15, pos.y() + 50);
                }
                //Draw a vertical line
                scene->addLine(pos.x() + 15, pos.y() + 50, pos.x() + 15, pos.y() + 30);
                //scene->addLine(x1, y1, x2, y2);
            }
        }else if(lowerLayers.size() >=1 && upperLayers.size() >=1){ //The layer is nor on top or on the bottom
            //Get the upper layer x
            QPoint pos = getLayerXPos(layerId);
            x = pos.x();
            y = pos.y() + 35;
            if(x != -1){ //The layer has already been added to the scence
                //Make sure that the layer underneath is not the bottom layer
                if(service.findLowerLayers(relationship.getLaterThan()).size() > 0){
                    QString text = QString("%1").arg(QString::number(relationship.getLaterThan()));
                    LayerMatrixItem *layerRect = new LayerMatrixItem(x, y, Qt::white);
                    layerRect->setData(0, relationship.getLaterThan());
                    layerRect->setText(text);
                    scene->addItem(layerRect);

                    //DRAW THE CONNECTION
                    scene->addLine(x + 15, y, x+15, y-5);

                    addLayerToList(relationship.getLaterThan(), QPoint(x, y));
                }
            }
        }
    }

    setScene(scene);
}

void HarrisMatrixWidget::addLayerToList(int layerId, QPoint point)
{
    QPair<int, QPoint> layerPair;
    layerPair.first = layerId;
    layerPair.second = point;

    layerPositions.append(layerPair);
}

QPoint HarrisMatrixWidget::getLayerXPos(int layerId)
{
//Include binary search here!
    for(int i = 0; i < layerPositions.size(); i++){
        if(layerPositions.at(i).first == layerId){
            return layerPositions.at(i).second;
        }
    }
    return QPoint(-1, -1); //If layer hasn't been added yet
}

void HarrisMatrixWidget::mousePressEvent(QMouseEvent *event)
{
    QGraphicsItem *item = itemAt(event->pos());
    if(item){
        if(item->childItems().size() > 0){ //User clicked directly on the square
            if(!item->data(0).isNull()){
                emit openVL(item->data(0).toInt());
            }
        }else if(!item->parentItem()->data(0).isNull()){ //User clicked on the text, get the parent item's data
            emit openVL(item->parentItem()->data(0).toInt());
        }
    }



}

void HarrisMatrixWidget::mouseMoveEvent(QMouseEvent *event)
{
    QGraphicsItem *item = itemAt(event->pos());
    if(item) {
        setCursor(Qt::PointingHandCursor);
    }else{
        setCursor(Qt::ArrowCursor);
    }
}
;
void HarrisMatrixWidget::contextMenuEvent(QContextMenuEvent *event)
{

    QGraphicsItem *item = itemAt(event->pos());
    QPoint globalPos = mapToGlobal(event->pos());
    QMenu menu;
    if(item){
        menu.addAction("Ouvrir");
        menu.addAction("Supprimer");
    }else {
        QAction *zoomIn = new QAction;
        zoomIn->setText(tr("Zoom +"));
        zoomIn->setShortcut(QKeySequence::ZoomIn);
        connect(zoomIn, SIGNAL(triggered()), this, SLOT(zoomIn()));

        QAction *zoomOut = new QAction;
        zoomOut->setText(tr("Zoom -"));
        zoomOut->setShortcut(QKeySequence::ZoomOut);
        connect(zoomOut, SIGNAL(triggered()), this, SLOT(zoomOut()));
        menu.addAction(zoomIn);
        menu.addAction(zoomOut);
        menu.addAction("Plein écran");
    }
    menu.exec(globalPos);
}

void HarrisMatrixWidget::zoomIn()
{
    this->scale(1.2, 1.2);
}

void HarrisMatrixWidget::zoomOut()
{
    this->scale(0.8, 0.8);
}





