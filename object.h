#ifndef OBJECT_H
#define OBJECT_H
#include <QtWidgets>


class Object
{
public:
    Object();

    //Operators
    friend QDataStream & operator <<( QDataStream& stream, const Object& object );
    friend QDataStream & operator >>( QDataStream& stream, Object& object);
    //Getters and setters
    int getId() const;
    void setId(int value);

    QString getName() const;
    void setName(const QString &value);

    int getType() const;
    void setType(int value);

    QString getMaterial() const;
    void setMaterial(const QString &value);

    double getHeight() const;
    void setHeight(double value);

    double getWidth() const;
    void setWidth(double value);

    double getDepth() const;
    void setDepth(double value);

    double getWeight() const;
    void setWeight(double value);

    double getDiameter() const;
    void setDiameter(double value);

    QString getCivilisation() const;
    void setCivilisation(const QString &value);

    QString getLocation() const;
    void setLocation(const QString &value);

    double getLocationX() const;
    void setLocationX(double value);

    double getLocationY() const;
    void setLocationY(double value);

    double getAltitude() const;
    void setAltitude(double value);

    QString getDescription() const;
    void setDescription(const QString &value);

private:
    int id;
    QString name;
    int type;
    QString material;
    double height;
    double width;
    double depth;
    double weight;
    double diameter;
    QString civilisation;
    QString location;
    double locationX;
    double locationY;
    double altitude;
    QString description;
};

#endif // OBJECT_H
