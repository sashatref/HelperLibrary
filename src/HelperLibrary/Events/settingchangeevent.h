#pragma once

#include "../export.h"
#include "../igadget.h"
#include <QEvent>

class HELPERLIBRARY_EXPORT SettingChangeEvent : public QEvent
{
public:
    SettingChangeEvent();

    static QEvent::Type type();

private:
    static QEvent::Type m_eventType;
};
