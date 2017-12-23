#include "classes/headers/relationship.h"

Relationship::Relationship()
{

}

Relationship::Relationship(int layerId)
{
    this->layerId = layerId;
}
//======================================================================
//=========================== OPERATORS ================================
//======================================================================
QDataStream& operator <<( QDataStream& stream, const Relationship& relationship )
{
    return stream << relationship.layerId << relationship.earlierThan << relationship.laterThan <<
                     relationship.contemporaryTo << relationship.equalTo;
}

QDataStream& operator >>( QDataStream& stream, Relationship& relationship )
{
     return stream >> relationship.layerId >> relationship.earlierThan >> relationship.laterThan >>
                      relationship.contemporaryTo >> relationship.equalTo;
}


//======================================================================
//====================== GETTERS AND SETTERS ===========================
//======================================================================

int Relationship::getEarlierThan() const
{
    return earlierThan;
}

void Relationship::setEarlierThan(int value)
{
    earlierThan = value;
}

int Relationship::getLaterThan() const
{
    return laterThan;
}

void Relationship::setLaterThan(int value)
{
    laterThan = value;
}

int Relationship::getContemporaryTo() const
{
    return contemporaryTo;
}

void Relationship::setContemporaryTo(int value)
{
    contemporaryTo = value;
}

int Relationship::getEqualTo() const
{
    return equalTo;
}

void Relationship::setEqualTo(int value)
{
    equalTo = value;
}

int Relationship::getLayerId() const
{
    return layerId;
}

void Relationship::setLayerId(int value)
{
    layerId = value;
}
