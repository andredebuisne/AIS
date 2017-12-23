#include "classes/headers/layer.h"

Layer::Layer()
{

}
//======================================================================
//=========================== OPERATORS ================================
//======================================================================
QDataStream& operator <<( QDataStream& stream, const Layer& layer )
{
    return stream << layer.id << layer.name << layer.type << layer.supervisor <<
                     layer.soilColor << layer.description << layer.dateDug <<
                     layer.civilisation << layer.objects;
}

QDataStream& operator >>( QDataStream& stream, Layer& layer )
{
    return stream >> layer.id >> layer.name >> layer.type >> layer.supervisor >>
                     layer.soilColor >> layer.description >> layer.dateDug >>
                     layer.civilisation >> layer.objects;
}


//======================================================================
//====================== GETTERS AND SETTERS ===========================
//======================================================================
int Layer::getId() const
{
    return id;
}

void Layer::setId(int value)
{
    id = value;
}

QString Layer::getName() const
{
    return name;
}

void Layer::setName(const QString &value)
{
    name = value;
}

int Layer::getType() const
{
    return type;
}

void Layer::setType(int value)
{
    type = value;
}

QString Layer::getSupervisor() const
{
    return supervisor;
}

void Layer::setSupervisor(const QString &value)
{
    supervisor = value;
}

QString Layer::getSoilColor() const
{
    return soilColor;
}

void Layer::setSoilColor(const QString &value)
{
    soilColor = value;
}

QString Layer::getDescription() const
{
    return description;
}

void Layer::setDescription(const QString &value)
{
    description = value;
}

QDate Layer::getDateDug() const
{
    return dateDug;
}

void Layer::setDateDug(const QDate &value)
{
    dateDug = value;
}

QString Layer::getCivilisation() const
{
    return civilisation;
}

void Layer::setCivilisation(const QString &value)
{
    civilisation = value;
}

QList<Object> Layer::getObjects() const
{
    return objects;
}

void Layer::setObjects(const QList<Object> &value)
{
    objects = value;
}
