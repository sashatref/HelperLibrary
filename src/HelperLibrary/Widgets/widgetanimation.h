#pragma once
#include <QWidget>
#include <QPropertyAnimation>

#include "../export.h"

namespace WidgetAnimation
{

class HELPERLIBRARY_EXPORT Hider : public QPropertyAnimation
{
    Q_OBJECT
public:
    enum Direction
    {
        Forw,
        Back
    };

    Hider(QWidget *_widget,
          const QSize &_start,
          const QSize &_end,
          int _duration,
          QEasingCurve::Type _type = QEasingCurve::InOutQuad);

    virtual ~Hider();

    void switchPosition();

    void hide();

    void show();

private slots:
    void onPropertyFinished() {}
    void onValueChanged(const QVariant &_value);

private:
    QSize m_currentSize;

    Direction m_direction;

    QSize m_startSize;
    QSize m_endSize;
    int m_duration;
};

}

