#include "statisticswidgets.h"
#include <QtWidgets>

StatisticsWidgets::StatisticsWidgets(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout *layout = new QVBoxLayout;

    QLabel *title = new QLabel("Page statistiques");

    layout->addWidget(title);

    setLayout(layout);
}
