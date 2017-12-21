#ifndef ACTIONSERVICE_H
#define ACTIONSERVICE_H
#include <QActionGroup>
#include <QtWidgets>
#include <QObject>


class ActionService : QObject
{
     Q_OBJECT
public:
    ActionService(bool siteIsLoaded);
    QActionGroup* createFileActions(QWidget *parent);
    QActionGroup* createRecentFilesActions(QWidget *parent);
    QActionGroup* createSettingsActions(QWidget *parent);
    QActionGroup* createCRUDActions(QWidget *parent);
    QActionGroup* createTopToolbarActions(QWidget *parent);

private:
    bool siteIsLoaded;
};

#endif // ACTIONSERVICE_H
