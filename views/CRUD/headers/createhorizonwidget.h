#ifndef CREATEHORIZONWIDGET_H
#define CREATEHORIZONWIDGET_H
#include <QWidget>
#include <QtWidgets>

class CreateHorizonWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CreateHorizonWidget(QWidget *parent = nullptr, QString filePath = nullptr);
signals:
    void updateView();

public slots:
    void createHorizon();
    void checkFormValidity();
protected:
    void keyPressEvent(QKeyEvent *event);

private:
    QSpinBox *horizonId;
    QLineEdit *horizonName;
    QComboBox *horizonType;
    QLineEdit *horizonDescription;
    QString filePath;
    QWidget *parentWidget;
    QPushButton *createHorizonButton;
    bool formIsValid;
};

#endif // CREATEHORIZONWIDGET_H
