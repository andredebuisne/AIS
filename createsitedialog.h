#ifndef CREATESITEDIALOG_H
#define CREATESITEDIALOG_H
#include <QDialog>
#include <QtWidgets>


class createSiteDialog : public QDialog
{
    Q_OBJECT

signals:
    void openSite(QString);
public slots:
    void createSite();
    void getFilePath();
public:
    createSiteDialog(QWidget *parent);
    QGroupBox* createLocationGroupBox();
    QGroupBox* createDateGroupBox();

private:
    //All of the form fields, to access them throughout the class
    QLineEdit *siteName;
    QLineEdit *siteDirector;
    QLineEdit *siteCity;
    QLineEdit *siteCountry;
    QComboBox *siteExcavationType;
    QDoubleSpinBox *siteLocationX;
    QDoubleSpinBox *siteLocationY;
    QDoubleSpinBox *siteAltitude;
    QLineEdit *siteAncientCity;
    QLineEdit *siteAncientRegion;
    QSpinBox *siteNumDiggers;
    QDateTimeEdit *siteDigBegin;
    QDateTimeEdit *siteDigEnd;
    QString filePath;

};

#endif // CREATESITEDIALOG_H
