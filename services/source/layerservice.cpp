#include "services/headers/layerservice.h"

LayerService::LayerService(QString filePath)
{
    this->filePath = filePath;
    this->fService = new LayerFileService(filePath);
}

void LayerService::insertObject(int layerId, Object object)
{
    fService->insertObject(layerId, object);
}

Object LayerService::loadObject(int objectId)
{
    return fService->loadObject(objectId);
}
