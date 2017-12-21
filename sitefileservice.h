#ifndef SITEFILESERVICE_H
#define SITEFILESERVICE_H
#include "horizon.h"
#include "layer.h"
#include <QtWidgets>
#include "site.h"


class SiteFileService
{
public:
    //Site
    SiteFileService(QString filePath);
    void createSite(Site &site);
    void insertLayerIdInSite(int horizonId, int layerId);
    Site findSite();
    void updateSite(Site site);
   //Horizon
    Horizon loadHorizon(int horizonId);
    int findHorizonInsertIndex(int horizonId);
    int findHorizonIndex(int horizonId);
    void createHorizon( Horizon horizon);
    void removeHorizon(int horizonId, bool deleteLayers);
    void updateHorizon(int horizonId, Horizon newHorizon);
    int findHorizonIdForLayer(int layerId);
    //Layer
    void createLayer(int horizonId, Layer layer);
    QString createLayerPath(int layerId); //Convert the file path into a layerPath
    QString getLayerPath(int layerId);// This doesn't create the file and directory, only gives the path
    void removeLayer(int layerId);
    void updateLayer(int layerId, Layer newLayer);
    Layer loadLayer(int layerId);
    void transferLayer(int horizonId, int layerId);
    int findLayerInsertIndex(int horizonIndex, int layerId);
    int findLayerIndex(int horizonIndex,int layerId);
    //Relationship
    void createRelationship(Relationship relationship);
    int findRelationshipInsertIndex(int layerId);
    int findRelationshipIndex(int layerId);
    QList<Relationship> findLowerLayers(int layerId);
    QList<Relationship> findUpperLayers(int layerId);
    QList<Relationship> findEqualLayers(int layerId);
    QList<Relationship> findContemporaryLayers(int layerId);
    Relationship loadRelationship(int layerId);


private:
    QString filePath;
};

#endif // SITEFILESERVICE_H
