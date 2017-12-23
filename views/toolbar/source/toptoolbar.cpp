#include "views/toolbar/headers/toptoolbar.h"
#include "services/headers/actionservice.h"

TopToolBar::TopToolBar(QWidget *parent) : QToolBar()
{
    ActionService as(true); //Show toolbar when site is loaded, so pass true right away
    addActions(as.createTopToolbarActions(parent)->actions());
    setOrientation(Qt::Horizontal);
    //setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    setMovable(false);
    setContextMenuPolicy(Qt::PreventContextMenu);

}
