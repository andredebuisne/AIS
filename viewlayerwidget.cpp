#include "viewlayerwidget.h"
#include "horizonservice.h"
#include "siteservice.h"
#include "fileerror.h"

ViewLayerWidget::ViewLayerWidget(QWidget *parent, QString filePath, int layerId) : QWidget(parent)
{
    this->filePath = filePath;
    this->layerId = layerId;
    if(layerId != -2){
        createLayout();
    }
}

void ViewLayerWidget::createLayout()
{
    layout = new QGridLayout;
    HorizonService hService(filePath);
    SiteService sService(filePath);
    Layer layer = hService.loadLayer(layerId);
    Relationship relationship = sService.loadRelationship(layerId);
    objectList = layer.getObjects();

    //Create labels
    QString text = QString(tr("Couche %1")).arg(QString::number(layer.getId()));
    QLabel *title = new QLabel(text);
    QLabel *layerIdLabel = new QLabel(tr("Numéro *"));
    QLabel *layerNameLabel = new QLabel(tr("Nom"));
    QLabel *layerTypeLabel = new QLabel(tr("Type *"));
    QLabel *layerSupervisorLabel = new QLabel(tr("Responsable"));
    QLabel *layerSoilColorLabel = new QLabel(tr("Couleur de la terre"));
    QLabel *layerDescriptionLabel = new QLabel(tr("Description"));
    QLabel *layerDateDugLabel = new QLabel(tr("Date de fouille *"));
    QLabel *layerCivilisationLabel = new QLabel(tr("Civilisation"));

    //Relationship labels
    QLabel *earlierThanLabel = new QLabel(tr("Plus vieux que"));
    QLabel *laterThanLabel = new QLabel(tr("Plus récent que "));
    QLabel *equalToLabel = new QLabel(tr("Égal à"));
    QLabel *contemporaryToLabel = new QLabel(tr("Contemporain de"));

    //Create values
    layerIdValue = new QLabel(QString::number(layer.getId()));
    layerName = new QLabel(layer.getName());
    layerType = new QLabel(QString::number(layer.getType()));
    layerSupervisor = new QLabel(layer.getSupervisor());
    layerSoilColor = new QLabel(layer.getSoilColor());
    layerDescription = new QLabel(layer.getDescription());
    layerDateDug = new QLabel(layer.getDateDug().toString());
    layerCivilisation = new QLabel(layer.getCivilisation());

    //Relationship values
    earlierThan = new QLabel(QString::number(relationship.getEarlierThan()));
    laterThan = new QLabel(QString::number(relationship.getLaterThan()));
    equalTo = new QLabel(QString::number(relationship.getEqualTo()));
    contemporaryTo = new QLabel(QString::number(relationship.getContemporaryTo()));

    //Create buttons
    openUpdateViewButton = new QPushButton(tr("Modifier"));
    deleteButton = new QPushButton(tr("Supprimer"));

    //Connect the buttons
    connect(openUpdateViewButton, SIGNAL(clicked()), this, SLOT(openUpdateView()));
    connect(deleteButton, SIGNAL(clicked()), this, SLOT(deleteLayer()));

    layout->addWidget(title, 0, 0, 1, 2);
    layout->addWidget(layerIdLabel, 1, 0);
    layout->addWidget(layerIdValue, 1, 1);
    layout->addWidget(layerNameLabel, 2, 0);
    layout->addWidget(layerName, 2, 1);
    layout->addWidget(layerTypeLabel, 3, 0);
    layout->addWidget(layerType, 3, 1);
    layout->addWidget(layerSupervisorLabel, 4, 0);
    layout->addWidget(layerSupervisor, 4, 1);
    layout->addWidget(layerSoilColorLabel, 5, 0);
    layout->addWidget(layerSoilColor, 5, 1);
    layout->addWidget(layerDescriptionLabel, 6, 0);
    layout->addWidget(layerDescription, 6, 1);
    layout->addWidget(layerDateDugLabel, 7, 0);
    layout->addWidget(layerDateDug, 7, 1);
    layout->addWidget(layerCivilisationLabel, 8, 0);
    layout->addWidget(layerCivilisation, 8, 1);
    //Relationship
    layout->addWidget(laterThanLabel, 10, 0);
    layout->addWidget(laterThan, 10, 1);
    layout->addWidget(earlierThanLabel, 11, 0);
    layout->addWidget(earlierThan, 11, 1);
    layout->addWidget(equalToLabel, 12, 0);
    layout->addWidget(equalTo, 12, 1);
    layout->addWidget(contemporaryToLabel, 13, 0);
    layout->addWidget(contemporaryTo, 13, 1);

    layout->addWidget(deleteButton, 14, 0);
    layout->addWidget(openUpdateViewButton, 14, 1);

    layout->setAlignment(Qt::AlignTop);

    setLayout(layout);
}

void ViewLayerWidget::openStaticView()
{
    HorizonService service(filePath);
    Layer layer = service.loadLayer(layerId);

    layerIdValue = new QLabel(QString::number(layer.getId()));
    layerName = new QLabel(layer.getName());
    layerType = new QLabel(QString::number(layer.getType()));
    layerSupervisor = new QLabel(layer.getSupervisor());
    layerSoilColor = new QLabel(layer.getSoilColor());
    layerDescription = new QLabel(layer.getDescription());
    layerDateDug = new QLabel(layer.getDateDug().toString());
    layerCivilisation = new QLabel(layer.getCivilisation());

    openUpdateViewButton = new QPushButton(tr("Modifier"));
    deleteButton = new QPushButton(tr("Supprimer"));

    //Connect the buttons
    connect(openUpdateViewButton, SIGNAL(clicked()), this, SLOT(openUpdateView()));
    connect(deleteButton, SIGNAL(clicked()), this, SLOT(deleteLayer()));

    //Replace in the layout
    layout->replaceWidget(layerIdEdit, layerIdValue);
    layout->replaceWidget(layerNameEdit, layerName);
    layout->replaceWidget(layerTypeEdit, layerType);
    layout->replaceWidget(layerSupervisorEdit, layerSupervisor);
    layout->replaceWidget(layerSoilColorEdit, layerSoilColor);
    layout->replaceWidget(layerDescriptionEdit, layerDescription);
    layout->replaceWidget(layerDateDugEdit, layerDateDug);
    layout->replaceWidget(layerCivilisationEdit, layerCivilisation);
    layout->replaceWidget(updateLayerButton, openUpdateViewButton);
    layout->replaceWidget(openStaticViewButton, deleteButton);
    layout->setAlignment(Qt::AlignTop);

    //Delete old widgets
    delete layerIdEdit;
    delete layerNameEdit;
    delete layerTypeEdit;
    delete layerSupervisorEdit;
    delete layerSoilColorEdit;
    delete layerDescriptionEdit;
    delete layerDateDugEdit;
    delete layerCivilisationEdit;
    delete updateLayerButton;
    delete openStaticViewButton;
}

void ViewLayerWidget::openUpdateView()
{
    layerIdEdit = new QSpinBox;
    layerNameEdit = new QLineEdit;
    layerTypeEdit = new QComboBox;
    layerSupervisorEdit = new QLineEdit;
    layerSoilColorEdit = new QLineEdit;
    layerDescriptionEdit = new QLineEdit;
    layerDateDugEdit = new QDateTimeEdit();
    layerCivilisationEdit = new QLineEdit;

    updateLayerButton = new QPushButton(tr("Enregistrer"));
    openStaticViewButton = new QPushButton(tr("Annuler"));

    //Connect the buttons
    connect(updateLayerButton, SIGNAL(clicked()), this, SLOT(updateLayer()));
    connect(openStaticViewButton, SIGNAL(clicked()), this, SLOT(openStaticView()));

    //Set the values
    layerIdEdit->setValue(layerIdValue->text().toInt());
    layerNameEdit->setText(layerName->text());
    //layerTypeEdit
    layerSupervisorEdit->setText(layerSupervisor->text());
    layerSoilColorEdit->setText(layerSoilColor->text());
    layerDescriptionEdit->setText(layerDescription->text());
    layerDateDugEdit->setDate(QDate::fromString(layerDateDug->text()));
    layerCivilisationEdit->setText(layerCivilisation->text());

    //Replace in the layout
    layout->replaceWidget(layerIdValue, layerIdEdit);
    layout->replaceWidget(layerName, layerNameEdit);
    layout->replaceWidget(layerType, layerTypeEdit);
    layout->replaceWidget(layerSupervisor, layerSupervisorEdit);
    layout->replaceWidget(layerSoilColor, layerSoilColorEdit);
    layout->replaceWidget(layerDescription, layerDescriptionEdit);
    layout->replaceWidget(layerDateDug, layerDateDugEdit);
    layout->replaceWidget(layerCivilisation, layerCivilisationEdit);
    layout->replaceWidget(openUpdateViewButton, updateLayerButton);
    layout->replaceWidget(deleteButton, openStaticViewButton);
    layout->setAlignment(Qt::AlignTop);

    //Delete old widgets
    delete layerIdValue;
    delete layerName;
    delete layerType;
    delete layerSupervisor;
    delete layerSoilColor;
    delete layerDescription;
    delete layerDateDug;
    delete layerCivilisation;
    delete openUpdateViewButton;
    delete deleteButton;

}

void ViewLayerWidget::updateLayer()
{
    bool success = true;
    HorizonService hService(filePath);
    Layer newLayer;
    newLayer.setId(layerIdEdit->value());
    newLayer.setName(layerNameEdit->text());
//    newLayer.setType();
    newLayer.setSupervisor(layerSupervisorEdit->text());
    newLayer.setSoilColor(layerSoilColorEdit->text());
    newLayer.setDescription(layerDescriptionEdit->text());
    newLayer.setDateDug(layerDateDugEdit->date());
    newLayer.setCivilisation(layerCivilisationEdit->text());
    newLayer.setObjects(objectList);
    try{
        hService.updateLayer(layerId, newLayer);

    }catch(FileError *error){
        QMessageBox::warning(this, "", error->getMessage());
        success = false;
        if(error->getType() == 9){ //Layer already exists
            layerIdEdit->setValue(layerId);
        }
    }catch(...){
        QMessageBox::warning(this, "", tr("Erreur inconnue"));
        success = false;
    }

    if(success){
        emit updateView();
    }

}

void ViewLayerWidget::deleteLayer()
{
    bool success = true;
    HorizonService hService(filePath);
    try{
        hService.removeLayer(layerId);

    }catch(FileError *error){
        QMessageBox::warning(this, "", error->getMessage());
        success = false;
    }catch(...){
        QMessageBox::warning(this, "", tr("Erreur inconnue"));
        success = false;
    }

    if(success){
        emit updateView();
    }
}
