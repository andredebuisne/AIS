#include "siteservice.h"

SiteService::SiteService(QString filePath)
{
    this->filePath = filePath;
    fService = new SiteFileService(filePath);
}

Horizon SiteService::loadHorizon(int horizonId)
{
    return fService->loadHorizon(horizonId);
}

void SiteService::createSite(Site &site)
{
    //Verifications

    //Create site
    fService->createSite(site);
}

Site SiteService::loadSite()
{
    Site site(filePath);
    site = fService->findSite();
    return site;
}

void SiteService::insertHorizon(Horizon horizon)
{
    fService->createHorizon(horizon);
}

void SiteService::removeHorizon(int horizonId, bool deleteLayers)
{
    fService->removeHorizon(horizonId, deleteLayers);
}

void SiteService::updateHorizon(int horizonId, Horizon newHorizon)
{
    fService->updateHorizon(horizonId, newHorizon);
}


void SiteService::createRelationship(Relationship relationship)
{
    fService->createRelationship(relationship);
}

Relationship SiteService::loadRelationship(int layerId)
{
    return fService->loadRelationship(layerId);
}
