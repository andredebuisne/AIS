#include "horizonservice.h"

HorizonService::HorizonService(QString filePath, int horizonId)
{
    fService = new SiteFileService(filePath);
    this->horizonId = horizonId;
}

Layer HorizonService::loadLayer(int layerId)
{
    return fService->loadLayer(layerId);
}

void HorizonService::insertLayer(Layer layer)
{
    fService->createLayer(horizonId, layer);
}

void HorizonService::removeLayer(int layerId)
{
    fService->removeLayer(layerId);
}

void HorizonService::updateLayer(int layerId, Layer newLayer)
{
    fService->updateLayer(layerId, newLayer);
}

void HorizonService::transferLayer(int layerId)
{
   fService->transferLayer(horizonId, layerId);
}
