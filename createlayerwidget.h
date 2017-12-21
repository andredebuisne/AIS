#ifndef CREATELAYERWIDGET_H
#define CREATELAYERWIDGET_H

#include <QWidget>
#include <QtWidgets>

class CreateLayerWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CreateLayerWidget(QWidget *parent = nullptr, QString filePath = nullptr, int horizonId = -2); //-1 horizon is base horizon
    void populateComboBox();
    QGroupBox *createRelationshipGroup();
    void createRelationship();

signals:
    void updateView();

private:
    //Layer
    QComboBox *layerHorizonId;
    QSpinBox *layerId;
    QLineEdit *layerName;
    QComboBox *layerType;
    QLineEdit *layerSupervisor;
    QLineEdit *layerSoilColor;
    QLineEdit *layerDescription;
    QDateTimeEdit *layerDateDug;
    QLineEdit *layerCivilisation;
    QString filePath;
    QPushButton *createLayerButton;
    //Relationship
    QGroupBox *relationshipGroup;
    QSpinBox *earlierThan;
    QSpinBox *laterThan;
    QSpinBox *contemporaryTo;
    QSpinBox *equalTo;
    int horizonId;

protected:
    void keyPressEvent(QKeyEvent *event);

public slots:
    void createLayer();
};

#endif // CREATELAYERWIDGET_H
