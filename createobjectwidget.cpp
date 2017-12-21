#include "createobjectwidget.h"
#include <QtWidgets>
#include "object.h"
#include "layerservice.h"
#include "site.h"
#include "siteservice.h"
#include "fileerror.h"

CreateObjectWidget::CreateObjectWidget(QWidget *parent, QString filePath, int layerId) : QWidget(parent)
{
    this->layerId = layerId;
    this->filePath = filePath;
    this->formIsValid = false;
    QGridLayout *layout = new QGridLayout;

    //Create all labels
    QLabel *headerNoLayer = new QLabel(tr("Créer un objet"));
    QString text = QString(tr("Création d'objet dans la couche %1")).arg(QString::number(layerId));
    QLabel *headerLayer = new QLabel(text);
    QLabel *objectLayerIdLabel = new QLabel(tr("Couche US *"));
    QLabel *objectIdLabel = new QLabel(tr("Numéro *"));
    QLabel *objectNameLabel = new QLabel(tr("Nom *"));
    QLabel *objectTypeLabel = new QLabel(tr("Type *"));
    QLabel *objectMaterialLabel = new QLabel(tr("Matériau *"));
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

    //Create all form inputs
    objectLayerId = new QComboBox;
    objectId = new QSpinBox;
    objectName = new QLineEdit;
    objectType = new QComboBox;
    objectMaterial = new QLineEdit;
    objectHeight = new QDoubleSpinBox;
    objectWidth = new QDoubleSpinBox;
    objectDepth = new QDoubleSpinBox;
    objectDiameter = new QDoubleSpinBox;
    objectWeight = new QDoubleSpinBox;
    objectCiviliation = new QLineEdit;
    objectLocation = new QLineEdit; //Sector found in
    objectLocationX = new QDoubleSpinBox;
    objectLocationY = new QDoubleSpinBox;
    objectAltitude = new QDoubleSpinBox;
    objectDescription = new QLineEdit;
    //Create all buttons
    createObjectButton = new QPushButton(tr("Créer"));
    createObjectButton->setEnabled(formIsValid);
    createObjectButton->setDefault(true);
    connect(createObjectButton, SIGNAL(clicked()), this, SLOT(createObject()));
    QPushButton *cancelButton = new QPushButton(tr("Annuler"));
    //Add a reset all fields button?

    //Make sure all required fields are filled out
    connect(objectName, SIGNAL(textChanged(QString)), this, SLOT(checkFormValidity()));
    connect(objectMaterial, SIGNAL(textChanged(QString)), this, SLOT(checkFormValidity()));

    populateComboBox();

    //Set the layout
    if(layerId != -2){
        layout->addWidget(headerLayer, 0, 0, 1, 2);
        QString currentText = QString(tr("Couche %1")).arg(QString::number(layerId));
        objectLayerId->setDisabled(true);
        objectLayerId->setItemText(0, currentText);
        objectLayerId->setCurrentIndex(0);

    }else{
        layout->addWidget(headerNoLayer, 0, 0, 1, 2);
    }
    layout->addWidget(objectLayerIdLabel, 1, 0);
    layout->addWidget(objectLayerId, 1, 1);
    layout->addWidget(objectIdLabel, 2, 0);
    layout->addWidget(objectId, 2, 1);
    layout->addWidget(objectNameLabel, 3, 0);
    layout->addWidget(objectName, 3, 1);
    layout->addWidget(objectTypeLabel, 4, 0);
    layout->addWidget(objectType, 4, 1);
    layout->addWidget(objectMaterialLabel, 5, 0);
    layout->addWidget(objectMaterial, 5, 1);
    layout->addWidget(objectHeightLabel, 6, 0);
    layout->addWidget(objectHeight, 6, 1);
    layout->addWidget(objectWidthLabel, 7, 0);
    layout->addWidget(objectWidth, 7, 1);
    layout->addWidget(objectDepthLabel, 8, 0);
    layout->addWidget(objectDepth, 8, 1);
    layout->addWidget(objectWeightLabel, 9, 0);
    layout->addWidget(objectWeight, 9, 1);
    layout->addWidget(objectDiameterLabel, 10, 0);
    layout->addWidget(objectDiameter, 10, 1);
    layout->addWidget(objectCiviliationLabel, 11, 0);
    layout->addWidget(objectCiviliation, 11, 1);
    layout->addWidget(objectLocationLabel, 12, 0);
    layout->addWidget(objectLocation, 12, 1);
    layout->addWidget(objectLocationXLabel, 13, 0);
    layout->addWidget(objectLocationX, 13, 1);
    layout->addWidget(objectLocationYLabel, 14, 0);
    layout->addWidget(objectLocationY, 14, 1);
    layout->addWidget(objectAltitudeLabel, 15, 0);
    layout->addWidget(objectAltitude, 15, 1);
    layout->addWidget(objectDescriptionLabel, 16, 0);
    layout->addWidget(objectDescription, 16, 1);
    layout->addWidget(cancelButton, 17, 0);
    layout->addWidget(createObjectButton, 17, 1);
    layout->setAlignment(Qt::AlignTop);

    this->setLayout(layout);
}

void CreateObjectWidget::populateComboBox()
{
    Site site(filePath);
    SiteService service(filePath);
    site = service.loadSite();

    for(int i = 0; i < site.getHorizons().size(); i++){
        Horizon horizon = site.getHorizons().at(i);
        for(int j = 0; j <horizon.getLayerIds().size(); j++){
            int layerId = horizon.getLayerIds().at(j);
            QString text = QString(tr("Couche %1")).arg(QString::number(layerId));
            objectLayerId->addItem(text, layerId);
        }
    }
}

void CreateObjectWidget::createObject()
{
    bool isError = false;
    Object object;
    int lId;
    if(layerId != -2){
        lId = layerId;
    }else{
        lId= objectLayerId->currentData().toInt();
    }
    object.setId(objectId->value());
    object.setName(objectName->text());
    //object.setType(objectType->currentData());
    object.setMaterial(objectMaterial->text());
    object.setHeight(objectHeight->value());
    object.setWidth(objectWidth->value());
    object.setDepth(objectDepth->value());
    object.setWeight(objectWeight->value());
    object.setDiameter(objectDiameter->value());
    object.setCivilisation(objectCiviliation->text());
    object.setLocation(objectLocation->text());
    object.setLocationX(objectLocationX->value());
    object.setLocationY(objectLocationY->value());
    object.setAltitude(objectAltitude->value());
    object.setDescription(objectDescription->text());

    LayerFileService service(filePath);
    try {
        service.insertObject(lId, object);
    }catch(FileError *error){
        QMessageBox::warning(this, "", error->getMessage());
        isError = true;
    }catch(...){
        QMessageBox::warning(this, "", tr("Erreur inconnue"));
        isError = true;
    }
    if(!isError){
        emit updateView();
    }


}

void CreateObjectWidget::checkFormValidity()
{
    bool name = objectName->text().isEmpty();
    bool material = objectMaterial->text().isEmpty();

    formIsValid = !(name || material);

    createObjectButton->setEnabled(formIsValid);
}
