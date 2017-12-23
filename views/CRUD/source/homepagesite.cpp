#include "views/CRUD/headers/homepagesite.h"
#include "services/headers/siteservice.h"
#include "services/headers/horizonservice.h"
#include "views/toolbar/headers/testcontrolswidget.h"
#include "views/tree/headers/sitetree.h"
#include "views/toolbar/headers/lefttoolbar.h"
#include "views/toolbar/headers/toptoolbar.h"
#include "views/CRUD/headers/viewsitewidget.h"
#include "views/statistics/headers/statisticswidgets.h"
#include "views/harrisMatrix/headers/harrismatrixwidget.h"
#include "views/map/headers/mapwidget.h"
#include <QtWidgets>
/*This class creates the main layout when a site is loaded*/

HomePageSite::HomePageSite(QMainWindow *parent, QString filePath) : QWidget(parent)
{
    currentPageIndex = 0;
    defaultCL = true;
    defaultCO = true;
    horizonId = -2;
    layerId = -2;
    this->filePath = filePath;
    SiteService service(filePath);
    Site site(filePath); //User a pointer here?
    site = service.loadSite();
    parent->setWindowTitle(site.getName());

    //Create the left menu
    this->createLayout();
    parent->setMinimumHeight(700);
    parent->setMinimumWidth(950);
    //Create top toolbar : Home (Dashboard, Layers, Horizons, Objects, Statistics, Map
    QToolBar *topToolBar = new TopToolBar(this);
    parent->addToolBar(topToolBar);
    //Create left toolbar : create horizon, layer, object
    QToolBar *leftToolBar = new LeftToolBar(this);
    parent->addToolBar(Qt::LeftToolBarArea,  leftToolBar);

}

void HomePageSite::createLayout()
{
    splitter = new QSplitter;
    splitter->setChildrenCollapsible(false);
    splitter->setHandleWidth(0);
    centralLayout = new QGridLayout;
    centralLayout->setMargin(0);

    siteTree = createSiteTree();

    globalPages = createGlobalPages();


    //centralLayout->addWidget(siteTree, 0, 0, 3, 1);
    //centralLayout->addWidget(globalPages, 0, 1, 3, 3);

    splitter->addWidget(siteTree);
    splitter->addWidget(globalPages);

    centralLayout->addWidget(splitter);

    this->setLayout(centralLayout);
}



QWidget *HomePageSite::createCRUDPages(bool defaultCL, int horizonId)
{

    QWidget *widget = new QWidget;
    QGridLayout *layout = new QGridLayout;
    //Create the right menu

    //Create the stacked pages
    crudPages = new QStackedWidget;
    ch = new CreateHorizonWidget(this, filePath);
    if(defaultCL){
        cl = new CreateLayerWidget(this, filePath);
    }else{
        cl = new CreateLayerWidget(this, filePath, horizonId);
    }
    if(defaultCO){
        co = new CreateObjectWidget(this, filePath);
    }else{
        co = new CreateObjectWidget(this, filePath, layerId);
    }
    vh = new ViewHorizonWidget(this, filePath, -2); //Create a default page, load nothing when = -2, more efficient
    vl = new ViewLayerWidget(this, filePath, -2);
    vo = new ViewObjectWidget(this, filePath, -2);

    connect(ch, SIGNAL(updateView()), this, SLOT(updateView()));
    connect(cl, SIGNAL(updateView()), this, SLOT(updateView()));
    connect(co, SIGNAL(updateView()), this, SLOT(updateView()));
    connect(vh, SIGNAL(updateView()), this, SLOT(updateView()));
    connect(vl, SIGNAL(updateView()), this, SLOT(updateView()));
    crudPages->addWidget(ch);//0 --> index
    crudPages->addWidget(cl);//1
    crudPages->addWidget(co);//2
    crudPages->addWidget(vh);//3
    crudPages->addWidget(vl);//4
    crudPages->addWidget(vo);//5
    crudPages->setCurrentIndex(currentPageIndex); //We stay on the same page after saving
    /*Add:
     * CreateHorizon DONE
     * CreateLayer DONE
     * CreateObject DONE
     * ViewSite
     * ViewHorizon
     * ViewLayer
     * ViewObject
     * TestButtons
     * Harris Diagram
     */
    layout->addWidget(crudPages, 0, 0, 2, 1);
    layout->addWidget(new TestControlsWidget(this), 0, 1, Qt::AlignTop);
    HarrisMatrixWidget *harris = new HarrisMatrixWidget(this, filePath);
    connect(harris, SIGNAL(openVL(int)), this, SLOT(openVL(int)));
//    harris->setMaximumWidth(200);
    harris->show();
    layout->addWidget(harris, 1, 1, Qt::AlignHCenter);

    widget->setLayout(layout);
    return widget;




}

QWidget *HomePageSite::createStatisticsPages()
{
    QGridLayout *layout = new QGridLayout;
    /*Add:
     * Test 1
     * Test 2
     * Test 3
     * Test 4
     * Test 5
     * Test 6
     * LatestTestViews
     */
}

QStackedWidget *HomePageSite::createGlobalPages()
{
    QStackedWidget *gp = new QStackedWidget;
    crudWidget = createCRUDPages(defaultCL, horizonId);
    gp->addWidget(crudWidget);
    gp->addWidget(new ViewSiteWidget(this, filePath));
    gp->addWidget(new StatisticsWidgets(this));
    gp->addWidget(new MapWidget(this));
    gp->setCurrentIndex(currentDashboardIndex);

    return gp;
}

QTreeWidget *HomePageSite::createSiteTree() //Create the site object expolorer
{
    SiteTree *tree = new SiteTree(this, filePath);
    connect(tree, SIGNAL(openCL(int)), this, SLOT(openCL(int))); //Connection enables us to open the create layer page with a defined horizon id
    connect(tree, SIGNAL(openCO(int)), this, SLOT(openCO(int)));
    connect(tree, SIGNAL(openVH(int)), this, SLOT(openVH(int)));
    connect(tree, SIGNAL(openVL(int)), this, SLOT(openVL(int)));
    connect(tree, SIGNAL(openVO(int)), this, SLOT(openVO(int)));
    return tree;
}


void HomePageSite::openCH()
{
    globalPages->setCurrentIndex(0); //Go back to the crudpages
    crudPages->setCurrentIndex(0);
    currentPageIndex = 0;
    currentDashboardIndex = 0;
}

void HomePageSite::openCL()
{
    globalPages->setCurrentIndex(0); //Go back to the crudpages
    crudPages->removeWidget(cl);
    cl = new CreateLayerWidget(this, filePath);
    connect(cl, SIGNAL(updateView()), this, SLOT(updateView()));
    crudPages->insertWidget(1, cl); //Custom update a widget
    crudPages->setCurrentIndex(1);
    currentPageIndex = 1;
    currentDashboardIndex = 0;
    defaultCL = true;
}

void HomePageSite::openCO()
{
    globalPages->setCurrentIndex(0); //Go back to the crudpages
    crudPages->removeWidget(co);
    co = new CreateObjectWidget(this, filePath);
    connect(co, SIGNAL(updateView()), this, SLOT(updateView()));
    crudPages->insertWidget(2, co);
    crudPages->setCurrentIndex(2);
    currentPageIndex = 2;
    currentDashboardIndex = 0;
    defaultCO = true;
}

void HomePageSite::openCL(int horizonId)
{
    globalPages->setCurrentIndex(0); //Go back to the crudpages
    crudPages->removeWidget(cl);
    cl = new CreateLayerWidget(this, filePath, horizonId);
    connect(cl, SIGNAL(updateView()), this, SLOT(updateView()));
    crudPages->insertWidget(1, cl); //Custom update a widget
    crudPages->setCurrentIndex(1);
    currentPageIndex = 1;
    currentDashboardIndex = 0;
    defaultCL = false;
    this->horizonId = horizonId;
}

void HomePageSite::openCO(int layerId)
{
    globalPages->setCurrentIndex(0);
    crudPages->removeWidget(co);
    co = new CreateObjectWidget(this, filePath, layerId);
    connect(co, SIGNAL(updateView()), this, SLOT(updateView()));
    crudPages->insertWidget(2, co);
    crudPages->setCurrentIndex(2);
    currentPageIndex = 2;
    currentDashboardIndex = 0;
    defaultCO = false;
    this->layerId = layerId;
}

void HomePageSite::openVH(int horizonIdForView)
{
    globalPages->setCurrentIndex(0);
    crudPages->removeWidget(vh);
    vh = new ViewHorizonWidget(this, filePath, horizonIdForView);
    connect(vh, SIGNAL(updateView()), this, SLOT(updateView()));
    crudPages->insertWidget(3, vh);
    crudPages->setCurrentIndex(3);

    currentPageIndex = 3;
    currentDashboardIndex = 0;

    //connect for update view, when the user updates the tree
    //When update, how to remember where we were?
}

void HomePageSite::openVL(int layerId)
{
    globalPages->setCurrentIndex(0);
    crudPages->removeWidget(vl);
    vl = new ViewLayerWidget(this, filePath, layerId);
    connect(vl, SIGNAL(updateView()), this, SLOT(updateView()));
    crudPages->insertWidget(4, vl);
    crudPages->setCurrentIndex(4);

    currentPageIndex = 4;
    currentDashboardIndex = 0;
}

void HomePageSite::openVO(int objectId)
{
    globalPages->setCurrentIndex(0);
    crudPages->removeWidget(vo);
    vo = new ViewObjectWidget(this, filePath, objectId);
    crudPages->insertWidget(5, vo);
    crudPages->setCurrentIndex(5);

    currentPageIndex = 5;
    currentDashboardIndex = 0;
}


void HomePageSite::updateView()
{
    //Update tree view...
    QTreeWidget *newSiteTree = createSiteTree();
    QStackedWidget *newGlobalPages = createGlobalPages();
    QSplitter *newSplitter = new QSplitter;
    newSplitter->setChildrenCollapsible(false);
    newSplitter->setHandleWidth(0);
    newSplitter->addWidget(newSiteTree);
    newSplitter->addWidget(newGlobalPages);
    centralLayout->replaceWidget(splitter, newSplitter);
    delete siteTree;
    delete globalPages;
    delete splitter;
    siteTree = new QTreeWidget;
    globalPages = new QStackedWidget;
    splitter = new QSplitter;
    siteTree = newSiteTree;
    globalPages = newGlobalPages;
    splitter = newSplitter;
}

void HomePageSite::openDashboard()
{
    globalPages->setCurrentIndex(1); //Go to the dashboard
}

void HomePageSite::openStatistics()
{
    globalPages->setCurrentIndex(2); //Go to the statistics home page
}

void HomePageSite::openMap()
{
    globalPages->setCurrentIndex(3); //Go to the maps home page
}



