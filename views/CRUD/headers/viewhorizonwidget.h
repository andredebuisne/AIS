#ifndef VIEWHORIZONWIDGET_H
#define VIEWHORIZONWIDGET_H

#include <QWidget>
#include "classes/headers/horizon.h"

class ViewHorizonWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ViewHorizonWidget(QWidget *parent = nullptr, QString filePath = nullptr, int horizonId = -2);
    void createLayout();

private:
    QGridLayout *layout;

    //Static view
    QString filePath;
    int horizonId;
    int numLayers;

    QLabel *horizonIdValue;
    QLabel *horizonName;
    QLabel *horizonType;
    QLabel *horizonDescription;
    QPushButton *editButton;
    QPushButton *deleteButton;

    //Update fields
    QSpinBox *horizonIdEdit;
    QLineEdit *horizonNameEdit;
    QComboBox *horizonTypeEdit;
    QLineEdit *horizonDescriptionEdit;
    QPushButton *updateHorizonButton;
    QPushButton *cancel;


signals:
    void updateView();

public slots:
    void openUpdateView();
    void openStaticView();
    void updateHorizon();
    void deleteHorizon();
};

#endif // VIEWHORIZONWIDGET_H
