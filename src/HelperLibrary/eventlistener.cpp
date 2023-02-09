#include "project_pch.h"
#include "eventlistener.h"

EventListener::EventListener(QList<int> _keyList,
                             QObject *_object,
                             std::function<void (int)> _callback,
                             QObject *_parent,
                             QEvent::Type _type):
    QObject         (_parent),
    m_callback      (_callback),
    m_keyList       (_keyList),
    m_object        (_object),
    m_eventType     (_type)
{
    m_object->installEventFilter(this);
}

bool EventListener::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == m_object)
    {
        if(event->type() == m_eventType)
        {
            if(m_eventType == QEvent::KeyPress)
            {
                QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);

                if(m_keyList.contains(keyEvent->key()))
                {
                    emit onKeyPressed(keyEvent->key());

                    if(m_callback)
                    {
                        m_callback(keyEvent->key());
                    }
                }
            } else if(m_eventType == QEvent::MouseButtonPress)
            {
                QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);

                if(m_keyList.contains(mouseEvent->button()))
                {
                    emit onKeyPressed(mouseEvent->button());

                    if(m_callback)
                    {
                        m_callback(mouseEvent->button());
                    }
                }
            }
        }
    }

    return QObject::eventFilter(watched, event);
}
