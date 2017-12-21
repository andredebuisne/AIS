#ifndef SITE_H
#define SITE_H
#include <QtWidgets>
#include "horizon.h"
#include "relationship.h"

/*Site class. A Site is saved in a .archeo file and contains:
    *Site information
    *List of horizons
*/

class Site
{
public:
    //Functions
    Site(QString filePath = nullptr); //Basic constructor
    void insertHorizon(Horizon);
    void removeHorizon(Horizon);
    void updateHorizon(int, Horizon);
    void createSite(); //Create the site file and insert the site

    //Set operators for i/o file operations

    friend QDataStream & operator <<( QDataStream& stream, const Site& site );
    friend QDataStream & operator >>( QDataStream& stream, Site& site );
    //Getters and setters
    long getId() const;
    void setId(long value);

    QString getName() const;
    void setName(const QString &value);

    QString getLocation() const;
    void setLocation(const QString &value);

    QList<double> getLocationXY() const;
    void setLocationXY(const QList<double> &value);

    double getAltitude() const;
    void setAltitude(double value);

    QString getModernCity() const;
    void setModernCity(const QString &value);

    QString getAncientCity() const;
    void setAncientCity(const QString &value);

    QString getModernCountry() const;
    void setModernCountry(const QString &value);

    QString getAncientRegion() const;
    void setAncientRegion(const QString &value);

    QDate getDateBegin() const;
    void setDateBegin(const QDate &value);

    QDate getDateEnd() const;
    void setDateEnd(const QDate &value);

    QString getDirector() const;
    void setDirector(const QString &value);

    int getNumDiggers() const;
    void setNumDiggers(int value);

    int getExcavationType() const;
    void setExcavationType(int value);

    QList<Horizon> getHorizons() const;
    void setHorizons(const QList<Horizon> &value);

    QList<Relationship> getRelationships() const;
    void setRelationships(const QList<Relationship> &value);

private:
    //Members
    long id; //Id is for internet upload
    QString name;
    QString location;
    QList<double> locationXY; //The x y location for a map is stored in a two value array of ints
    double altitude;
    QString modernCity;
    QString ancientCity;
    QString modernCountry;
    QString ancientRegion;
    QDate dateBegin;
    QDate dateEnd;
    QString director;
    int numDiggers;
    int excavationType;
    QList<Horizon> horizons;
    QList<Relationship> relationships;

    //Service members
    QString filePath;


};

#endif // SITE_H
