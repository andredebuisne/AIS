#ifndef LAYER_H
#define LAYER_H
#include <QtWidgets>
#include "object.h"


class Layer
{
public:
    Layer();
    bool insertObject(Object object);
    bool removeObject(int objectId);
    bool updateObject(int objectId, Object newObject);
    //Operators
    friend QDataStream & operator <<( QDataStream& stream, const Layer& layer );
    friend QDataStream & operator >>( QDataStream& stream, Layer& layer);
    //Getters and setters
    int getId() const;
    void setId(int value);

    QString getName() const;
    void setName(const QString &value);

    int getType() const;
    void setType(int value);

    QString getSupervisor() const;
    void setSupervisor(const QString &value);

    QString getSoilColor() const;
    void setSoilColor(const QString &value);

    QString getDescription() const;
    void setDescription(const QString &value);

    QDate getDateDug() const;
    void setDateDug(const QDate &value);

    QString getCivilisation() const;
    void setCivilisation(const QString &value);

    QList<Object> getObjects() const;
    void setObjects(const QList<Object> &value);

private:
    int id;
    QString name;
    int type;
    QString supervisor;
    QString soilColor;
    QString description;
    QDate dateDug;
    QString civilisation;
    QList<Object> objects;

};

#endif // LAYER_H
