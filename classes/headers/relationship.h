#ifndef RELATIONSHIP_H
#define RELATIONSHIP_H

#include <QtWidgets>
class Relationship
{
public:
    Relationship();
    Relationship(int layerId);
    //Operators
    friend QDataStream & operator <<( QDataStream& stream, const Relationship& relationship );
    friend QDataStream & operator >>( QDataStream& stream, Relationship& relationship );

    //Getters and setters
    int getEarlierThan() const;
    void setEarlierThan(int value);

    int getLaterThan() const;
    void setLaterThan(int value);

    int getContemporaryTo() const;
    void setContemporaryTo(int value);

    int getEqualTo() const;
    void setEqualTo(int value);

    int getLayerId() const;
    void setLayerId(int value);

private:
    int layerId;
    int earlierThan;
    int laterThan;
    int contemporaryTo;
    int equalTo;
};

#endif // RELATIONSHIP_H
