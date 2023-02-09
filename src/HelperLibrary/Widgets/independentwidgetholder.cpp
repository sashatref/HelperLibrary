#include "independentwidgetholder.h"

namespace HelperLibraryNS
{

IndependentWidgetHolder::IndependentWidgetHolder(QObject *_parent):
    QObject(_parent)
{

}

void IndependentWidgetHolder::registerIndependentWindow(QWidget *_independentWidnow)    //зарегестрировать окно без родителя
{
    m_independentWidgets.append(_independentWidnow);
    _independentWidnow->setAttribute(Qt::WA_DeleteOnClose);
    connect(_independentWidnow, &QWidget::destroyed, this, [this, _independentWidnow]
    {
        m_independentWidgets.removeOne(_independentWidnow);
    });
}

void IndependentWidgetHolder::closeIndependentWindows()
{
    foreach (QWidget *_item, m_independentWidgets)
    {
        _item->close();
    }
}

}
