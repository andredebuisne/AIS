#ifndef LAYERSERVICE_H
#define LAYERSERVICE_H
#include "layer.h"
#include "layerfileservice.h"


class LayerService
{
public:
    LayerService(QString filePath);
    void insertObject(int layerId, Object object);
    Object loadObject(int objectId);

private:
    LayerFileService *fService;
    QString filePath;

};

#endif // LAYERSERVICE_H
