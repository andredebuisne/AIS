#include "mainwindow.h"
#include "views/CRUD/headers/homepagenosite.h"
#include "views/CRUD/headers/homepagesite.h"
#include "views/CRUD/headers/createsitedialog.h"
#include "views/dialogs/headers/settingsdialog.h"
#include <QtWidgets>
#include <QAction>
#include <QToolBar>

MainWindow::MainWindow(QWidget *parent, QString filePath)
    : QMainWindow(parent)
{
    if(filePath != "NULL"){
        this->filePath = filePath;
        this->siteIsLoaded = true;
    }else{
        this->filePath = QString(); //Create empty string for the current file path
        siteIsLoaded = false;
    }

    QSettings settings;
    validateRecentFiles(); //Make sure the recent files all exist
    QRect windowGeometry = settings.value("windowGeometry").toRect(); //Get the stored window geometry
    this->setGeometry(windowGeometry); //Set it

    this->renderView();
    setUnifiedTitleAndToolBarOnMac(true); //Toolbar and title are unseperated on macOS


}

void MainWindow::renderView()
{
    this->createMenuBar();
    siteIsLoaded ? this->setCentralWidget(new HomePageSite(this, filePath)) :
                   this->setCentralWidget(new HomePageNoSite(this));
    this->setStatusBar(new QStatusBar);
}




MainWindow::~MainWindow() //Destructor
{
 QSettings settings;
 settings.setValue("windowGeometry", this->geometry()); //Remember the last size and position of the main window
}


void MainWindow::createMenuBar()
{
    menuBar()->clear();
    //TODO : Deal with no site loaded condition
    ActionService as(siteIsLoaded);
    //File menu
    QMenu *fileMenu = menuBar()->addMenu(tr("Fichier")); // tr() is to allow translations with QLinguistic
    fileMenu->addActions(as.createFileActions(this)->actions());
    //Load recent files
    QMenu *recentFilesMenu = fileMenu->addMenu(tr("Ouvrir recents"));
    recentFilesMenu->addActions(as.createRecentFilesActions(this)->actions());

    //Settings menu
    QMenu *settingsMenu = menuBar()->addMenu(tr("Réglages"));
    settingsMenu->addActions(as.createSettingsActions(this)->actions());

    //Create the toolbar as well //Isolate in seperate functions
    //Remove all previous toolbars
    QList<QToolBar *> allToolBars = findChildren<QToolBar *>();
    foreach(QToolBar *tb, allToolBars) {
        // This does not delete the tool bar.
        removeToolBar(tb);
    }

}


void MainWindow::createSite()
{
    QDialog *createSite = new createSiteDialog(this);
    connect(createSite, SIGNAL(openSite(QString)), this, SLOT(openSite(QString)));
    createSite->show();
}

void MainWindow::openSite(){
    QString temp = QFileDialog::getOpenFileName(this, tr("Choisir le site"), QDir::homePath(), tr("Site (*.archeo)"));
    if(!temp.isEmpty()){ //If user doesn't press cancel
        if(!siteIsLoaded){
            filePath = temp;
            siteIsLoaded = true;
            addFileToSettings(temp);
            renderView();
        }else if(temp != filePath){
            QFileInfo info(filePath);
            QString filePathName = info.fileName();
            QString text = QString(tr("Souhaitez-vous ouvrir le fichier %1 dans une nouvelle fenêtre?")).arg(filePathName);
            int res = QMessageBox::question(this, tr("Ouverture de fichier"), text,QMessageBox::Cancel ,QMessageBox::No, QMessageBox::Yes);

            if(res == QMessageBox::Yes){
                MainWindow *newWindow = new MainWindow(0, temp);
                newWindow->move(20, -20);
                newWindow->show(); // Open a new window
            }else if(res == QMessageBox::No){
                filePath = temp;
                addFileToSettings(temp);
                renderView();
            }
        }
    }
}
void MainWindow::openSite(QString filePath){
    if(!siteIsLoaded){
        this->filePath = filePath;
            if(!filePath.isEmpty()){ //If user doesn't press cancel
            siteIsLoaded = true;
            addFileToSettings(filePath);
            renderView();
        }
    }
}

void MainWindow::openRecentSite(){
    //Identify the SIGNAL that called this function to get the filePath
    QAction *action = qobject_cast<QAction *>(sender());
    QString temp = action->text();
    if(action){
        if(!siteIsLoaded){
            filePath = temp; //Load the file stored in the actions data | text = AIS3, data = /path/to/AIS3.archeo
            siteIsLoaded = true;
            renderView();
        }else if(siteIsLoaded && filePath != temp){
            QFileInfo info(filePath);
            QString filePathName = info.fileName();
            QString text = QString(tr("Souhaitez-vous ouvrir le fichier %1 dans une nouvelle fenêtre?")).arg(filePathName);
            int res = QMessageBox::question(this, tr("Ouverture de fichier"), text,QMessageBox::Cancel ,QMessageBox::No, QMessageBox::Yes);

            if(res == QMessageBox::Yes){
                MainWindow *newWindow = new MainWindow(0, temp);
                newWindow->move(20, -20);
                newWindow->show(); // Open a new window
            }else if(res == QMessageBox::No){
                filePath = temp;
                addFileToSettings(temp);
                renderView();
            }
        }
    }
}

void MainWindow::openRecentSite(QListWidgetItem *item)
{
    QString temp = item->text();
    if(!siteIsLoaded){ //If user opens the already loaded site, nothing happens
        filePath = item->text();
        siteIsLoaded = true;
        renderView();
    }else if(siteIsLoaded && filePath != temp){
        QFileInfo info(filePath);
        QString filePathName = info.fileName();
        QString text = QString(tr("Souhaitez-vous ouvrir le fichier %1 dans une nouvelle fenêtre?")).arg(filePathName);
        int res = QMessageBox::question(this, tr("Ouverture de fichier"), text,QMessageBox::Cancel ,QMessageBox::No, QMessageBox::Yes);

        if(res == QMessageBox::Yes){
            MainWindow *newWindow = new MainWindow(0, temp);
            newWindow->move(20, -20);
            newWindow->show(); // Open a new window
        }else if(res == QMessageBox::No){
            filePath = temp;
            addFileToSettings(temp);
            renderView();
        }
    }
}

void MainWindow::closeSite(){
    filePath = QString();
    siteIsLoaded = false;
    renderView();
}

void MainWindow::openGeneralSettings()
{
    QDialog *settings = new settingsDialog(this);
    settings->show();
}

void MainWindow::addFileToSettings(QString fileName)
{
    QSettings settings;
    QStringList recentFiles = settings.value("recentFilesList").toStringList();
    recentFiles.removeAll(fileName); //Don't want duplicates
    recentFiles.prepend(fileName);

    if(recentFiles.size() > 5){
        recentFiles.removeLast(); //Only keep the 5 most recent ones
    }

    settings.setValue("recentFilesList", recentFiles);
}

void MainWindow::validateRecentFiles()
{
    QSettings settings;
    QStringList recentFiles = settings.value("recentFilesList").toStringList();

    for(int i = 0; i < recentFiles.size(); i++){
        QFileInfo fileInfo(recentFiles.at(i));
        if(!fileInfo.exists() || fileInfo.suffix() != "archeo" ){ //File doesn't exist or isn't a .archeo file
            recentFiles.replace(i, ""); //Replace the file path with an empty string
        }
    }
    recentFiles.removeAll(""); //Remove all the empty strings
    settings.setValue("recentFilesList", recentFiles);
}
