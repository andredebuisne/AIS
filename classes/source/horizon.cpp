#include "classes/headers/horizon.h"

Horizon::Horizon()
{
    //Set default values
    id = -1;
    name = "Undefined";
    type = -1;
    description = "Undefined";
}

//======================================================================
//=========================== OPERATORS ================================
//======================================================================
QDataStream& operator <<( QDataStream& stream, const Horizon& horizon )
{
    return stream << horizon.name << horizon.type << horizon.id << horizon.description << horizon.layerIds;
}

QDataStream& operator >>( QDataStream& stream, Horizon& horizon )
{
     return stream >> horizon.name >> horizon.type >> horizon.id >> horizon.description >> horizon.layerIds;
}

//======================================================================
//====================== GETTERS AND SETTERS ===========================
//======================================================================

int Horizon::getId() const
{
    return id;
}

void Horizon::setId(int value)
{
    id = value;
}

QString Horizon::getName() const
{
    return name;
}

void Horizon::setName(const QString &value)
{
    name = value;
}

int Horizon::getType() const
{
    return type;
}

void Horizon::setType(int value)
{
    type = value;
}

QString Horizon::getDescription() const
{
    return description;
}

void Horizon::setDescription(const QString &value)
{
    description = value;
}

QList<int> Horizon::getLayerIds() const
{
    return layerIds;
}

void Horizon::setLayerIds(const QList<int> &value)
{
    layerIds = value;
}
