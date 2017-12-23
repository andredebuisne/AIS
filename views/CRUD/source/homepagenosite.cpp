#include "views/CRUD/headers/homepagenosite.h"

#include <QtWidgets>
#include <QSettings>

/*This class creates the layout for the main window when no site is loaded
 *Created by @Andre on 22-11-2017
 *
 */

HomePageNoSite::HomePageNoSite(QWidget *parent) : QWidget(parent)
{
    parent->setWindowTitle("A.I.S");
    QSettings settings; //Load the settings to get the list of recent files
    QGridLayout *layout = new QGridLayout;
    QLabel *welcomeMessage = new QLabel(tr("<h3> A.I.S : Votre Systeme d'Information Archeologique</h3>"));

    QLabel *recentFileViewHeader = new QLabel(tr("<u>Fichiers recents: </u>"));

    QListWidget *recentFileView = new QListWidget; //List of the five most recent files opened by the user
    recentFileView->setAttribute(Qt::WA_MacShowFocusRect, false); //Remove blue outline on mac
    recentFileView->setStyleSheet("background-color: transparent; border: 1px solid darkgrey");
    QStringList recentFileList = settings.value("recentFilesList").toStringList();

    for(int i = 0; i < recentFileList.size(); i++){
        QListWidgetItem *newItem = new QListWidgetItem;
        newItem->setText(recentFileList.at(i));
        newItem->setIcon(QIcon(":/icons/new-svg"));
        recentFileView->addItem(newItem);
    }

    //Connect the recentFileList to the main window
    connect(recentFileView, SIGNAL(itemDoubleClicked(QListWidgetItem*)), parent, SLOT(openRecentSite(QListWidgetItem*)));


    QPushButton *createSiteButton = new QPushButton(tr("Creer un site")); //Main buttons
    createSiteButton->setIcon(QIcon(":/icons/new-svg"));
    createSiteButton->setStyleSheet ("text-align: left; padding: 10px; vertical-align: middle"); //Align the text on the left
    QPushButton *openSiteButton = new QPushButton(tr("Ouvrir un site"));
    openSiteButton->setIcon(QIcon(":/icons/open-svg"));
    openSiteButton->setStyleSheet ("text-align: left; padding: 10px");
    QPushButton *helpButton = new QPushButton(tr("Aide"));
    helpButton->setIcon(QIcon(":/icons/help"));
    helpButton->setStyleSheet ("text-align: left; padding: 10px");
    QPushButton *instructionsButton = new QPushButton(tr("Mode d'emploi"));
    instructionsButton->setIcon(QIcon(":/icons/instructions"));
    instructionsButton->setStyleSheet ("text-align: left; padding: 10px");

    //Connect the buttons to the main window
    connect(createSiteButton, SIGNAL(clicked()), parent, SLOT(createSite()));
    connect(openSiteButton, SIGNAL(clicked()), parent, SLOT(openSite()));

    layout->addWidget(welcomeMessage, 0, 0, 1, 2, Qt::AlignCenter);
    layout->addWidget(recentFileViewHeader,1,0);
    layout->addWidget(recentFileView, 2, 0, 3, 1);
    layout->addWidget(createSiteButton, 1, 1);
    layout->addWidget(openSiteButton, 2, 1);
    layout->addWidget(helpButton, 3, 1);
    layout->addWidget(instructionsButton, 4, 1);
    this->setLayout(layout);
    //parent->setFixedSize(500, 300);

}
