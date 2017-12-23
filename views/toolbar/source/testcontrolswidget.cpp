#include "views/toolbar/headers/testcontrolswidget.h"
#include <QtWidgets>

TestControlsWidget::TestControlsWidget(QWidget *parent) : QWidget(parent)
{
    QGridLayout *mainLayout = new QGridLayout;
    QGroupBox *group = new QGroupBox;
    QVBoxLayout *layout = new QVBoxLayout;

    //Create the buttons
    QPushButton *parametricTestsButton = new QPushButton(tr("Test Paramétriques"));
    QPushButton *nonParametricTestsButton = new QPushButton(tr("Tests non paramétriques"));
    QPushButton *allTestsButton = new QPushButton(tr("Tous tests statistiques"));

    layout->addWidget(parametricTestsButton);
    layout->addWidget(nonParametricTestsButton);
    layout->addWidget(allTestsButton);

    group->setLayout(layout);
    group->setMaximumHeight(100);
    mainLayout->addWidget(group);

    this->setLayout(mainLayout);


}
