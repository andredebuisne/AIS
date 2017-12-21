#include "relationshipservice.h"

RelationshipService::RelationshipService(QString filePath)
{
    this->filePath = filePath;
     fService = new SiteFileService(filePath);
}

QList<Relationship> RelationshipService::findLowerLayers(int layerId)
{
    return fService->findLowerLayers(layerId);
}

QList<Relationship> RelationshipService::findUpperLayers(int layerId)
{
    return fService->findUpperLayers(layerId);
}

QList<Relationship> RelationshipService::findEqualLayers(int layerId)
{
    return fService->findEqualLayers(layerId);
}

QList<Relationship> RelationshipService::findContemporaryLayers(int layerId)
{
    return fService->findContemporaryLayers(layerId);
}
