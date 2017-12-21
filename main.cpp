#include "mainwindow.h"
#include <QApplication>
#include <QTranslator>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QSettings settings;
    QTranslator t;
    QString language = settings.value("language").toString();
    QString lang;
    //If this is the first time the user opens the app, let them choose the language
    if(language.isEmpty()){
        QStringList languages;
        languages << "Français" << "English";
        lang = QInputDialog::getItem(NULL, "Select language", "Language", languages);
        settings.setValue("language", lang);
    }else{
        lang = settings.value("language").toString();
    }

    if(lang == "English"){
        t.load(":/translations/AIS_en.qm"); //TEMPORARY : Load from QSettings
    }

    a.installTranslator(&t);
    MainWindow w;
    w.show();


    return a.exec();
}
