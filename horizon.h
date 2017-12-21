#ifndef HORIZON_H
#define HORIZON_H
#include <QtWidgets>
#include "layer.h"


class Horizon
{
public:
    Horizon();
    bool insertLayer(Layer layer);
    bool removeLayer(int layerId);
    bool updateLayer(int layerId, Layer newLayer);

    //Operators
    friend QDataStream & operator <<( QDataStream& stream, const Horizon& horizon );
    friend QDataStream & operator >>( QDataStream& stream, Horizon& horizon );


    //Getters and setters
    int getId() const;
    void setId(int value);

    QString getName() const;
    void setName(const QString &value);

    int getType() const;
    void setType(int value);

    QString getDescription() const;
    void setDescription(const QString &value);

    QList<int> getLayerIds() const;
    void setLayerIds(const QList<int> &value);

private:
    int id;
    QString name;
    int type;
    QString description;
    QList<int> layerIds;
};

#endif // HORIZON_H
