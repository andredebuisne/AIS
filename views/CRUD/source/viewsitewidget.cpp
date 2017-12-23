#include "views/CRUD/headers/viewsitewidget.h"
#include "services/headers/siteservice.h"
#include "views/CRUD/headers/siteinformation.h"
/*
*This view is the dashboard, the main part of the application.
* Created by Andre Debuisne on 3-12-2017
* View contains:
        * Site information --> DONE
        * Site edit --> IN PROGRESS
        * View of horizons
        * View of layers
        * View of harris matrix
        * View of the different sectors --> create and edit the different sectors
        * Create a layer sheet (create a pdf)
        * View a map

* Use tabs and stacked widgets
*/
ViewSiteWidget::ViewSiteWidget(QWidget *parent, QString filePath) : QWidget(parent)
{
    this->filePath = filePath;
    loadSite();

    //Site information
    QGridLayout *layout = new QGridLayout;
    QWidget *information = new SiteInformation(this, filePath);
    layout->addWidget(information, 0, 0);



    setLayout(layout);



}

void ViewSiteWidget::loadSite()
{
    site = Site(filePath);
    SiteService service(filePath);
    site = service.loadSite();
}


