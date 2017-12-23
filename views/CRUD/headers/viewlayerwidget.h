#ifndef VIEWLAYERWIDGET_H
#define VIEWLAYERWIDGET_H

#include <QWidget>
#include <QtWidgets>
#include "classes/headers/object.h"

class ViewLayerWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ViewLayerWidget(QWidget *parent = nullptr, QString filePath = nullptr, int layerId = -2);
    void createLayout();
private:
    QString filePath;
    int layerId;
    QGridLayout *layout;
    QList<Object> objectList;
    //Static
    QLabel *layerIdValue;
    QLabel *layerName;
    QLabel *layerType;
    QLabel *layerSupervisor;
    QLabel *layerSoilColor;
    QLabel *layerDescription;
    QLabel *layerDateDug;
    QLabel *layerCivilisation;
    QPushButton *deleteButton;
    QPushButton *openUpdateViewButton;

    //Static relationship
    QLabel *earlierThan;
    QLabel *laterThan;
    QLabel *equalTo;
    QLabel *contemporaryTo;

    //Edit
    QSpinBox *layerIdEdit;
    QLineEdit *layerNameEdit;
    QComboBox *layerTypeEdit;
    QLineEdit *layerSupervisorEdit;
    QLineEdit *layerSoilColorEdit;
    QLineEdit *layerDescriptionEdit;
    QDateTimeEdit *layerDateDugEdit;
    QLineEdit *layerCivilisationEdit;

    QPushButton *updateLayerButton;
    QPushButton *openStaticViewButton;

signals:
    void updateView();

public slots:
    void openStaticView();
    void openUpdateView();
    void updateLayer();
    void deleteLayer();
};

#endif // VIEWLAYERWIDGET_H
