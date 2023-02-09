#pragma once

#include <QWidget>
#include "widgethelper.h"

template<class WidgetType>
class SingleWidget
{
public:
    SingleWidget():
        m_widget(nullptr)
    {

    }

    ~SingleWidget()
    {
        if(m_widget)
        {
            delete m_widget;
        }
    }

    WidgetType *w()
    {
        return m_widget;
    }

    void show()
    {
        createIfNoExist();
        m_widget->show();
        WidgetHelper::showWindow(m_widget);
    }

    void closeIfExist()
    {
        if(m_widget)
        {
            m_widget->close();
        }
    }

    bool createIfNoExist(std::function<WidgetType*()> _func = nullptr)
    {
        if(!m_widget)
        {
            if(_func)
            {
                m_widget = _func();
            } else
            {
                m_widget = new WidgetType();
            }

            m_widget->setAttribute(Qt::WA_DeleteOnClose);
            QObject::connect(m_widget, &QWidget::destroyed, [this]
            {
                m_widget = nullptr;
            });

            return true;
        }

        return false;
    }

    WidgetType *m_widget;
};
