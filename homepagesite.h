#ifndef HOMEPAGESITE_H
#define HOMEPAGESITE_H
#include "site.h"
#include "createhorizonwidget.h"
#include "createlayerwidget.h"
#include "createobjectwidget.h"
#include "viewhorizonwidget.h"
#include "viewlayerwidget.h"
#include "viewobjectwidget.h"
#include <QWidget>

class HomePageSite : public QWidget
{
    Q_OBJECT
public:
    //Functions
    explicit HomePageSite(QMainWindow *parent = nullptr, QString filePath = nullptr);
    QWidget *createCRUDPages(bool defaultCL, int horizonId = -2);
    QWidget *createStatisticsPages();
    QStackedWidget *createGlobalPages();
    QWidget *createMapPages();
    QTreeWidget *createSiteTree();
    void createLayout();

private:
    //Members
    QString filePath;
    QSplitter *splitter; //Create a splitter to contain all, allow the resize of the tree, with a handle
    QStackedWidget *crudPages;
    QStackedWidget *globalPages;
    QWidget *crudWidget;
    QPushButton *createHorizonButton;
    QPushButton *createLayerButton;
    QPushButton *createObjectButton;
    QTreeWidget *siteTree;
    QGridLayout *centralLayout;
    int currentPageIndex; //For the crud pages
    int currentDashboardIndex; //Index for the global pages
    CreateHorizonWidget *ch;
    CreateLayerWidget *cl;
    CreateObjectWidget *co;
    ViewHorizonWidget *vh;
    ViewLayerWidget *vl;
    ViewObjectWidget *vo;
    bool defaultCL; //Do we use the default page or one with a predefined horizon id
    int horizonId;
    bool defaultCO;
    int layerId;
signals:

public slots:
    void openCH();//open create horizon page
    void openCL();//create layer page
    void openCO();//create object page
    void openCL(int horizonId); //Create layer page, with horizon id predefined
    void openCO(int layerId); //Create object page, with layer id predefined
    void openVH(int horizonId); //Open the view horizon widget
    void openVL(int layerId); //Open the view layer widget
    void openVO(int objectId); //Open the view object widget
    void updateView(); //Create the side tree
    void openDashboard(); //Open the view site widget, the "dashboard"
    void openStatistics(); //Open the statistics dashboard
    void openMap(); //Open the map dashboard
};

#endif // HOMEPAGESITE_H
