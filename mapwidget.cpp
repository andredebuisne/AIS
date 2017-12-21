#include "mapwidget.h"
#include <QtWidgets>

MapWidget::MapWidget(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout *layout = new QVBoxLayout;

    QLabel *title = new QLabel("Carte(s) du site archéologique");

    layout->addWidget(title);

    setLayout(layout);
}
