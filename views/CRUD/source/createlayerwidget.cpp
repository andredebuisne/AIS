#include "views/CRUD/headers/createlayerwidget.h"
#include <QtWidgets>
#include "services/headers/horizonservice.h"
#include "services/headers/siteservice.h"
#include "errors/headers/fileerror.h"
#include "classes/headers/relationship.h"
CreateLayerWidget::CreateLayerWidget(QWidget *parent, QString filePath, int horizonId) : QWidget(parent)
{
    this->filePath = filePath;
    this->horizonId = horizonId;

    QGridLayout *layout = new QGridLayout;
    //Create all labels
    QLabel *headerNoHorizon = new QLabel(tr("Créer une couche US"));
    QString headerHorizonText = QString(tr("Création de couche US dans l'horizon %1")).arg(horizonId);
    QLabel *headerHorizon = new QLabel(headerHorizonText);
    QLabel *layerHorizonIdLabel = new QLabel(tr("Horizon *"));
    QLabel *layerIdLabel = new QLabel(tr("Numéro *"));
    QLabel *layerNameLabel = new QLabel(tr("Nom"));
    QLabel *layerTypeLabel = new QLabel(tr("Type *"));
    QLabel *layerSupervisorLabel = new QLabel(tr("Responsable"));
    QLabel *layerSoilColorLabel = new QLabel(tr("Couleur de la terre"));
    QLabel *layerDescriptionLabel = new QLabel(tr("Description"));
    QLabel *layerDateDugLabel = new QLabel(tr("Date de fouille *"));
    QLabel *layerCivilisationLabel = new QLabel(tr("Civilisation"));

    //Create all input fields
    layerHorizonId = new QComboBox; //Populate the combo box
    layerId = new QSpinBox;
    layerName = new QLineEdit;
    layerType = new QComboBox;
    layerSupervisor = new QLineEdit;
    layerSoilColor = new QLineEdit;
    layerDescription = new QLineEdit;
    layerDateDug = new QDateTimeEdit(QDate::currentDate());
    layerCivilisation = new QLineEdit;

    //Create the field group box
    relationshipGroup = createRelationshipGroup();

    //Create all buttons
    createLayerButton = new QPushButton(tr("Créer"));
    createLayerButton->setDefault(true);
    QPushButton *cancelButton = new QPushButton(tr("Annuler"));
    //No validity requirements here, as everything needed already has a value


    populateComboBox();
    if(horizonId != -2){  //Page was called from a horizon in the tree widget, horizon id predefined
        layout->addWidget(headerHorizon, 0, 0, 1, 2);
        QString currentText = QString(tr("Horizon %1")).arg(QString::number(horizonId));
        layerHorizonId->setDisabled(true);
        layerHorizonId->setItemText(0, currentText);
        layerHorizonId->setCurrentIndex(0);
    }else{ //User chooses the horizon
        layout->addWidget(headerNoHorizon, 0, 0, 1, 2);
    }

    layout->addWidget(layerHorizonIdLabel, 1, 0);
    layout->addWidget(layerHorizonId, 1, 1);
    layout->addWidget(layerIdLabel, 2, 0);
    layout->addWidget(layerId, 2, 1);
    layout->addWidget(layerNameLabel, 3, 0);
    layout->addWidget(layerName, 3, 1);
    layout->addWidget(layerTypeLabel, 4, 0);
    layout->addWidget(layerType, 4, 1);
    layout->addWidget(layerSupervisorLabel, 5, 0);
    layout->addWidget(layerSupervisor, 5, 1);
    layout->addWidget(layerSoilColorLabel, 6, 0);
    layout->addWidget(layerSoilColor, 6, 1);
    layout->addWidget(layerDescriptionLabel, 7, 0);
    layout->addWidget(layerDescription, 7, 1);
    layout->addWidget(layerDateDugLabel, 8, 0);
    layout->addWidget(layerDateDug, 8, 1);
    layout->addWidget(layerCivilisationLabel, 9, 0);
    layout->addWidget(layerCivilisation, 9, 1);
    layout->addWidget(relationshipGroup, 10, 0, 1, 2);
    layout->addWidget(cancelButton, 11, 0);
    layout->addWidget(createLayerButton, 11, 1);
    layout->setAlignment(Qt::AlignTop); //Align all items on top

    this->setLayout(layout);

    connect(createLayerButton, SIGNAL(clicked()), this, SLOT(createLayer()));
}

void CreateLayerWidget::populateComboBox(){
    Site site(filePath);
    SiteService service(filePath);
    site = service.loadSite();

    for(int i = 0; i < site.getHorizons().size(); i++){
        int id = site.getHorizons().at(i).getId();
        QString s;
        if(id != -1){
        s = QString(tr("Horizon %1")).arg(QString::number(id));

        }else{
        s = QString(tr("Aucun horizon"));
        }
        layerHorizonId->addItem(s, id); //Add icon
    }
}

QGroupBox *CreateLayerWidget::createRelationshipGroup()
{
    QGroupBox *group = new QGroupBox(tr("Relations"));

    QGridLayout *layout = new QGridLayout;

    //Create the labels
    QLabel *earlierThanLabel = new QLabel(tr("Plus vieux que"));
    QLabel *laterThanLabel = new QLabel(tr("Plus récent que"));
    QLabel *contemporaryToLabel = new QLabel(tr("Contemporain de"));
    QLabel *equalToLabel = new QLabel(tr("Égal à"));

    //Create the fields
    earlierThan = new QSpinBox;
    laterThan = new QSpinBox;
    contemporaryTo = new QSpinBox;
    equalTo = new QSpinBox;

    layout->addWidget(earlierThanLabel, 0, 0);
    layout->addWidget(earlierThan, 0, 1);
    layout->addWidget(laterThanLabel, 1, 0);
    layout->addWidget(laterThan, 1, 1);
    layout->addWidget(contemporaryToLabel, 2, 0);
    layout->addWidget(contemporaryTo, 2, 1);
    layout->addWidget(equalToLabel, 3, 0);
    layout->addWidget(equalTo, 3, 1);

    group->setLayout(layout);
    return group;
}

void CreateLayerWidget::createRelationship()
{
    Relationship relationship(layerId->value());

    relationship.setEarlierThan(earlierThan->value());
    relationship.setLaterThan(laterThan->value());
    relationship.setContemporaryTo(contemporaryTo->value());
    relationship.setEqualTo(equalTo->value());

    SiteService service(filePath);
    service.createRelationship(relationship);
}


void CreateLayerWidget::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return){
            createLayer();
    }
}

void CreateLayerWidget::createLayer()
{
    //Create the service
    int hId;
    bool isError = false;
    if(horizonId != -2){
        hId = horizonId;
    }else{
        hId = layerHorizonId->currentData().toInt();
    }
    HorizonService service(filePath, hId);
    //Create the layer
    Layer layer;
    layer.setId(layerId->value());
    layer.setName(layerName->text());
//    layer.setType(layerType->currentText());
    layer.setSupervisor(layerSupervisor->text());
    layer.setSoilColor(layerSoilColor->text());
    layer.setDescription(layerDescription->text());
    layer.setCivilisation(layerCivilisation->text());
    layer.setDateDug(layerDateDug->date());

    try{
        service.insertLayer(layer);
    }catch(FileError *error){
        QMessageBox::information(this, "", error->getMessage());
        isError = true;
    }catch(...){
        QMessageBox::information(this, "", tr("Erreur inconnue"));
    }
    if(!isError){
        createRelationship();
        emit updateView();
    }
}


