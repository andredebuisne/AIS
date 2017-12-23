#include "services/headers/layerfileservice.h"
#include "services/headers/sitefileservice.h"
#include "classes/headers/layer.h"
#include "errors/headers/fileerror.h"

LayerFileService::LayerFileService(QString filePath)
{
    this->filePath = filePath;
}

void LayerFileService::insertObject(int layerId, Object object)
{
    QString layerPath = getLayerPath(layerId);
    QFile file(layerPath);
    Layer layer;
    if(!file.exists()){
        throw new FileError(0);
    }else{
        if(!file.open(QIODevice::ReadWrite)){
            throw new FileError(2);
        }

        QDataStream in(&file);
        in.setVersion(QDataStream::Qt_DefaultCompiledVersion);

        in >> layer;

        if(!file.flush()){
            throw new FileError(3);
        }
        file.close();
        if(objectExists(object.getId())){
            throw new FileError(10);
        }
            QList<Object> objects = layer.getObjects();
            objects.append(object);
            layer.setObjects(objects);
            SiteFileService siteService(filePath);
            siteService.updateLayer(layerId, layer);
    }


}

Object LayerFileService::loadObject(int objectId)
{
    //Find the object with a find algorithm
    Site site(filePath);
    SiteFileService sService(filePath);
    site = sService.findSite();

    for(int i = 0; i < site.getHorizons().size(); i++){
        Horizon horizon = site.getHorizons().at(i);

        for(int j = 0; j < horizon.getLayerIds().size(); j++){
            Layer layer = sService.loadLayer(horizon.getLayerIds().at(j));

            QList<Object> o = layer.getObjects();
            //List is already sorted because of our smart insert :)
            //Search variables
            int low = 0;
            int high = o.size() -1;
            int mid; //Value to be returned, that we are looking for

            while( low <= high){
                mid = (low + high) / 2;
                if(objectId == o.at(mid).getId()){
                    return layer.getObjects().at(mid);
                }else if(objectId >o.at(mid).getId()){
                    low = mid + 1;
                }else{
                    high = mid - 1;
                }
            }


        }

    }
}

QString LayerFileService::getLayerPath(int layerId)
{
    QString layerPath;
    QStringList partsList = filePath.split('/'); //Split my file path in all folders
    for(int i=0; i <partsList.size()-1;i++){
        layerPath.append(partsList.at(i)); //Add all partLists to the filename except the last one
        layerPath.append('/');
    }
    layerPath.append("layers/");
    layerPath.append(QString::number(layerId));
    layerPath.append(".arcus");

    return layerPath;
}

bool LayerFileService::objectExists(int objectId)
{
    Site site(filePath);
    bool exists = false;
    SiteFileService sService(filePath);
    site = sService.findSite();

    for(int i = 0; i < site.getHorizons().size(); i++){
        Horizon horizon = site.getHorizons().at(i);

        for(int j = 0; j < horizon.getLayerIds().size(); j++){
            Layer layer = sService.loadLayer(horizon.getLayerIds().at(j));
            QList<Object> o = layer.getObjects();
            int low = 0;
            int high = o.size() -1;
            int mid; //Value to be returned, that we are looking for

            while( low <= high){
                mid = (low + high) / 2;
                if(objectId == o.at(mid).getId()){
                    exists = true;
                    break;
                }else if(objectId >o.at(mid).getId()){
                    low = mid + 1;
                }else{
                    high = mid - 1;
                }
            }

        }

    }
    return exists;
}
