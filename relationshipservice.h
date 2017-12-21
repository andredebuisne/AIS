#ifndef RELATIONSHIPSERVICE_H
#define RELATIONSHIPSERVICE_H
#include <QtWidgets>
#include "relationship.h"
#include "sitefileservice.h"

class RelationshipService
{
public:
    RelationshipService(QString filePath);
    QList<Relationship> findLowerLayers(int layerId);
    QList<Relationship> findUpperLayers(int layerId);
    QList<Relationship> findEqualLayers(int layerId);
    QList<Relationship> findContemporaryLayers(int layerId);


private:
    SiteFileService *fService;
    QString filePath;
};

#endif // RELATIONSHIPSERVICE_H
