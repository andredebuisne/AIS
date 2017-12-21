#include "sitefileservice.h"
#include "fileerror.h"


SiteFileService::SiteFileService(QString filePath)
{
    this->filePath = filePath;
}

void SiteFileService::createSite(Site &site)
{
   QFile file(filePath); //Open the file
   if(file.exists()){
       throw new FileError(1); //File already exists
   }
   else{
       if(!file.open(QIODevice::ReadWrite)){
           throw new FileError(2);
       }
       QDataStream out(&file);
       out.setVersion(QDataStream::Qt_DefaultCompiledVersion);
       out << site;
       if(!file.flush()){
            throw new FileError(3);
       }
       file.close();
       }
}

void SiteFileService::insertLayerIdInSite(int horizonId, int layerId)
{
    Site site(filePath);
    site = findSite();

    int horizonIndex = findHorizonIndex(horizonId);
    QList<Horizon> horizons = site.getHorizons();
    Horizon horizon = horizons.at(horizonIndex);
    QList<int> layerIds = horizon.getLayerIds();

    int layerInsertIndex = findLayerInsertIndex(horizonIndex, layerId);
    layerIds.insert(layerInsertIndex,layerId);
    horizon.setLayerIds(layerIds);
    horizons.replace(horizonIndex, horizon);
    site.setHorizons(horizons);

    updateSite(site);
}

Site SiteFileService::findSite()
{

    Site site(filePath);
    QFile file(filePath); //Open the file
    if(!file.exists()){
        throw new FileError(0);
    }
    else{
        if(!file.open(QIODevice::ReadWrite)){
            throw new FileError(2);
        }

        QDataStream in(&file);
        in.setVersion(QDataStream::Qt_DefaultCompiledVersion);

        in >> site;

        if(!file.flush()){
            throw new FileError(3);
        }
        file.close();

        return site;
    }


}

void SiteFileService::createHorizon(Horizon horizon)
{
    Site site(filePath);
    QFile file(filePath); //Open the file
    if(!file.exists()){
        throw new FileError(0);
    }
    else{
        if(!file.open(QIODevice::ReadWrite)){
            throw new FileError(2);
        }
        QDataStream in(&file);
        in.setVersion(QDataStream::Qt_DefaultCompiledVersion);
        in >> site;
        if(!file.flush()){
            throw new FileError(3);
        }
        file.close();
    }
    if(findHorizonIndex(horizon.getId()) != -1){
        throw new FileError(8);
    }
    int index = findHorizonInsertIndex(horizon.getId()); //No need to sort the list now!
    QList<Horizon> siteHorizons = site.getHorizons();
    siteHorizons.insert(index, horizon);
    site.setHorizons(siteHorizons);

    updateSite(site);

}

void SiteFileService::removeHorizon(int horizonId, bool deleteLayers)
{
    Site site(filePath);
    site = findSite();

    int horizonIndex = findHorizonIndex(horizonId);
    Horizon horizon = site.getHorizons().at(horizonIndex);
    QList<Horizon> horizons = site.getHorizons();

    if(deleteLayers){ //User wants to delete all associated layers
        for(int i = 0; i < horizon.getLayerIds().size(); i++){
            QString layerPath = createLayerPath(horizon.getLayerIds().at(i));
            QFile::remove(layerPath); //Remove the file

            //TODO --> Remove the relatioship
        }
        horizons.removeAt(horizonIndex);
        site.setHorizons(horizons);

    }else if(!deleteLayers){ //User wants to keep all the layers, we put them in horizon -1
        Horizon baseHorizon = site.getHorizons().at(0); //It's the base horizon at index 0, always
        QList<int> baseLayerIds = baseHorizon.getLayerIds();
        for(int i = 0; i < horizon.getLayerIds().size(); i++){
            int layerId = horizon.getLayerIds().at(i);
            baseLayerIds.append(layerId);
        }
        baseHorizon.setLayerIds(baseLayerIds);
        horizons.replace(0, baseHorizon); //Update the base horizon
        horizons.removeAt(horizonIndex);
        site.setHorizons(horizons);
    }
    updateSite(site);

}

void SiteFileService::updateHorizon(int horizonId, Horizon newHorizon)
{
    Site site(filePath);
    site = findSite();
    int horizonIndex = findHorizonIndex(horizonId);
    //Link the layer ids, as they are not included in the new horizon
    QList<int> layerIds = site.getHorizons().at(horizonIndex).getLayerIds();
    newHorizon.setLayerIds(layerIds);
    QList<Horizon> horizons = site.getHorizons();
    if(horizonId == newHorizon.getId()){
        //Id is unchanged
        horizons.replace(horizonIndex, newHorizon);
    }else{
         //Id is different, need to reinsert at a new index
        int newInsertIndex = findHorizonInsertIndex(newHorizon.getId());
        horizons.insert(newInsertIndex, newHorizon);
        horizons.removeAt(horizonIndex);
    }
    site.setHorizons(horizons);
    updateSite(site);
}

int SiteFileService::findHorizonIdForLayer(int layerId)
{
    Site site(filePath);
    site = findSite();

    for(int i = 0; i < site.getHorizons().size(); i++){
        Horizon horizon = site.getHorizons().at(i);
        for(int j = 0; j < horizon.getLayerIds().size(); j++){
            if(horizon.getLayerIds().at(j) == layerId)
                return horizon.getId();
        }
    }
}

void SiteFileService::updateSite(Site site)
{
    QFile file(filePath); //Open the file
    if(!file.exists()){
        throw new FileError(0);
    }
    else{
        if(!file.open(QIODevice::ReadWrite | QIODevice::Truncate)){
            throw new FileError(2);
        }
        QDataStream out(&file);
        out.setVersion(QDataStream::Qt_DefaultCompiledVersion);
        out << site;
        if(!file.flush()){
            throw new FileError(3);
        }
        file.close();
        }

}

Horizon SiteFileService::loadHorizon(int horizonId)
{
    Site site(filePath);
    site = findSite();
    Horizon horizon = site.getHorizons().at(findHorizonIndex(horizonId));
    return horizon;
}

int SiteFileService::findHorizonInsertIndex(int horizonId)
{
    //Find what index to insert the new horizon
    Site site(filePath);
    site = findSite();
    int index = 0;

    for(int i = 0; i < site.getHorizons().size(); i++){
        if(site.getHorizons().at(i).getId() < horizonId){ //No <= because verification is made before
            index = i;
        }
        if(site.getHorizons().at(i).getId() > horizonId){
            break;
        }

        //As soon as the id is higher than our new id, we stop
    }
    return index + 1;
}

int SiteFileService::findHorizonIndex(int horizonId)
{
    //Binary search (log(n)) efficiency
    Site site(filePath);
    site = findSite();
    QList<Horizon> h = site.getHorizons();
    //List is already sorted because of our smart insert :)
    //Search variables
    int low = 0;
    int high = h.size() -1;
    int mid; //Value to be returned, that we are looking for

    while( low <= high){
        mid = (low + high) / 2;
        if(horizonId == h.at(mid).getId()){
            return mid;
        }else if(horizonId >h.at(mid).getId()){
            low = mid + 1;
        }else{
            high = mid - 1;
        }
    }
    return -1;
}

void SiteFileService::createLayer(int horizonId, Layer layer)
{
    //Create layer file and insert layer
    QString layerPath = createLayerPath(layer.getId());
    QFile file(layerPath);
    if(file.exists()){
        throw new FileError(9);
    }else{
        if(!file.open(QIODevice::ReadWrite)){
            throw new FileError(2);
        }

        QDataStream out(&file);
        out.setVersion(QDataStream::Qt_DefaultCompiledVersion);

        out << layer;

        if(!file.flush()){
            throw new FileError(3);
        }
        file.close();
    }
    //Insert layer id into the the horizon number {horizonId}
    insertLayerIdInSite(horizonId, layer.getId());

}


Layer SiteFileService::loadLayer(int layerId)
{
    Layer layer;
    QString layerPath = getLayerPath(layerId);
    QFile file(layerPath);
    if(!file.exists()){
        throw new FileError(0);
    }else{
        if(!file.open(QIODevice::ReadWrite)){
            throw new FileError(2);
        }

        QDataStream in(&file);
        in.setVersion(QDataStream::Qt_DefaultCompiledVersion);

        in >> layer;

        if(!file.flush()){
            throw new FileError(3);
        }
        file.close();
    }
    return layer;

}

void SiteFileService::transferLayer(int horizonId, int layerId)
{
    Site site(filePath);
    site = findSite();
    //catch errors here

    int oldHorizonId = findHorizonIdForLayer(layerId);
    if(oldHorizonId != horizonId){

        int oldHorizonIndex = findHorizonIndex(oldHorizonId);
        int newHorizonIndex = findHorizonIndex(horizonId);

        QList<Horizon> oldHorizons = site.getHorizons();

        Horizon oldHorizon = oldHorizons.at(oldHorizonIndex);
        QList<int> oldLayerIds = oldHorizon.getLayerIds();
        oldLayerIds.removeAll(layerId); //Remove the old layer id
        oldHorizon.setLayerIds(oldLayerIds);
        oldHorizons.replace(oldHorizonIndex, oldHorizon);

        Horizon newHorizon = oldHorizons.at(newHorizonIndex);
        QList<int> newLayerIds = newHorizon.getLayerIds();
        newLayerIds.push_back(layerId);
        newHorizon.setLayerIds(newLayerIds);
        oldHorizons.replace(newHorizonIndex, newHorizon);

        site.setHorizons(oldHorizons);

        updateSite(site);
    }

}

int SiteFileService::findLayerInsertIndex(int horizonIndex, int layerId)
{
    Site site(filePath);
    site = findSite();
    int index = 0;

    Horizon horizon = site.getHorizons().at(horizonIndex);
    for(int i = 0; i < horizon.getLayerIds().size(); i++){
        if(horizon.getLayerIds().at(i) < layerId){
            index = i;
        }
        if(horizon.getLayerIds().at(i) > layerId){
            return i;
        }
    }
    return index + 1;
}

int SiteFileService::findLayerIndex(int horizonIndex, int layerId)
{
    //Binary search (log(n)) efficiency
    Site site(filePath);
    site = findSite();
    QList<int> l = site.getHorizons().at(horizonIndex).getLayerIds();
    //List is already sorted because of our smart insert :)
    //Search variables
    int low = 0;
    int high = l.size() -1;
    int mid; //Value to be returned, that we are looking for

    while( low <= high){
        mid = (low + high) / 2;
        if(layerId == l.at(mid)){
            return mid;
        }else if(layerId >l.at(mid)){
            low = mid + 1;
        }else{
            high = mid - 1;
        }
    }
    return -1;
}

int SiteFileService::findRelationshipInsertIndex(int layerId)
{
    Site site(filePath);
    site = findSite();
    int index = 0;

    for(int i = 0; i < site.getRelationships().size(); i++){
        Relationship rl = site.getRelationships().at(i);
        if(rl.getLayerId() < layerId){
            index = i;
        }
        if(rl.getLayerId() > layerId){
            return i;
        }
    }
    return index + 1;

}

int SiteFileService::findRelationshipIndex(int layerId)
{
    Site site(filePath);
    site = findSite();
    QList<Relationship> rl = site.getRelationships();

    int low = 0;
    int high = rl.size() -1;
    int mid; //Value to be returned, that we are looking for

    while( low <= high){
        mid = (low + high) / 2;
        if(layerId == rl.at(mid).getLayerId()){
            return mid;
        }else if(layerId > rl.at(mid).getLayerId()){
            low = mid + 1;
        }else{
            high = mid - 1;
        }
    }
    return -1;

}

QList<Relationship> SiteFileService::findLowerLayers(int layerId)
{
    //Find all the layers directly below one layer
    Site site(filePath);
    site = findSite();
    QList<Relationship> relationships = site.getRelationships();
    QList<Relationship> rlist;
    Relationship currentRl = loadRelationship(layerId);

    if(currentRl.getEarlierThan() != 0){
        rlist.push_back(currentRl);
    }

    for(int i = 0; i < relationships.size(); i++){
        Relationship r = relationships.at(i);
        if(r.getEarlierThan() == layerId){
            rlist.push_back(r);
        }
    }
    return rlist;
}

QList<Relationship> SiteFileService::findUpperLayers(int layerId)
{
    Site site(filePath);
    site = findSite();
    QList<Relationship> relationships = site.getRelationships();
    QList<Relationship> rlist;
    Relationship currentRl = loadRelationship(layerId);

    if(currentRl.getLaterThan() != 0){
        rlist.push_back(currentRl);
    }

    for(int i = 0; i < relationships.size(); i++){
        Relationship r = relationships.at(i);
        if(r.getLaterThan() == layerId){
            rlist.push_back(r);
        }
    }
    return rlist;
}

QList<Relationship> SiteFileService::findEqualLayers(int layerId)
{
    Site site(filePath);
    site = findSite();
    QList<Relationship> relationships = site.getRelationships();
    QList<Relationship> rlist;

    Relationship currentRl = loadRelationship(layerId);

    if(currentRl.getEqualTo() != 0){
        rlist.push_back(currentRl);
    }

    for(int i = 0; i < relationships.size(); i++){
        Relationship r = relationships.at(i);
        if(r.getEqualTo() == layerId){
            rlist.push_back(r);
        }
    }
    return rlist;
}

QList<Relationship> SiteFileService::findContemporaryLayers(int layerId)
{
    Site site(filePath);
    site = findSite();
    QList<Relationship> relationships = site.getRelationships();
    QList<Relationship> rlist;
    Relationship currentRl = loadRelationship(layerId);

    if(currentRl.getContemporaryTo() != 0){
        rlist.push_back(currentRl);
    }

    for(int i = 0; i < relationships.size(); i++){
        Relationship r = relationships.at(i);
        if(r.getContemporaryTo() == layerId){
            rlist.push_back(r);
        }
    }
    return rlist;
}

Relationship SiteFileService::loadRelationship(int layerId)
{
    Site site(filePath);
    site = findSite();

    int rIndex = findRelationshipIndex(layerId);

    return site.getRelationships().at(rIndex);
}


void SiteFileService::createRelationship(Relationship relationship)
{
    Site site(filePath);
    site = findSite();

    QList<Relationship> relationships = site.getRelationships();
    int index = findRelationshipInsertIndex(relationship.getLayerId());
    relationships.insert(index, relationship);

    site.setRelationships(relationships);
    updateSite(site);
}

QString SiteFileService::createLayerPath(int layerId)
{
    QString layerPath;
    QStringList partsList = filePath.split('/'); //Split my file path in all folders
    for(int i=0; i <partsList.size()-1;i++){
        layerPath.append(partsList.at(i)); //Add all partLists to the filename except the last one
        layerPath.append('/');
    }
    layerPath.append("layers");
    QDir dir;
    dir.mkpath(layerPath); //Create the /layers directory
    layerPath.append("/");
    layerPath.append(QString::number(layerId));
    layerPath.append(".arcus");

    return layerPath;
}

QString SiteFileService::getLayerPath(int layerId)
{
    QString layerPath;
    QStringList partsList = filePath.split('/'); //Split my file path in all folders
    for(int i=0; i <partsList.size()-1;i++){
        layerPath.append(partsList.at(i)); //Add all partLists to the filename except the last one
        layerPath.append('/');
    }
    layerPath.append("layers/");
    layerPath.append(QString::number(layerId));
    layerPath.append(".arcus");

    return layerPath;
}

void SiteFileService::removeLayer(int layerId)
{
    Site site(filePath);
    site = findSite();
    QString layerPath = createLayerPath(layerId);
    bool success;
    success = QFile::remove(layerPath);
    if(!success){
        throw new FileError(11);
    }
    //Remove from the horizon list
    int horizonIndex = findHorizonIndex(findHorizonIdForLayer(layerId));
    QList<Horizon> horizons = site.getHorizons();
    Horizon horizon = horizons.at(horizonIndex);
    QList<int> layerIds = horizon.getLayerIds();
    layerIds.removeAll(layerId);
    horizon.setLayerIds(layerIds);
    horizons.replace(horizonIndex, horizon);
    site.setHorizons(horizons);

    //Remove from relationships
    QList<Relationship> relationships = site.getRelationships();
    int relationshipIndex = findRelationshipIndex(layerId);
    relationships.removeAt(relationshipIndex);
    site.setRelationships(relationships);

    updateSite(site);

}

void SiteFileService::updateLayer(int layerId, Layer newLayer)
{
    if(layerId == newLayer.getId()){ //Ids don't change
        QString layerPath = getLayerPath(layerId);
        QFile file(layerPath);
        if(!file.exists()){
            throw new FileError(0);
        }else{
            if(!file.open(QIODevice::ReadWrite | QIODevice::Truncate)){
                throw new FileError(2);
            }

            QDataStream out(&file);
            out.setVersion(QDataStream::Qt_DefaultCompiledVersion);

            out << newLayer;

            if(!file.flush()){
                throw new FileError(3);
            }
            file.close();
        }



    }else{
        //Ids change
        //Delete old file
        bool createNewLayer = true;
        int horizonId = findHorizonIdForLayer(layerId);
        //Insert layer in new .arcus file
        try{
            createLayer(horizonId, newLayer);
        }catch(FileError *error){
            throw new FileError(9);
            createNewLayer = false;
        }
        if(createNewLayer){
            QString layerPath = createLayerPath(layerId);
            QFile::remove(layerPath);

            //Replace layer id in horizon

            Site site(filePath);
            site = findSite();

            QList<Horizon> horizons = site.getHorizons();
            int horizonIndex = findHorizonIndex(horizonId);
            Horizon horizon = horizons.at(horizonIndex);
            QList<int> layerIds = horizon.getLayerIds();
            layerIds.removeAll(layerId);
            horizon.setLayerIds(layerIds);
            horizons.replace(horizonIndex, horizon);
            site.setHorizons(horizons);

            //Replace layerId in the relationship
            QList<Relationship> relationships = site.getRelationships();
            int relationshipIndex = findRelationshipIndex(layerId);
            Relationship rl = relationships.at(relationshipIndex);
            rl.setLayerId(newLayer.getId());
            relationships.replace(relationshipIndex, rl);
            site.setRelationships(relationships);
            updateSite(site);
        }
    }
}
