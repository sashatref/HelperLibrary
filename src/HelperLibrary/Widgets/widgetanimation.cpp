#include "widgetanimation.h"

namespace WidgetAnimation
{

Hider::Hider(QWidget *_widget, const QSize &_start, const QSize &_end, int _duration, QEasingCurve::Type _type):
    QPropertyAnimation  (_widget, "maximumSize"),
    m_currentSize       (),
    m_direction         (Forw),
    m_startSize         (_start),
    m_endSize           (_end),
    m_duration          (_duration)
{
    connect(this, &QPropertyAnimation::valueChanged, this, &Hider::onValueChanged);
    setDuration(m_duration);
    setEasingCurve(_type);

    m_currentSize = m_startSize;
}

Hider::~Hider()
{

}

void Hider::switchPosition()
{
    if(m_direction == Forw)
    {
        hide();
    } else
    {
        show();
    }
}

void Hider::hide()
{
    setStartValue(m_currentSize);
    setEndValue(m_endSize);

    start(/*QAbstractAnimation::DeleteWhenStopped*/);

    m_direction = Back;
}

void Hider::show()
{
    setStartValue(m_currentSize);
    setEndValue(m_startSize);

    start(/*QAbstractAnimation::DeleteWhenStopped*/);

    m_direction = Forw;
}

void Hider::onValueChanged(const QVariant &_value)
{
    m_currentSize = _value.toSize();
}

}
