#include "isavewidget.h"

QVariant saveWidgetState(const ISaveWidget *_sw)
{
    LayoutSaver m;
    m.save(_sw->saveWidgetState(), _sw->getWidgetUniqueName());
    return m.m();
}

void loadWidgetState(ISaveWidget *_sw, const QVariant &_val)
{
    LayoutSaver saver = _val.toMap();
    QVariant state;

    if(saver.load(state, _sw->getWidgetUniqueName()))
    {
        _sw->loadWidgetState(state);
    }
}

QVariant ISaveWidget::saveWidgetState() const
{
    LayoutSaver saver;
    saveState(saver);
    return saver.m();
}

void ISaveWidget::loadWidgetState(const QVariant &_state)
{
    const LayoutSaver saver = _state.toMap();
    loadState(saver);
}

void ISaveWidget::loadState(const LayoutSaver &_saver)
{
    Q_UNUSED(_saver)
}

void ISaveWidget::saveState(LayoutSaver &_saver) const
{
    Q_UNUSED(_saver)
}

void ISaveWidget::setOnSaveCallback(const std::function<void (const QVariant &)> &_saveStateFunc)
{
    m_saveStateFunc = _saveStateFunc;
}

void ISaveWidget::emitSaveFunc()
{
    if(m_saveStateFunc)
    {
        m_saveStateFunc(saveWidgetState());
    }
}
