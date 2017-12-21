#include "viewobjectwidget.h"
#include <QtWidgets>
#include "layerservice.h"

ViewObjectWidget::ViewObjectWidget(QWidget *parent, QString filePath, int objectId) : QWidget(parent)
{
    this->filePath = filePath;
    this->objectId = objectId;
    if(objectId != -2){
        createLayout();
    }
}

void ViewObjectWidget::createLayout()
{
    QGridLayout *layout = new QGridLayout;
    LayerService service(filePath);
    Object object = service.loadObject(objectId);

    //Create labels
    QString text = QString(tr("Objet %1")).arg(object.getId());
    QLabel *title = new QLabel(text);

    QLabel *objectIdLabel = new QLabel(tr("Numéro"));
    QLabel *objectNameLabel = new QLabel(tr("Nom"));
    QLabel *objectTypeLabel = new QLabel(tr("Type"));
    QLabel *objectMaterialLabel = new QLabel(tr("Matériau"));
    QLabel *objectHeightLabel = new QLabel(tr("Hauteur"));
    QLabel *objectWidthLabel = new QLabel(tr("Largeur"));
    QLabel *objectDepthLabel = new QLabel(tr("Profondeur"));
    QLabel *objectDiameterLabel = new QLabel(tr("Diamètre"));
    QLabel *objectWeightLabel = new QLabel(tr("Poids"));
    QLabel *objectCiviliationLabel = new QLabel(tr("Civilisation"));
    QLabel *objectLocationLabel = new QLabel(tr("Localisation"));
    QLabel *objectLocationXLabel = new QLabel(tr("Latitude"));
    QLabel *objectLocationYLabel = new QLabel(tr("Longitude"));
    QLabel *objectAltitudeLabel = new QLabel(tr("Altitude"));
    QLabel *objectDescriptionLabel = new QLabel(tr("Description"));

    //Create value fields
    QLabel *objectId = new QLabel(QString::number(object.getId()));
    QLabel *objectName = new QLabel(object.getName());
    QLabel *objectType = new QLabel(QString::number(object.getType()));
    QLabel *objectMaterial = new QLabel(object.getMaterial());
    QLabel *objectHeight = new QLabel(QString::number(object.getHeight()));
    QLabel *objectWidth = new QLabel(QString::number(object.getWidth()));
    QLabel *objectDepth = new QLabel(QString::number(object.getDepth()));
    QLabel *objectDiameter = new QLabel(QString::number(object.getDiameter()));
    QLabel *objectWeight = new QLabel(QString::number(object.getWeight()));
    QLabel *objectCiviliation = new QLabel(object.getCivilisation());
    QLabel *objectLocation = new QLabel(object.getLocation());
    QLabel *objectLocationX = new QLabel(QString::number(object.getLocationX()));
    QLabel *objectLocationY = new QLabel(QString::number(object.getLocationY()));
    QLabel *objectAltitude = new QLabel(QString::number(object.getAltitude()));
    QLabel *objectDescription = new QLabel(object.getDescription());

    layout->addWidget(title, 0, 0, 1, 2);
    layout->addWidget(objectIdLabel, 1, 0);
    layout->addWidget(objectId, 1, 1);
    layout->addWidget(objectNameLabel, 2, 0);
    layout->addWidget(objectName, 2, 1);
    layout->addWidget(objectTypeLabel, 3, 0);
    layout->addWidget(objectType, 3, 1);
    layout->addWidget(objectMaterialLabel, 4, 0);
    layout->addWidget(objectMaterial, 4, 1);
    layout->addWidget(objectHeightLabel, 5, 0);
    layout->addWidget(objectHeight, 5, 1);
    layout->addWidget(objectWidthLabel, 6, 0);
    layout->addWidget(objectWidth, 6, 1);
    layout->addWidget(objectDepthLabel, 7, 0);
    layout->addWidget(objectDepth, 7, 1);
    layout->addWidget(objectWeightLabel, 8, 0);
    layout->addWidget(objectWeight, 8, 1);
    layout->addWidget(objectDiameterLabel, 9, 0);
    layout->addWidget(objectDiameter, 9, 1);
    layout->addWidget(objectCiviliationLabel, 10, 0);
    layout->addWidget(objectCiviliation, 10, 1);
    layout->addWidget(objectLocationLabel, 11, 0);
    layout->addWidget(objectLocation, 11, 1);
    layout->addWidget(objectLocationXLabel, 12, 0);
    layout->addWidget(objectLocationX, 12, 1);
    layout->addWidget(objectLocationYLabel, 13, 0);
    layout->addWidget(objectLocationY, 13, 1);
    layout->addWidget(objectAltitudeLabel, 14, 0);
    layout->addWidget(objectAltitude, 14, 1);
    layout->addWidget(objectDescriptionLabel, 15, 0);
    layout->addWidget(objectDescription, 15, 1);

    setLayout(layout);
}
