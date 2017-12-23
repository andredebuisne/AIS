#ifndef CREATEOBJECTWIDGET_H
#define CREATEOBJECTWIDGET_H

#include <QtWidgets>

class CreateObjectWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CreateObjectWidget(QWidget *parent = nullptr, QString filePath = nullptr, int layerId = -2);
    void populateComboBox();
private:
    QComboBox *objectLayerId;
    QSpinBox *objectId;
    QLineEdit *objectName;
    QComboBox *objectType;
    QLineEdit *objectMaterial;
    QDoubleSpinBox *objectHeight;
    QDoubleSpinBox *objectWidth;
    QDoubleSpinBox *objectDepth;
    QDoubleSpinBox *objectDiameter;
    QDoubleSpinBox *objectWeight;
    QLineEdit *objectCiviliation;
    QLineEdit *objectLocation; //Sector found in
    QDoubleSpinBox *objectLocationX;
    QDoubleSpinBox *objectLocationY;
    QDoubleSpinBox *objectAltitude;
    QLineEdit *objectDescription;
    QString filePath;
    QPushButton *createObjectButton;
    int layerId;
    bool formIsValid;

signals:
    void updateView();

public slots:
    void createObject();
    void checkFormValidity();
};

#endif // CREATEOBJECTWIDGET_H
