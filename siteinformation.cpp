#include "siteinformation.h"
#include "siteservice.h"

SiteInformation::SiteInformation(QWidget *parent, QString filePath) : QWidget(parent)
{
    this->filePath = filePath;
    loadSite();

    layout = new QGridLayout;
    //Labels, that never change
    QLabel *siteNameLabel = new QLabel(tr("<b>Nom du site</b>"));
    QLabel *siteExcavationTypeLabel = new QLabel(tr("<b>Type de fouilles</b>"));
    QLabel *siteModernCityLabel = new QLabel(tr("<b>Ville</b>"));
    QLabel *siteModernCountryLabel = new QLabel(tr("<b>Pays</b>"));
    QLabel *siteAncientCityLabel = new QLabel(tr("<b>Nom ancien</b>"));
    QLabel *siteAncientRegionLabel = new QLabel(tr("<b>Région ancienne</b>"));
    QLabel *siteDirectorLabel = new QLabel(tr("<b>Directeur</b>"));
    QLabel *siteNumDiggersLabel = new QLabel(tr("<b>Nombre de fouilleurs</b>"));
    QLabel *siteLocationXLabel = new QLabel(tr("<b>Latitude</b>"));
    QLabel *siteLocationYLabel = new QLabel(tr("<b>Longitude</b>"));
    QLabel *siteAltitudeLabel = new QLabel(tr("<b>Altitude</b>"));
    QLabel *siteDigStartLabel = new QLabel(tr("<b>Début des fouilles</b>"));
    QLabel *siteDigEndLabel = new QLabel(tr("<b>Fin des fouilles</b>"));

    //Initialize once the text
    siteName = new QLabel(site.getName());
    siteExcavationType = new QLabel(QString::number(site.getExcavationType()));
    siteModernCity = new QLabel(site.getModernCity());
    siteModernCountry = new QLabel(site.getModernCountry());
    siteAncientCity = new QLabel(site.getAncientCity());
    siteAncientRegion = new QLabel(site.getAncientRegion());
    siteDirector = new QLabel(site.getDirector());
    siteNumDiggers = new QLabel(QString::number(site.getNumDiggers()));
    siteLocationX = new QLabel(QString::number(site.getLocationXY().at(0)));
    siteLocationY = new QLabel(QString::number(site.getLocationXY().at(1)));
    siteAltitude = new QLabel(QString::number(site.getAltitude()));
    siteDigStart = new QLabel(site.getDateBegin().toString());
    siteDigEnd = new QLabel(site.getDateEnd().toString());
    //Edit button
    editButton = new QPushButton(tr("Modifier"));
    editButton->setIcon(QIcon(":/icons/edit"));

    connect(editButton, SIGNAL(clicked()), this, SLOT(editForm()));

    //Row 1
    layout->addWidget(siteNameLabel, 0, 0);
    layout->addWidget(siteName, 0, 1);
    layout->addWidget(siteExcavationTypeLabel, 0, 2);
    layout->addWidget(siteExcavationType, 0, 3);

    //Row 2
    layout->addWidget(siteModernCityLabel, 1, 0);
    layout->addWidget(siteModernCity, 1, 1);
    layout->addWidget(siteModernCountryLabel, 1, 2);
    layout->addWidget(siteModernCountry, 1, 3);

    //Row 3
    layout->addWidget(siteAncientCityLabel, 2, 0);
    layout->addWidget(siteAncientCity, 2, 1);
    layout->addWidget(siteAncientRegionLabel, 2, 2);
    layout->addWidget(siteAncientRegion, 2, 3);

    //Row 4
    layout->addWidget(siteDirectorLabel, 3, 0);
    layout->addWidget(siteDirector, 3, 1);
    layout->addWidget(siteNumDiggersLabel, 3, 2);
    layout->addWidget(siteNumDiggers, 3, 3);

    //Row 5
    layout->addWidget(siteLocationXLabel, 4, 0);
    layout->addWidget(siteLocationX, 4, 1);
    layout->addWidget(siteLocationYLabel, 4, 2);
    layout->addWidget(siteLocationY, 4, 3);

    //Row 6
    layout->addWidget(siteAltitudeLabel, 5, 0);
    layout->addWidget(siteAltitude, 5, 1);

    //Row 7
    layout->addWidget(siteDigStartLabel, 6, 0);
    layout->addWidget(siteDigStart, 6, 1);
    layout->addWidget(siteDigEndLabel, 6, 2);
    layout->addWidget(siteDigEnd, 6, 3);

    //Row 8
    layout->addWidget(editButton, 7, 0);

    setLayout(layout);

}

void SiteInformation::loadSite()
{
    site = Site(filePath);
    SiteService service(filePath);
    site = service.loadSite();
}


void SiteInformation::editForm()
{
    siteNameEdit = new QLineEdit;
    siteDirectorEdit = new QLineEdit;
    siteCityEdit = new QLineEdit;
    siteCountryEdit = new QLineEdit;
    siteExcavationTypeEdit = new QComboBox;
    siteAncientCityEdit = new QLineEdit;
    siteAncientRegionEdit = new QLineEdit;
    siteNumDiggersEdit = new QSpinBox;
    siteLocationXEdit = new QDoubleSpinBox;
    siteLocationYEdit = new QDoubleSpinBox;
    siteAltitudeEdit = new QDoubleSpinBox;
    siteDigBeginEdit = new QDateTimeEdit;
    siteDigEndEdit = new QDateTimeEdit;
    //Population the excavation type combo box
    siteExcavationTypeEdit->addItem(tr("Préventive"), 0);
    siteExcavationTypeEdit->addItem(tr("Programmée"), 1);
    //Add more : bâti, sous-marine, subaquatique...

    //Set all values
    siteNameEdit->setText(site.getName());
    siteDirectorEdit->setText(site.getDirector());
    siteCityEdit->setText(site.getModernCity());
    siteCountryEdit->setText(site.getModernCountry());
    int index = siteExcavationTypeEdit->findData(site.getExcavationType()); //Find the current set index
    siteExcavationTypeEdit->setCurrentIndex(index);
    siteAncientCityEdit->setText(site.getAncientCity());
    siteAncientRegionEdit->setText(site.getAncientRegion());
    siteNumDiggersEdit->setValue(site.getNumDiggers());
    siteLocationXEdit->setValue(site.getLocationXY().at(0));
    siteLocationYEdit->setValue(site.getLocationXY().at(1));
    siteAltitudeEdit->setValue(site.getAltitude());
    siteDigBeginEdit->setDate(site.getDateBegin());
    siteDigEndEdit->setDate(site.getDateEnd());

    //Replace all the widgets in the layout
    layout->replaceWidget(siteName, siteNameEdit);
    layout->replaceWidget(siteDirector, siteDirectorEdit);
    layout->replaceWidget(siteModernCity, siteCityEdit);
    layout->replaceWidget(siteModernCountry, siteCountryEdit);
    layout->replaceWidget(siteExcavationType, siteExcavationTypeEdit);
    layout->replaceWidget(siteAncientCity, siteAncientCityEdit);
    layout->replaceWidget(siteAncientRegion, siteAncientRegionEdit);
    layout->replaceWidget(siteNumDiggers, siteNumDiggersEdit);
    layout->replaceWidget(siteLocationX, siteLocationXEdit);
    layout->replaceWidget(siteLocationY, siteLocationYEdit);
    layout->replaceWidget(siteAltitude, siteAltitudeEdit);
    layout->replaceWidget(siteDigStart, siteDigBeginEdit);
    layout->replaceWidget(siteDigEnd, siteDigEndEdit);

    //Cancel and save button

    saveEdit = new QPushButton(tr("Enregistrer"));
    cancelEdit = new QPushButton(tr("Annuler"));

    connect(cancelEdit, SIGNAL(clicked()), this, SLOT(staticLayout()));

    layout->replaceWidget(editButton, cancelEdit);
    layout->addWidget(saveEdit, 7, 1);
    //Delete all the old labels
    delete siteName;
    delete siteDirector;
    delete siteModernCity;
    delete siteModernCountry;
    delete siteExcavationType;
    delete siteAncientCity;
    delete siteAncientRegion;
    delete siteNumDiggers;
    delete siteLocationX;
    delete siteLocationY;
    delete siteAltitude;
    delete siteDigStart;
    delete siteDigEnd;
    delete editButton;




}

void SiteInformation::staticLayout()
{

    siteName = new QLabel(site.getName());
    siteExcavationType = new QLabel(QString::number(site.getExcavationType()));
    siteModernCity = new QLabel(site.getModernCity());
    siteModernCountry = new QLabel(site.getModernCountry());
    siteAncientCity = new QLabel(site.getAncientCity());
    siteAncientRegion = new QLabel(site.getAncientRegion());
    siteDirector = new QLabel(site.getDirector());
    siteNumDiggers = new QLabel(QString::number(site.getNumDiggers()));
    siteLocationX = new QLabel(QString::number(site.getLocationXY().at(0)));
    siteLocationY = new QLabel(QString::number(site.getLocationXY().at(1)));
    siteAltitude = new QLabel(QString::number(site.getAltitude()));
    siteDigStart = new QLabel(site.getDateBegin().toString());
    siteDigEnd = new QLabel(site.getDateEnd().toString());

    editButton = new QPushButton(tr("Modifier"));
    editButton->setIcon(QIcon(":/icons/edit"));

    connect(editButton, SIGNAL(clicked()), this, SLOT(editForm()));


    //Replace all the widgets in the layout
    layout->replaceWidget(siteNameEdit, siteName);
    layout->replaceWidget(siteDirectorEdit, siteDirector);
    layout->replaceWidget(siteCityEdit, siteModernCity);
    layout->replaceWidget(siteCountryEdit, siteModernCountry);
    layout->replaceWidget(siteExcavationTypeEdit, siteExcavationType);
    layout->replaceWidget(siteAncientCityEdit, siteAncientCity);
    layout->replaceWidget(siteAncientRegionEdit, siteAncientRegion);
    layout->replaceWidget(siteNumDiggersEdit, siteNumDiggers);
    layout->replaceWidget(siteLocationXEdit, siteLocationX);
    layout->replaceWidget(siteLocationYEdit, siteLocationY);
    layout->replaceWidget(siteAltitudeEdit, siteAltitude);
    layout->replaceWidget(siteDigBeginEdit, siteDigStart);
    layout->replaceWidget(siteDigEndEdit, siteDigEnd);


    layout->replaceWidget(cancelEdit, editButton);
    //Delete all the old labels
    delete siteNameEdit;
    delete siteDirectorEdit;
    delete siteCityEdit;
    delete siteCountryEdit;
    delete siteExcavationTypeEdit;
    delete siteAncientCityEdit;
    delete siteAncientRegionEdit;
    delete siteNumDiggersEdit;
    delete siteLocationXEdit;
    delete siteLocationYEdit;
    delete siteAltitudeEdit;
    delete siteDigBeginEdit;
    delete siteDigEndEdit;
    delete cancelEdit;
    delete saveEdit;





}
