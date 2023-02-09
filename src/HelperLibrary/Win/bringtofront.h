#pragma once

#include "../export.h"

#include <QRect>

namespace BringToFrontNS
{
    struct SearchWindowConf
    {
        bool findByProcessName = false;
        bool findByWindowTitleAndClass = false;

        QString processName;
        QString windowTitle;
        QString windowClass;
    };

    void HELPERLIBRARY_EXPORT bringToFront(const SearchWindowConf &_searchConf, const QRect &_rect);

    bool HELPERLIBRARY_EXPORT bringToFront(const QString &_processName, const QRect &_rect);

    bool HELPERLIBRARY_EXPORT bringToFront(const QString &_windowClass, const QString _windowTitle, const QRect &_rect);

    bool HELPERLIBRARY_EXPORT bringToFront(
        const QString &_processName,
        const QString &_windowClass,
        const QString &_windowTitle,
        const QRect &_rect);
}

