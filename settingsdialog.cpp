#include "settingsdialog.h"
#include <QtWidgets>
/*
* This class creates the layout for the general settings dialog
* User can choose these general settings:
    * Language
    * Color theme
    * Font size
    * Font
    * ...
*
*/


settingsDialog::settingsDialog(QWidget *parent) : QDialog(parent)
{
 //On the left : list with the different settings
 //On the right : stacked pages with the setting options

    this->setModal(false); //User can interact with the app while this window is open

    QGridLayout *layout = new QGridLayout;

    this->setWindowTitle(tr("Réglages")); //Set a window title
    QListWidget *settingsOptions = new QListWidget; //List for all the different types of settings
    settingsOptions->setMaximumWidth(120); //Automatically set the width of the tree view
    settingsOptions->setIconSize(QSize(25, 25));

    QListWidgetItem *languageOption = new QListWidgetItem; //Create the language setting
    languageOption->setIcon(QIcon(":/icons/language"));
    languageOption->setText(tr("Langue"));

    QListWidgetItem *fontOption = new QListWidgetItem; //Create the font setting
    fontOption->setIcon(QIcon(":/icons/font"));
    fontOption->setText(tr("Police"));

    QListWidgetItem *themeOption = new QListWidgetItem; //Create the theme setting
    themeOption->setIcon(QIcon(":/icons/theme"));
    themeOption->setText(tr("Thème"));

    settingsOptions->addItem(languageOption);
    settingsOptions->addItem(fontOption);
    settingsOptions->addItem(themeOption);

    settingsPages = this->createSettingsPages();
    settingsOptions->setCurrentRow(0); //Set the tree index to 0 right away to get the first setting

    layout->addWidget(settingsOptions, 0, 0);
    layout->addWidget(settingsPages, 0, 1);

    this->setLayout(layout);

    connect(settingsOptions, SIGNAL(currentItemChanged(QListWidgetItem*,QListWidgetItem*)), this, SLOT(changePage(QListWidgetItem*, QListWidgetItem*)));


}

QStackedWidget* settingsDialog::createSettingsPages()
{
    QStackedWidget *pages = new QStackedWidget;

    //Language setting page
    QWidget *languageSettingPage = new QWidget; //Create the widget to add to the StackedWidget
    QHBoxLayout *languageLayout = new QHBoxLayout; //Create the layout

    languagePicker = new QComboBox;
    languagePicker->addItem(QIcon(":/icons/english"), "English");
    languagePicker->addItem(QIcon(":/icons/french"), "Français");

    QPushButton *changeLanguageButton = new QPushButton(tr("Changer la langue"));

    connect(changeLanguageButton, SIGNAL(clicked()), this, SLOT(changeLanguage()));

    languageLayout->addWidget(languagePicker);
    languageLayout->addWidget(changeLanguageButton);

    languageSettingPage->setLayout(languageLayout);

    //Font setting page

    QWidget *fontSettingPage = new QWidget; //Create the widget to add to the StackedWidget
    QHBoxLayout *fontLayout = new QHBoxLayout;

    QLabel *fontLabel = new QLabel(tr("Réglage de la police et de sa taille"));

    fontLayout->addWidget(fontLabel);

    fontSettingPage->setLayout(fontLayout);

    //Theme setting page
    QWidget *themeSettingPage = new QWidget;
    QHBoxLayout *themeLayout = new QHBoxLayout;

    QLabel *themeLabel = new QLabel(tr("Réglage du thème de l'application"));
    QComboBox *themePicker = new QComboBox;
    QStringList themes;
    themes << tr("Normal") << tr("Sombre"); //Set the different themes, easily add them here
    themePicker->addItems(themes);



    themeLayout->addWidget(themeLabel);
    themeLayout->addWidget(themePicker);

    themeSettingPage->setLayout(themeLayout);

    //Add all the pages to the stack
    pages->addWidget(languageSettingPage);
    pages->addWidget(fontSettingPage);
    pages->addWidget(themeSettingPage);

    return pages;



}

void settingsDialog::changePage(QListWidgetItem *current, QListWidgetItem *previous)
{
    if(current->text() ==  tr("Langue")){
        settingsPages->setCurrentIndex(0);
        this->setWindowTitle(tr("Langue")); //Change the window title TODO : append, like : Settings | Language
    }else if(current->text() == tr("Police")){
        settingsPages->setCurrentIndex(1);
          this->setWindowTitle(tr("Police"));
    }else if(current->text() == tr("Thème")){
        settingsPages->setCurrentIndex(2);
        this->setWindowTitle(tr("Theme"));
    }


}

void settingsDialog::changeLanguage()
{
   QSettings settings;
   settings.setValue("language", languagePicker->currentText());
   QMessageBox::information(this, tr("Information"), tr("Le changement de langue sera effectif à la prochaine ouverture du logiciel"));
}


