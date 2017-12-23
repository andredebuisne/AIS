#include "classes/headers/object.h"

Object::Object()
{

}

//======================================================================
//=========================== OPERATORS ================================
//======================================================================
QDataStream& operator <<( QDataStream& stream, const Object& object )
{
    return stream << object.id << object.name << object.type << object.material <<
                     object.height << object.width << object.depth << object.weight <<
                     object.diameter << object.civilisation << object.location <<
                     object.locationX << object.locationY << object.altitude <<
                     object.description;
}

QDataStream& operator >>( QDataStream& stream, Object& object )
{
    return stream >> object.id >> object.name >> object.type >> object.material >>
                     object.height >> object.width >> object.depth >> object.weight >>
                     object.diameter >> object.civilisation >> object.location >>
                     object.locationX >> object.locationY >> object.altitude >>
                     object.description;
}


//======================================================================
//====================== GETTERS AND SETTERS ===========================
//======================================================================

int Object::getId() const
{
    return id;
}

void Object::setId(int value)
{
    id = value;
}

QString Object::getName() const
{
    return name;
}

void Object::setName(const QString &value)
{
    name = value;
}

int Object::getType() const
{
    return type;
}

void Object::setType(int value)
{
    type = value;
}

QString Object::getMaterial() const
{
    return material;
}

void Object::setMaterial(const QString &value)
{
    material = value;
}

double Object::getHeight() const
{
    return height;
}

void Object::setHeight(double value)
{
    height = value;
}

double Object::getWidth() const
{
    return width;
}

void Object::setWidth(double value)
{
    width = value;
}

double Object::getDepth() const
{
    return depth;
}

void Object::setDepth(double value)
{
    depth = value;
}

double Object::getWeight() const
{
    return weight;
}

void Object::setWeight(double value)
{
    weight = value;
}

double Object::getDiameter() const
{
    return diameter;
}

void Object::setDiameter(double value)
{
    diameter = value;
}

QString Object::getCivilisation() const
{
    return civilisation;
}

void Object::setCivilisation(const QString &value)
{
    civilisation = value;
}

QString Object::getLocation() const
{
    return location;
}

void Object::setLocation(const QString &value)
{
    location = value;
}

double Object::getLocationX() const
{
    return locationX;
}

void Object::setLocationX(double value)
{
    locationX = value;
}

double Object::getLocationY() const
{
    return locationY;
}

void Object::setLocationY(double value)
{
    locationY = value;
}

double Object::getAltitude() const
{
    return altitude;
}

void Object::setAltitude(double value)
{
    altitude = value;
}

QString Object::getDescription() const
{
    return description;
}

void Object::setDescription(const QString &value)
{
    description = value;
}
