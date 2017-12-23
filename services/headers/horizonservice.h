#ifndef HORIZONSERVICE_H
#define HORIZONSERVICE_H
#include <QtWidgets>
#include "sitefileservice.h"
#include "classes/headers/layer.h"

class HorizonService
{
public:
    HorizonService(QString filePath, int horizonId = -1); //When we want to work with layers, we don't need a horizonId
    Layer loadLayer(int layerId);
    void insertLayer(Layer layer);
    void removeLayer(int layerId);
    void updateLayer(int layerId, Layer newLayer);
    void transferLayer(int layerId);


private:
    SiteFileService *fService;
    int horizonId;



};

#endif // HORIZONSERVICE_H
