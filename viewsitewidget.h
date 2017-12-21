#ifndef VIEWSITEWIDGET_H
#define VIEWSITEWIDGET_H

#include <QWidget>
#include "site.h"

class ViewSiteWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ViewSiteWidget(QWidget *parent = nullptr, QString filePath = nullptr);
    void loadSite();
    QGroupBox *createSiteInformation();

private:
    QString filePath;
    Site site;

signals:

public slots:
};

#endif // VIEWSITEWIDGET_H
