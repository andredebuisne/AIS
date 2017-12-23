#include "views/CRUD/headers/createsitedialog.h"
#include "classes/headers/site.h"
#include <QtWidgets>
/*This class creates the layout for the site creation dialog
*Created by @Andre on 23-11-17
* Fields are:
    * name --> DONE
    * director --> DONE
    * city --> DONE
    * country --> DONE
    * dateBegin --> DONE
    * dateEnd --DONE
    * location(X, Y, Altitude) --> DONE
    * excavation type --> DONE
    * number of diggers --> DONE
*/

createSiteDialog::createSiteDialog(QWidget *parent) : QDialog(parent)
{
    QGridLayout *layout = new QGridLayout;

    //Create form header
    QLabel *formHeader = new QLabel(tr("<h3> <img src=':/icons/new-svg' style='vertical-align: middle'> Création de site  </h3>"));

    //Create all the input labels. Add * if the input is required
    QLabel *siteNameLabel = new QLabel(tr("Nom du site *"));
    QLabel *siteDirectorLabel = new QLabel(tr("Nom du directeur"));
    QLabel *siteCityLabel = new QLabel(tr("Ville *"));
    QLabel *siteCountryLabel = new QLabel(tr("Pays *"));
    QLabel *siteExcavationTypeLabel = new QLabel(tr("Type de fouille *"));
    QLabel *siteAncientCityLabel = new QLabel(tr("Nom ancien"));
    QLabel *siteAncientRegionLabel = new QLabel(tr("Région ancienne"));
    QLabel *siteNumDiggersLabel = new QLabel(tr("Nombre de fouilleurs"));

    //Create the location group box
    QGroupBox *locationGroup = createLocationGroupBox();
    //Create the date group box
    QGroupBox *dateGroup = createDateGroupBox();

    //Create all the input fields
    siteName = new QLineEdit;
    siteDirector = new QLineEdit;
    siteCity = new QLineEdit;
    siteCountry = new QLineEdit;
    siteExcavationType = new QComboBox;
    siteAncientCity = new QLineEdit;
    siteAncientRegion = new QLineEdit;
    siteNumDiggers = new QSpinBox;

    //Population the excavation type combo box
    siteExcavationType->addItem(tr("Préventive"), 0);
    siteExcavationType->addItem(tr("Programmée"), 1);
    //Add more : bâti, sous-marine, subaquatique...

    //Create action buttons
    QPushButton *createSite = new QPushButton(tr("Enregister"));
    QPushButton *cancel = new QPushButton(tr("Annuler"));
    createSite->setDefault(true);

    //Connect the buttons
    connect(cancel, SIGNAL(clicked()), this, SLOT(close()));
    connect(createSite, SIGNAL(clicked()), this, SLOT(getFilePath()));

    //Row 0 : header
    layout->addWidget(formHeader, 0, 0,1, 4, Qt::AlignCenter); //Header
    //Form : Row 1
    layout->addWidget(siteNameLabel, 1, 0);
    layout->addWidget(siteName, 1, 1);
    layout->addWidget(siteExcavationTypeLabel, 1, 2);
    layout->addWidget(siteExcavationType, 1, 3);
    //Row 2
    layout->addWidget(siteCityLabel, 2, 0);
    layout->addWidget(siteCity, 2, 1);
    layout->addWidget(siteCountryLabel, 2, 2);
    layout->addWidget(siteCountry , 2, 3);
    //Row 3
    layout->addWidget(siteAncientCityLabel, 3, 0);
    layout->addWidget(siteAncientCity, 3, 1);
    layout->addWidget(siteAncientRegionLabel, 3, 2);
    layout->addWidget(siteAncientRegion, 3, 3);
    //Row 4
    layout->addWidget(siteDirectorLabel, 4, 0);
    layout->addWidget(siteDirector, 4, 1);
    layout->addWidget(siteNumDiggersLabel, 4, 2);
    layout->addWidget(siteNumDiggers, 4, 3);
    //Row 5
    layout->addWidget(locationGroup, 5, 0, 1, 2);
    layout->addWidget(dateGroup, 5, 2, 1, 2);






    //Action buttons
    layout->addWidget(cancel, 6, 2);
    layout->addWidget(createSite, 6, 3);

    this->setLayout(layout);
    this->setModal(true);


}

QGroupBox *createSiteDialog::createLocationGroupBox()
{
    QGroupBox *group = new QGroupBox();
    QGridLayout *layout = new QGridLayout;

    QLabel *siteLocationXLabel = new QLabel(tr("Latitude"));
    QLabel *siteLocationYLabel = new QLabel(tr("Longitude"));
    QLabel *siteAltitudeLabel = new QLabel (tr("Altitude (m)"));
    siteLocationX = new QDoubleSpinBox;
    siteLocationY = new QDoubleSpinBox;
    siteAltitude = new QDoubleSpinBox;

    siteLocationX->setMaximum(90.00); //Set the maximums for the longitude and latitude
    siteLocationX->setMinimum(-90.00);
    siteLocationX->setDecimals(6); //Precision of 6 decimals, the norm for longitude and latitude
    siteLocationY->setMaximum(180.00);
    siteLocationY->setMinimum(-180.00);
    siteLocationY->setDecimals(6);
    siteAltitude->setMaximum(8000.00); //Let's just assume you can't dig higher than Mt. Everest...

    layout->addWidget(siteLocationXLabel, 0, 0);
    layout->addWidget(this->siteLocationX, 0, 1);
    layout->addWidget(siteLocationYLabel, 0, 2);
    layout->addWidget(this->siteLocationY, 0, 3);
    layout->addWidget(siteAltitudeLabel, 1, 0, 1, 2);
    layout->addWidget(this->siteAltitude, 1, 2, 1, 2);

    group->setLayout(layout);
    return group;

}

QGroupBox *createSiteDialog::createDateGroupBox()
{
    QGroupBox *group = new QGroupBox();
    QGridLayout *layout = new QGridLayout;

    QLabel *siteDigBeginLabel = new QLabel(tr("Début des fouilles"));
    QLabel *siteDigEndLabel = new QLabel(tr("Fin des fouilles"));
    siteDigBegin = new QDateTimeEdit(QDate::currentDate());
    siteDigEnd = new QDateTimeEdit(QDate::currentDate());

    layout->addWidget(siteDigBeginLabel, 0, 0);
    layout->addWidget(siteDigBegin, 0, 1);
    layout->addWidget(siteDigEndLabel, 1, 0);
    layout->addWidget(siteDigEnd, 1, 1);


    group->setLayout(layout);
    return group;
}

void createSiteDialog::createSite()
{
    //Create the site
    Site site(filePath);
    site.setName(siteName->text());
    //Create location XY
    QList<double> tmpLocation;
    tmpLocation.push_back(siteLocationX->text().toDouble());
    tmpLocation.push_back(siteLocationY->text().toDouble());
    site.setLocationXY(tmpLocation);
    site.setAltitude(siteAltitude->text().toDouble());
    site.setModernCity(siteCity->text());
    site.setModernCountry(siteCountry->text());
    site.setAncientCity(siteAncientCity->text());
    site.setModernCity(siteCountry->text());
    site.setAncientRegion(siteAncientRegion->text());
    site.setDirector(siteDirector->text());
    site.setNumDiggers(siteNumDiggers->text().toInt());
    site.setDateBegin(QDate(siteDigBegin->date()));
    site.setDateEnd(QDate(siteDigEnd->date()));
    site.setExcavationType(siteExcavationType->currentData().toInt());

    //Save the site
    site.createSite();
    QString fullFilePath = QString("%1/%2/%3.archeo").arg(filePath).arg(site.getName()).arg(site.getName().toLower());
    emit openSite(fullFilePath);
    this->close();

}

void createSiteDialog::getFilePath()
{
    QString s = QFileDialog::getExistingDirectory(this, "Choisir le fichier", QDir::homePath(), QFileDialog::ShowDirsOnly| QFileDialog::DontResolveSymlinks);
    filePath = s;
    //Excpetional : create the directory here
    createSite();
}
