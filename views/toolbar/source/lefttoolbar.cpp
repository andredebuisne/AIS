#include "views/toolbar/headers/lefttoolbar.h"
#include "services/headers/actionservice.h"

LeftToolBar::LeftToolBar(QWidget *parent) : QToolBar()
{
    ActionService as(true);
    addActions(as.createCRUDActions(parent)->actions());
    setOrientation(Qt::Vertical);
    setToolButtonStyle(Qt::ToolButtonTextUnderIcon );
    setMovable(false);
    setContextMenuPolicy(Qt::PreventContextMenu);
}
