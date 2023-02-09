#include "settingchangeevent.h"

QEvent::Type SettingChangeEvent::m_eventType = QEvent::None;

SettingChangeEvent::SettingChangeEvent():
    QEvent(SettingChangeEvent::type())
{

}

QEvent::Type SettingChangeEvent::type()
{
    if (m_eventType == QEvent::None)
    {
        int generatedType = QEvent::registerEventType();
        m_eventType = static_cast<QEvent::Type>(generatedType);
    }

    return m_eventType;
}
