#include "views/tree/headers/sitetree.h"
#include "services/headers/siteservice.h"
#include "services/headers/horizonservice.h"

SiteTree::SiteTree(QWidget *parent, QString filePath) : QTreeWidget(parent)
{
    this->filePath = filePath;
    //List all horizons, layers and object in the site root file
    SiteService sService(this->filePath);
    Site site(this->filePath); //User a pointer here?
    site = sService.loadSite();

    setAttribute(Qt::WA_MacShowFocusRect, false); //Remove blue outline on mac
    setHeaderLabel(tr("Stratigraphie"));
    setMaximumWidth(200);
    setMinimumWidth(100);
    setColumnCount(1);
    //setHeaderHidden(true);
    setExpandsOnDoubleClick(false);
    //Drag and drop functionnality
    setDragEnabled(true);
    viewport()->setAcceptDrops(true);
    setDropIndicatorShown(true);
    setDragDropMode(QAbstractItemView::InternalMove);
    //Configure the right click menu
    setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, SIGNAL(customContextMenuRequested(const QPoint&)),
        this, SLOT(showContextMenu(const QPoint&)));
    connect(this, SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)), this, SLOT(openItem(QTreeWidgetItem*,int)));

    //setSelectionMode(QAbstractItemView::MultiSelection); SELECT MUTLIPLE --> implement

    //ADD HORIZONS
    for(int i =0; i<site.getHorizons().size();i++){
        Horizon horizon = site.getHorizons().at(i);
        if(horizon.getId() != -1) {
            //1st level = horizons
            QTreeWidgetItem *horizonItem = new QTreeWidgetItem;
            QString s = QString(tr("Horizon %1")).arg(QString::number(horizon.getId()));
            //Set data here?
            horizonItem->setIcon(0, QIcon(":/icons/horizon"));
            horizonItem->setText(0, s);
            this->addTopLevelItem(horizonItem);
            horizonItem->setExpanded(true);
            //ADD LAYERS
            for(int j =0; j <horizon.getLayerIds().size(); j++){
                HorizonService hService(filePath, horizon.getId());
                int layerId = horizon.getLayerIds().at(j);
                Layer layer = hService.loadLayer(layerId);
                QTreeWidgetItem *layerItem = new QTreeWidgetItem;
                QString l = QString(tr("Couche %1")).arg(QString::number(layer.getId()));
                layerItem->setIcon(0, QIcon(":/icons/layer3"));
                layerItem->setText(0, l);
                horizonItem->addChild(layerItem);

                for(int k = 0; k < layer.getObjects().size(); k++){
                    Object object = layer.getObjects().at(k);
                    QTreeWidgetItem *objectItem  = new QTreeWidgetItem;
                    QString o = QString(tr("%1 - %2")).arg(QString::number(object.getId())).arg(object.getName());
                    objectItem->setIcon(0, QIcon(":/icons/object"));
                    objectItem->setText(0, o);
                    objectItem->setData(1, 0, object.getId());
                    layerItem->addChild(objectItem);
                }
            }
        }else if(horizon.getId() == -1){ //This is the BASE HORIZON!
            for(int j =0; j <horizon.getLayerIds().size(); j++){
                HorizonService hService(filePath, horizon.getId());
                int layerId = horizon.getLayerIds().at(j);
                Layer layer = hService.loadLayer(layerId);
                QTreeWidgetItem *layerItem = new QTreeWidgetItem;
                QString l = QString(tr("Couche %1")).arg(QString::number(layer.getId()));
                layerItem->setIcon(0, QIcon(":/icons/layer3"));
                layerItem->setText(0, l);
                addTopLevelItem(layerItem);
                for(int k = 0; k < layer.getObjects().size(); k++){
                    Object object = layer.getObjects().at(k);
                    QTreeWidgetItem *objectItem  = new QTreeWidgetItem;
                    QString o = QString(tr("%1 - %2")).arg(QString::number(object.getId())).arg(object.getName());
                    objectItem->setIcon(0, QIcon(":/icons/object"));
                    objectItem->setText(0, o);
                    objectItem->setData(1, 0, object.getId());
                    layerItem->addChild(objectItem);
                }
            }
        }
    }
}

void SiteTree::dropEvent(QDropEvent *event)
{
    QTreeWidgetItem* d = itemAt(event->pos());
    QTreeWidgetItem* s = itemAt(currentDragItemPosition);
    QString source = s->text(0);
    if(d){
        QString destination = d->text(0);

        if( checkTransfer(source, destination) ){
                transfer(source, destination);
                QTreeWidget::dropEvent(event);
                d->setExpanded(true);

        }else if(destination.contains(tr("Couche")) && d->parent() != NULL){ //If user drops on a layer, add it to its parent horizon
            destination = d->parent()->text(0);
            transfer(source, destination);
                  //QTreeWidget::dropEvent(event);
                  //event->acceptProposedAction();
                  //d->parent()->setExpanded(true);
                //Update tree?
        }
        else{
            event->ignore();
        }
    }else{
        transfer(source, tr("Horizon -1"));
        QTreeWidget::dropEvent(event);
    }

    currentDragItemPosition = QPoint(); //Recent the current source

}


void SiteTree::dragEnterEvent(QDragEnterEvent *event)
{
    QTreeWidget::dragEnterEvent(event);
    QTreeWidgetItem * source = itemAt(event->pos());

        if(!source->text(0).contains(tr("Horizon"))){
            currentDragItemPosition = event->pos(); //A horizon should not be dragged!
        }else{
            event->ignore();
        }
}

void SiteTree::dragMoveEvent(QDragMoveEvent *event)
{
    QTreeWidgetItem *source = itemAt(event->pos());
    QTreeWidget::dragMoveEvent(event);
    if(source){
        if(source->text(0).contains(tr("Couche"))){
           //source->parent()->setBackgroundColor(0, Qt::cyan );
        }
    }
}

void SiteTree::keyPressEvent(QKeyEvent *event)
{
    QTreeWidgetItem *item= currentItem();
    //When the user presses a specific key in the tree
    if(event->key() == Qt::Key_Delete ||event->key() == Qt::Key_Backspace){
        QString text = QString("Delete %1").arg(item->text(0));
        QMessageBox::information(this, "", text);
    }else if(event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return){
        openItem(item, 0);
    }else if(event->key() == Qt::Key_Up){//Implement keyboard navigation
        //Control out of bounds
        if(indexAbove(currentIndex()).isValid()){
             setCurrentIndex(indexAbove(currentIndex()));
        }else{
            //setCurrentIndex(); //Move to the bottom ? How?
        }
    }else if(event->key() == Qt::Key_Down){
        if(indexBelow(currentIndex()).isValid()){
        setCurrentIndex(indexBelow(currentIndex())); //Implement keyboard navigation
        }else{
            //Move to top..
        }
   }
}

bool SiteTree::checkTransfer(QString source, QString destination)
{
    if(source.isEmpty() || destination.isEmpty()){
        return false;
    }
    else if(source.contains(tr("Horizon")) && destination.contains(tr("Horizon"))){
        return false;
    }
    else if(source.contains(tr("Horizon")) && destination.contains(tr("Couche"))){
        return false;
    }
    else if(source.contains(tr("Couche")) && destination.contains(tr("Couche"))){
        return false;
    }
    return true;
}

void SiteTree::transfer(QString source, QString destination)
{
    if(source.contains(tr("Couche")) && destination.contains(tr("Horizon"))){
        //Transfer a layer to another horizon
        int horizonId = extractHorizonId(destination);
        int layerId = extractLayerId(source);

        HorizonService service(filePath, horizonId);
        service.transferLayer(layerId);
    }
}

int SiteTree::extractLayerId(QString string)
{
    QStringList list = string.split(tr("Couche "));
    QString idString = list.at(1);

    return idString.toInt();
}

int SiteTree::extractHorizonId(QString string)
{
    QStringList list = string.split(tr("Horizon "));
    QString idString = list.at(1);

    return idString.toInt();
}

void SiteTree::openItem(QString itemText)
{
    if(itemText.contains(tr("Horizon"))){
        int horizonId = extractHorizonId(itemText);
        emit openVH(horizonId);
    }
}

void SiteTree::openItem(QTreeWidgetItem *item, int column)
{
    QString s = item->text(column);
    if(s.contains(tr("Horizon"))){
        int horizonId = extractHorizonId(s);
        emit openVH(horizonId);
    }else if(s.contains(tr("Couche"))){
        int layerId = extractLayerId(s);
        emit openVL(layerId);
    }else if(s.contains("-")){
        int objectId = item->data(1,0).toInt();
        emit openVO(objectId);
    }
}

void SiteTree::showContextMenu(const QPoint& pos) // this is a slot
{
    //Manage the right click button on the tree widget
    // for most widgets
    QPoint globalPos = mapToGlobal(pos);
    QMenu menu;

    QTreeWidgetItem *item = itemAt(pos);
    if(item){
        if(item->text(0).contains(tr("Horizon"))){
                //Set locally the horizon id
                this->horizonId = extractHorizonId(item->text(0));
                QAction *openHorizon = new QAction(tr("Ouvrir"), parentWidget());
                connect(openHorizon, SIGNAL(triggered()), this, SLOT(openVH()));

                QAction *createLayer = new QAction(tr("Ajouter une couche"), parentWidget());
                connect(createLayer, SIGNAL(triggered()), this, SLOT(openCL()));

                QAction *deleteHorizon = new QAction(tr("Supprimer"), parentWidget());
                connect(deleteHorizon, SIGNAL(triggered()), this, SLOT(deleteHorizon()));

                menu.addAction(openHorizon);
                menu.addAction(createLayer);
                menu.addAction(deleteHorizon);
         }else if(item->text(0).contains(tr("Couche"))){
                this->layerId = extractLayerId(item->text(0));
                QAction *openLayer = new QAction(tr("Ouvrir"), parentWidget());
                connect(openLayer, SIGNAL(triggered()), this, SLOT(openVL()));

                QAction *createObject = new QAction(tr("Ajouter un objet"), parentWidget());
                connect(createObject, SIGNAL(triggered()), this, SLOT(createObject()));

                menu.addAction(openLayer);
                menu.addAction(createObject);
                menu.addAction(tr("Supprimer"));
        }else if(item->text(0).contains("-")){
            objectId = item->data(1, 0).toInt();
            QAction *openObject = new QAction(tr("Ouvrir"), parentWidget());
            connect(openObject, SIGNAL(triggered()), this, SLOT(openVO()));

            menu.addAction(openObject);
            menu.addAction(tr("Supprimer"));
        }
    }
    else{
        QAction *createHorizon = new QAction(tr("Ajouter un horizon"), parentWidget());
        connect(createHorizon, SIGNAL(triggered()), parentWidget()->parentWidget(), SLOT(openCH()));
        QAction *createLayer = new QAction(tr("Ajouter une couche"), parentWidget());
        connect(createLayer, SIGNAL(triggered()), parentWidget()->parentWidget(), SLOT(openCL()));

        menu.addAction(createHorizon);
        menu.addAction(createLayer);

    }


    QAction* selectedItem = menu.exec(globalPos);
    if (selectedItem)
    {
        // something was chosen, do stuff
    }
    else
    {
        // nothing was chosen
    }

}

void SiteTree::openCL()
{
    emit openCL(horizonId);
}

void SiteTree::openVH()
{
    emit openVH(horizonId);
}

void SiteTree::openVL()
{
    emit openVL(layerId);
}

void SiteTree::openVO()
{
    emit openVO(objectId);
}

void SiteTree::deleteHorizon()
{
    emit deleteHorizon(horizonId);
}

void SiteTree::createObject()
{
    emit openCO(layerId);
}
