#ifndef SITEINFORMATION_H
#define SITEINFORMATION_H

#include <QWidget>
#include "classes/headers/site.h"

class SiteInformation : public QWidget
{
    Q_OBJECT
public:
    explicit SiteInformation(QWidget *parent = nullptr, QString filePath = nullptr);
    void loadSite();

private:
    QGridLayout *layout;
    QString filePath;
    Site site;
    QLabel *siteName;
    QLabel *siteExcavationType;
    QLabel *siteModernCity;
    QLabel *siteModernCountry;
    QLabel *siteAncientCity;
    QLabel *siteAncientRegion;
    QLabel *siteDirector;
    QLabel *siteNumDiggers;
    QLabel *siteLocationX;
    QLabel *siteLocationY;
    QLabel *siteAltitude;
    QLabel *siteDigStart;
    QLabel *siteDigEnd;
    QPushButton *editButton;

    //Form edit items
    QLineEdit *siteNameEdit;
    QLineEdit *siteDirectorEdit;
    QLineEdit *siteCityEdit;
    QLineEdit *siteCountryEdit;
    QComboBox *siteExcavationTypeEdit;
    QDoubleSpinBox *siteLocationXEdit;
    QDoubleSpinBox *siteLocationYEdit;
    QDoubleSpinBox *siteAltitudeEdit;
    QLineEdit *siteAncientCityEdit;
    QLineEdit *siteAncientRegionEdit;
    QSpinBox *siteNumDiggersEdit;
    QDateTimeEdit *siteDigBeginEdit;
    QDateTimeEdit *siteDigEndEdit;
    QPushButton *saveEdit;
    QPushButton *cancelEdit;


signals:

public slots:
    void editForm(); //Transform all labels into form edits
    void staticLayout();
};

#endif // SITEINFORMATION_H
