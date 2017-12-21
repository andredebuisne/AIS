#include "lefttoolbar.h"
#include "actionservice.h"

LeftToolBar::LeftToolBar(QWidget *parent) : QToolBar()
{
    ActionService as(true);
    addActions(as.createCRUDActions(parent)->actions());
    setOrientation(Qt::Vertical);
    setToolButtonStyle(Qt::ToolButtonTextUnderIcon );
    setMovable(false);
    setContextMenuPolicy(Qt::PreventContextMenu);
}
