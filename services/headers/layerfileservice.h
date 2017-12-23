#ifndef LAYERFILESERVICE_H
#define LAYERFILESERVICE_H
#include "classes/headers/object.h"


class LayerFileService
{
public:
    LayerFileService(QString filePath);
    void insertObject(int layerId, Object object);
    Object loadObject(int objectId);
    QString getLayerPath(int layerId);
    bool objectExists(int objectId);

private:
    QString filePath;
};

#endif // LAYERFILESERVICE_H
