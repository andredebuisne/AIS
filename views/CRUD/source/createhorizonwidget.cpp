#include "views/CRUD/headers/createhorizonwidget.h"
#include <QtWidgets>
#include "classes/headers/horizon.h"
#include "services/headers/siteservice.h"
#include "errors/headers/fileerror.h"

CreateHorizonWidget::CreateHorizonWidget(QWidget *parent, QString filePath) : QWidget(parent)
{
    QGridLayout *layout = new QGridLayout;
    formIsValid = false;
    this->filePath = filePath;
    this->parentWidget = parent;
    //Create all the labels
    QLabel *header = new QLabel(tr("Créer un horizon")); //Add icons through HTML
    QLabel *horizonIdLabel = new QLabel(tr("Numéro * "));
    QLabel *horizonNameLabel = new QLabel(tr("Nom * ")); //If name is empty, name = "Horizon {id}"
    QLabel *horizonTypeLabel = new QLabel(tr("Type * "));
    QLabel *horizonDescriptionLabel = new QLabel(tr("Description"));
    //Create all input fields
    horizonId = new QSpinBox;
    horizonName = new QLineEdit;
    horizonType = new QComboBox;
    horizonDescription = new QLineEdit;
    //Create buttons
    createHorizonButton = new QPushButton(tr("Créer"));
    QPushButton *cancelButton = new QPushButton(tr("Annuler"));
    createHorizonButton->setDefault(true);
    createHorizonButton->setEnabled(formIsValid);

    //Connect the buttons
    connect(createHorizonButton, SIGNAL(clicked()), this, SLOT(createHorizon()));

    //Check the required inputs are filled in
    connect(horizonName, SIGNAL(textChanged(QString)), this, SLOT(checkFormValidity()));
    connect(horizonId, SIGNAL(valueChanged(int)), this, SLOT(checkFormValidity()));

    layout->addWidget(header, 0, 0, 1, 2);
    layout->addWidget(horizonIdLabel, 1, 0);
    layout->addWidget(horizonId, 1, 1);
    layout->addWidget(horizonNameLabel, 2, 0);
    layout->addWidget(horizonName, 2, 1);
    layout->addWidget(horizonTypeLabel, 3, 0);
    layout->addWidget(horizonType, 3, 1);
    layout->addWidget(horizonDescriptionLabel, 4, 0);
    layout->addWidget(horizonDescription, 4, 1);
    layout->addWidget(cancelButton, 5, 0);
    layout->addWidget(createHorizonButton, 5, 1);
    layout->setAlignment(Qt::AlignTop);

    this->setLayout(layout);

}

void CreateHorizonWidget::checkFormValidity()
{
//    if(input.isEmpty()){
//        formIsValid = false; //If one of the required fields is empty, then the form is not valid
//    }else{
        bool id = horizonId->text().isEmpty();
        bool name = horizonName->text().isEmpty();

        formIsValid = !(id || name);
        createHorizonButton->setEnabled(formIsValid);
//    }

}

void CreateHorizonWidget::createHorizon()
{
    bool isError = false;
    Horizon horizon;
    horizon.setId(horizonId->value());
    horizon.setName(horizonName->text());
    //horizon.setType(horizonType->currentText().toInt());
    horizon.setDescription(horizonDescription->text());
    SiteService service(filePath);
    try{
        service.insertHorizon(horizon);
    }catch(FileError *error){
        QMessageBox::warning(this, "", error->getMessage());
        isError = true;
    }catch(...){
        QMessageBox::warning(this, "", tr("Erreur inconnue"));
    }
    if(!isError){
        emit updateView();
    }

}

void CreateHorizonWidget::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return){
        if(formIsValid){//Make sure form is valid
            createHorizon();
        }
    }
}

