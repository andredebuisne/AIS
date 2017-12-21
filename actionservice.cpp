#include "actionservice.h"

ActionService::ActionService(bool siteIsLoaded)
{
    this->siteIsLoaded = siteIsLoaded;
}

QActionGroup *ActionService::createFileActions(QWidget *parent)
{
    QActionGroup *actions = new QActionGroup(parent); //Group all the actions in an QActionGroup

    //Define the actions --> we need to access them throughout the application, they are thus placed here
    QAction *createSiteAction = new QAction(tr("Creer un site"), parent);
    QAction *openSiteAction = new QAction(tr("Ouvrir un site"), parent);
    QAction *closeSiteAction = new QAction(tr("Fermer le site"), parent);

    //Connect the actions to functions in the main window
    connect(createSiteAction, SIGNAL(triggered()), parent, SLOT(createSite()));
    connect(openSiteAction, SIGNAL(triggered()), parent, SLOT(openSite()));
    connect(closeSiteAction, SIGNAL(triggered()), parent, SLOT(closeSite()));

    createSiteAction->setToolTip(tr("Creer un nouveau fichier .archeo"));
    createSiteAction->setShortcut(QKeySequence::New);
    createSiteAction->setIcon(QIcon(":/icons/new-svg"));
    openSiteAction->setToolTip(tr("Ouvrir un fichier .archeo"));
    openSiteAction->setShortcut(QKeySequence::Open);
    openSiteAction->setIcon(QIcon(":/icons/open-svg"));
    closeSiteAction->setToolTip(tr("Fermer le fichier en cours de traitement"));


    actions->addAction(createSiteAction);
    actions->addAction(openSiteAction);
    if (siteIsLoaded) actions->addAction(closeSiteAction);

    return actions;
}

QActionGroup *ActionService::createRecentFilesActions(QWidget *parent){
    QSettings settings; //Load the settings to access the most recent files

    QActionGroup *actions = new QActionGroup(parent); //Group all the recent files (max 5) in a set of actions to open them

    QStringList recentFilesList = settings.value("recentFilesList").toStringList();

    for(int i = 0; i < recentFilesList.size(); i++){ //TEMPORARY : load from QSettings
       QAction *newAction = new QAction(recentFilesList.at(i), parent);
       newAction->setToolTip(tr("Ouvrir un fichier utilise recemment"));

       //Connect the action to the openRecentSite() function in main window
       connect(newAction, SIGNAL(triggered()), parent, SLOT(openRecentSite()));
       actions->addAction(newAction);
    }
    return actions;
}

QActionGroup *ActionService::createSettingsActions(QWidget *parent)
{
    QActionGroup *actions = new QActionGroup(parent);

    QAction *generalSettings = new QAction(tr("Général"), parent); //Open the general settings for the app (settingsdialog.cpp)
    generalSettings->setToolTip(tr("Réglages général de l'application"));

    //Connect to the mainwindow
    connect(generalSettings, SIGNAL(triggered()), parent, SLOT(openGeneralSettings()));
    actions->addAction(generalSettings);
    return actions;

}

QActionGroup *ActionService::createCRUDActions(QWidget *parent)
{
    QActionGroup *actions = new QActionGroup(parent);

    QAction *createHorizon = new QAction(tr("Nouvel horizon"), parent);
    QAction *createLayer = new QAction(tr("Nouvelle couche"), parent);
    QAction *createObject = new QAction(tr("Nouvel objet"), parent);
    createHorizon->setIcon(QIcon(":/icons/horizon"));
    createLayer->setIcon(QIcon(":/icons/layer3"));
    createObject->setIcon(QIcon(":/icons/object"));
    connect(createHorizon, SIGNAL(triggered()), parent, SLOT(openCH()));
    connect(createLayer, SIGNAL(triggered()), parent, SLOT(openCL()));
    connect(createObject, SIGNAL(triggered()), parent, SLOT(openCO()));
    actions->addAction(createHorizon);
    actions->addAction(createLayer);
    actions->addAction(createObject);
    return actions;
}

QActionGroup *ActionService::createTopToolbarActions(QWidget *parent)
{
    QActionGroup *actions = new QActionGroup(parent);

    QAction *home = new QAction(tr("Accueil"), parent);
    QAction *statistics = new QAction(tr("Statistiques"), parent);
    QAction *map = new QAction(tr("Carte"), parent);
    home->setIcon(QIcon(":/icons/home"));
    statistics->setIcon(QIcon(":/icons/statistics"));
    map->setIcon(QIcon(":/icons/map"));
    connect(home, SIGNAL(triggered()), parent, SLOT(openDashboard()));
    connect(statistics, SIGNAL(triggered()), parent, SLOT(openStatistics()));
    connect(map, SIGNAL(triggered()), parent, SLOT(openMap()));
    actions->addAction(home);
    actions->addAction(statistics);
    actions->addAction(map);
    return actions;
}
