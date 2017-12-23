#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H
#include <QDialog>
#include <QtWidgets>

class settingsDialog : public QDialog
{
    Q_OBJECT   
public slots:
    void changeLanguage(); //Change the current language of the app
    QStackedWidget* createSettingsPages(); //Create the layout for the stacked pages on the right
    void changePage(QListWidgetItem*, QListWidgetItem*);

public:
    settingsDialog(QWidget *parent);
    QStackedWidget *settingsPages; //Stacked pages, made public so we can change its index
    QComboBox *languagePicker;

};

#endif // SETTINGSDIALOG_H
