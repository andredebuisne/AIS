#include "views/CRUD/headers/viewhorizonwidget.h"
#include <QtWidgets>
#include "services/headers/siteservice.h"
#include "errors/headers/fileerror.h"

/*
*This class creates the layout for the viewing of a horizon.
* We can switch between two views:
        * static information view
        * editing view
*/
ViewHorizonWidget::ViewHorizonWidget(QWidget *parent, QString filePath, int horizonId) : QWidget(parent)
{
    this->filePath = filePath;
    this->horizonId = horizonId;
    this->numLayers = 0;
    if(horizonId != -2){
        createLayout();
    }



}

void ViewHorizonWidget::createLayout()
{
    SiteService service(filePath);
    Horizon horizon; //Use a pointer here, and everywhere else!
    horizon = service.loadHorizon(horizonId);
    numLayers = horizon.getLayerIds().size();
    layout = new QGridLayout;
    //Add labels
    QLabel *horizonIdLabel = new QLabel(tr("Numero"));
    QLabel *horizonNameLabel = new QLabel(tr("Nom"));
    QLabel *horizonTypeLabel = new QLabel(tr("Type"));
    QLabel *horizonDescriptionLabel = new QLabel(tr("Description"));
    //Add text
    horizonIdValue = new QLabel(QString::number(horizon.getId()));
    horizonName = new QLabel(horizon.getName());
    horizonType = new QLabel(QString::number(horizon.getType()));
    horizonDescription = new QLabel(horizon.getDescription());

    //Add buttons
    editButton = new QPushButton(tr("Modifier"));
    deleteButton = new QPushButton(tr("Supprimer"));
    connect(editButton, SIGNAL(clicked()), this, SLOT(openUpdateView()));
    connect(deleteButton, SIGNAL(clicked()), this, SLOT(deleteHorizon()));

    layout->addWidget(horizonIdLabel, 0, 0);
    layout->addWidget(horizonIdValue, 0, 1);
    layout->addWidget(horizonNameLabel, 1, 0);
    layout->addWidget(horizonName, 1, 1);
    layout->addWidget(horizonTypeLabel, 2, 0);
    layout->addWidget(horizonType, 2, 1);
    layout->addWidget(horizonDescriptionLabel, 3, 0);
    layout->addWidget(horizonDescription, 3, 1);
    layout->addWidget(deleteButton, 4, 0);
    layout->addWidget(editButton, 4, 1);
    layout->setAlignment(Qt::AlignTop);

    setLayout(layout);
}

void ViewHorizonWidget::openStaticView()
{
    SiteService service(filePath);
    Horizon horizon; //Use a pointer here, and everywhere else!
    horizon = service.loadHorizon(horizonId);
    horizonIdValue = new QLabel(QString::number(horizon.getId()));
    horizonName = new QLabel(horizon.getName());
    horizonType = new QLabel(QString::number(horizon.getType()));
    horizonDescription = new QLabel(horizon.getDescription());
    editButton = new QPushButton(tr("Modifier"));
    deleteButton = new QPushButton(tr("Supprimer"));
    connect(editButton, SIGNAL(clicked()), this, SLOT(openUpdateView()));

    layout->replaceWidget(horizonIdEdit, horizonIdValue);
    layout->replaceWidget(horizonNameEdit, horizonName);
    layout->replaceWidget(horizonTypeEdit, horizonType);
    layout->replaceWidget(horizonDescriptionEdit, horizonDescription);
    layout->replaceWidget(updateHorizonButton, editButton);
    layout->replaceWidget(cancel, deleteButton);
    layout->setAlignment(Qt::AlignTop);


    delete horizonIdEdit;
    delete horizonNameEdit;
    delete horizonTypeEdit;
    delete horizonDescriptionEdit;
    delete updateHorizonButton;
    delete cancel;
}


void ViewHorizonWidget::openUpdateView()
{
    //Create the form fields
    horizonIdEdit = new QSpinBox;
    horizonNameEdit = new QLineEdit;
    horizonTypeEdit = new QComboBox;
    horizonDescriptionEdit = new QLineEdit;

    horizonIdEdit->setValue(horizonIdValue->text().toInt());
    horizonNameEdit->setText(horizonName->text());
    //Find the right index to the type combo box
    //horizonTypeEdit->setCurrentIndex();
    horizonDescriptionEdit->setText(horizonDescription->text());


    updateHorizonButton = new QPushButton(tr("Enregistrer"));
    cancel = new QPushButton(tr("Annuler"));

    layout->replaceWidget(horizonIdValue, horizonIdEdit);
    layout->replaceWidget(horizonName, horizonNameEdit);
    layout->replaceWidget(horizonType, horizonTypeEdit);
    layout->replaceWidget(horizonDescription, horizonDescriptionEdit);
    layout->replaceWidget(editButton, updateHorizonButton);
    layout->replaceWidget(deleteButton, cancel);
    layout->setAlignment(Qt::AlignTop);


    connect(cancel, SIGNAL(clicked()), this, SLOT(openStaticView()));
    connect(updateHorizonButton, SIGNAL(clicked()), this, SLOT(updateHorizon()));


    delete horizonIdValue;
    delete horizonName;
    delete horizonType;
    delete horizonDescription;
    delete editButton;
    delete deleteButton;

}


void ViewHorizonWidget::updateHorizon()
{
    bool success = true;
    Horizon newHorizon;
    newHorizon.setId(horizonIdEdit->value());
    newHorizon.setName(horizonNameEdit->text());
//    newHorizon.setType(horizonTypeEdit->currentData());
    newHorizon.setDescription(horizonDescriptionEdit->text());

    SiteService service(filePath);
    try{
        service.updateHorizon(horizonId, newHorizon);
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


void ViewHorizonWidget::deleteHorizon()
{
    SiteService service(filePath);

    if(numLayers >0){
        int response = QMessageBox::question(this, "", tr("Voulez vous supprimer les couches associées?"),
                                             QMessageBox::Cancel, QMessageBox::No, QMessageBox::Yes);
        if(response == QMessageBox::Yes){
            service.removeHorizon(horizonId, true);
        }else if(response == QMessageBox::No){
            service.removeHorizon(horizonId, false);
        }
        if(response != QMessageBox::Cancel){
            emit updateView();
        }
    }else{
        service.removeHorizon(horizonId, false);
        emit updateView();
    }


}


