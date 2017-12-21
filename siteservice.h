#ifndef SITESERVICE_H
#define SITESERVICE_H
#include "sitefileservice.h"
#include "site.h"
#include "horizon.h"
#include "relationship.h"
#include <QtWidgets>

class SiteService
{
public:
    SiteService(QString filePath);
    Horizon loadHorizon(int horizonId); //Find a horizon with its id
    int findHorizonIndex(int horizonId); //Find the index of a horizon with its id
    void sortHorizons(QList<Horizon> horizons);
    void createSite(Site &site);
    Site loadSite();
    void insertHorizon(Horizon horizon);
    void removeHorizon(int horizonId, bool deleteLayers);
    void updateHorizon(int horizonId, Horizon newHorizon);

    //Relationship
    void createRelationship(Relationship relationship);
    Relationship loadRelationship(int layerId);

private:
    SiteFileService *fService ; //Manipulate the data in files through this service
    QString filePath; //Where the site is stored

};

#endif // SITESERVICE_H
