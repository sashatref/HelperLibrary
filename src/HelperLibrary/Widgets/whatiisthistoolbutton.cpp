#include "whatiisthistoolbutton.h"

namespace HelperLibraryNS
{

WhatiIsThisToolButton::WhatiIsThisToolButton(QWidget *_parent):
    QToolButton(_parent)
{
    QAction *act = QWhatsThis::createAction(this);
    setIcon(act->icon());
    setText(act->text());
    setToolTip(act->toolTip());
    setStatusTip(act->statusTip());
    connect(this, &WhatiIsThisToolButton::clicked, act, &QAction::trigger);
    setCheckable(act->isCheckable());
}

}
