#include "classes/headers/site.h"
#include "services/headers/siteservice.h"

Site::Site(QString filePath)
{
    //Set the filePath for the whole path
    this->filePath =filePath;

    //Initialize all the values
    id = -1; //During upload on the internet, we know the site has not been an id
    name = QString(); //Empty string
    location = QString();
    locationXY = {0.000000, 0.000000};
    altitude = 0.00;
    modernCity = QString();
    ancientCity = QString();
    modernCountry = QString();
    ancientRegion = QString();
    dateBegin = QDate();
    dateEnd = QDate();
    director = QString();
    numDiggers = 0;
    excavationType = -1; //Undefined

    //Create the base horizon
    Horizon baseHorizon; //Add corresponding fields here
    baseHorizon.setId(-1);
    baseHorizon.setName("Default");
    baseHorizon.setType(-1);
    horizons.push_back(baseHorizon);
}

void Site::createSite()
{
    //Specific for this function : the file path is directory/sitename.archeo
    //Create the directory here
    QString filename;
    filename.append(filePath);
    filename.append("/");
    filename.append(getName());
    QDir dir;
    dir.mkpath(filename);
    QString completeFilePath = QString("%1/%2/%3.archeo").arg(filePath).arg(getName()).arg(getName().toLower());
    SiteService siteService(completeFilePath);
    siteService.createSite(*this);
}


void Site::insertHorizon(Horizon horizon)
{
    //Catch error here
    SiteService service(filePath);
    service.insertHorizon(horizon);
}

//======================================================================
//=========================== OPERATORS ================================
//======================================================================

QDataStream& operator <<( QDataStream& stream, const Site& site )
{
    return stream << site.name << site.locationXY << site.altitude <<
                     site.modernCity << site.ancientCity << site.modernCountry <<
                     site.ancientRegion << site.dateBegin << site.dateEnd <<
                     site.director << site.numDiggers << site.excavationType << site.horizons <<
                     site.relationships;
    //TODO: insert the horizons
}

QDataStream& operator >>( QDataStream& stream, Site& site )
{
    return stream >> site.name >> site.locationXY >> site.altitude >>
                     site.modernCity >> site.ancientCity >> site.modernCountry >>
                     site.ancientRegion >> site.dateBegin >> site.dateEnd >>
                     site.director >> site.numDiggers >> site.excavationType >> site.horizons >>
                     site.relationships;
}

//======================================================================
//====================== GETTERS AND SETTERS ===========================
//======================================================================
long Site::getId() const
{
    return id;
}

void Site::setId(long value)
{
    id = value;
}

QString Site::getName() const
{
    return name;
}

void Site::setName(const QString &value)
{
    name = value;
}

QString Site::getLocation() const
{
    return location;
}

void Site::setLocation(const QString &value)
{
    location = value;
}

QList<double> Site::getLocationXY() const
{
    return locationXY;
}

void Site::setLocationXY(const QList<double> &value)
{
    locationXY = value;
}

double Site::getAltitude() const
{
    return altitude;
}

void Site::setAltitude(double value)
{
    altitude = value;
}

QString Site::getModernCity() const
{
    return modernCity;
}

void Site::setModernCity(const QString &value)
{
    modernCity = value;
}

QString Site::getAncientCity() const
{
    return ancientCity;
}

void Site::setAncientCity(const QString &value)
{
    ancientCity = value;
}

QString Site::getModernCountry() const
{
    return modernCountry;
}

void Site::setModernCountry(const QString &value)
{
    modernCountry = value;
}

QString Site::getAncientRegion() const
{
    return ancientRegion;
}

void Site::setAncientRegion(const QString &value)
{
    ancientRegion = value;
}

QDate Site::getDateBegin() const
{
    return dateBegin;
}

void Site::setDateBegin(const QDate &value)
{
    dateBegin = value;
}

QDate Site::getDateEnd() const
{
    return dateEnd;
}

void Site::setDateEnd(const QDate &value)
{
    dateEnd = value;
}

QString Site::getDirector() const
{
    return director;
}

void Site::setDirector(const QString &value)
{
    director = value;
}

int Site::getNumDiggers() const
{
    return numDiggers;
}

void Site::setNumDiggers(int value)
{
    numDiggers = value;
}

int Site::getExcavationType() const
{
    return excavationType;
}

void Site::setExcavationType(int value)
{
    excavationType = value;
}

QList<Horizon> Site::getHorizons() const
{
    return horizons;
}

void Site::setHorizons(const QList<Horizon> &value)
{
    horizons = value;
}

QList<Relationship> Site::getRelationships() const
{
    return relationships;
}

void Site::setRelationships(const QList<Relationship> &value)
{
    relationships = value;
}
