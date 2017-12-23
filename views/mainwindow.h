#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include "services/headers/actionservice.h" //We use this service to create our actions for our menu bar

class MainWindow : public QMainWindow
{
    Q_OBJECT

public slots:
    void createSite(); //Open the site creator dialog
    void openSite(); //Open the open site dialog
    void openSite(QString filePath);
    void openRecentSite(); //Open a recent site (from Action)
    void openRecentSite(QListWidgetItem*); //Open a recent site (from ListWidget)
    void closeSite(); //Close the site
    void openGeneralSettings();


public:
    MainWindow(QWidget *parent = 0, QString filePath = "NULL");
    ~MainWindow();
    void createMenuBar(); //Create the menubar
    void renderView(); //Create the main window view, used for creation and update
    void addFileToSettings(QString fileName);
    void validateRecentFiles(); //Verify the existence of every recent file in the list

private:
    QString filePath; //Filepath of the current file
    bool siteIsLoaded; //Flag, indicates how to create menu and views --> Can be removed?


};

#endif // MAINWINDOW_H
