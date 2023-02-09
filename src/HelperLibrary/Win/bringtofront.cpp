#include "bringtofront.h"
#include "../functions.h"

namespace BringToFrontNS
{

struct WindowInfo
{
    QRect rect;
    QString processName;
    QString windowClass;
    QString windowTitle;
    bool result = false;
};

QString getWindowClassName(HWND _hwnd)
{
    const int buffSize = 4096;
    char buff[buffSize] = { 0 };

    GetClassNameA(_hwnd, buff, buffSize);
    return QString(buff);
}

QString getWindowTitle(HWND _hwnd)
{
    const int buffSize = 4096;
    char buff[buffSize] = { 0 };

    GetWindowTextA(_hwnd, buff, buffSize);
    return QString(buff);
}

bool checkWindowClassAndTitle(HWND _hwnd, const QString &_winClass, const QString &_winTitle)
{
    if (_winClass.isEmpty() && _winTitle.isEmpty()) return true;

    const QString moduleClassName = getWindowClassName(_hwnd);
    const QString moduleTitleName = getWindowTitle(_hwnd);

    if (!_winClass.isEmpty() && _winClass != moduleClassName)
    {
        return false;
    }

    if (!_winTitle.isEmpty() && _winTitle != moduleTitleName)
    {
        return false;
    }

    return true;
}

int __stdcall OnEnumWindowShow(HWND hwnd, LPARAM lParam)
{
    WindowInfo *wInfo = reinterpret_cast<WindowInfo*>(lParam);
    bool bContinue = true;
    DWORD dwProcessID;
    if (GetWindowThreadProcessId(hwnd, &dwProcessID))
    {
        HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwProcessID);
        if (hProcess)
        {
            const int buffSize = 4096;
            char buff[buffSize] = { 0 };
            if (GetModuleFileNameExA(hProcess, NULL, buff, buffSize))
            {
                const QString sModuleName(buff);

                if (sModuleName.indexOf(wInfo->processName, 0, Qt::CaseInsensitive) != -1)
                {
                    if (checkWindowClassAndTitle(hwnd, wInfo->windowClass, wInfo->windowTitle))
                    {
                        if (!IsHungAppWindow(hwnd))
                        {
                            SetWindowPos(hwnd, HWND_TOP,
                                         wInfo->rect.x(),
                                         wInfo->rect.y(),
                                         wInfo->rect.width(),
                                         wInfo->rect.height(),
                                         SWP_SHOWWINDOW);
                        }

                        //SetForegroundWindow(hwnd);
                        bContinue = false;
                        wInfo->result = true;
                    }
                }
            }

            CloseHandle(hProcess);
        }
    }

    return bContinue;
}

bool bringToFront(const QString &_processName, const QRect &_rect)
{
    if(_processName.isEmpty())
    {
        return false;
    }

    WindowInfo wInfo;
    wInfo.processName = _processName;
    wInfo.rect = _rect;

    EnumWindows(&OnEnumWindowShow, (LPARAM)&wInfo);

    return wInfo.result;
}

bool bringToFront(const QString &_windowClass, const QString _windowTitle, const QRect &_rect)
{
    if(_windowClass.isEmpty() && _windowTitle.isEmpty())
    {
        return false;
    }

    HWND hWindow = FindWindowA(
                _windowClass.isEmpty() ? 0 : _windowClass.toUtf8().data(),
                _windowTitle.isEmpty() ? 0 : _windowTitle.toUtf8().data());
    if (hWindow && !IsHungAppWindow(hWindow))
    {
        SetWindowPos(hWindow, HWND_TOP,
                     _rect.x(),
                     _rect.y(),
                     _rect.width(),
                     _rect.height(),
                     SWP_SHOWWINDOW);
        return true;
    }

    return false;
}

bool bringToFront(const QString &_processName, const QString &_windowClass, const QString &_windowTitle, const QRect &_rect)
{
    if(_processName.isEmpty())
    {
        return false;
    }

    if(_windowClass.isEmpty() && _windowTitle.isEmpty())
    {
        return false;
    }

    WindowInfo wInfo;
    wInfo.processName = _processName;
    wInfo.windowClass = _windowClass;
    wInfo.windowTitle = _windowTitle;
    wInfo.rect = _rect;

    EnumWindows(&OnEnumWindowShow, (LPARAM)&wInfo);

    return wInfo.result;
}

void bringToFront(const SearchWindowConf &_searchConf, const QRect &_rect)
{
    if (_searchConf.findByProcessName && _searchConf.findByWindowTitleAndClass)
    {
        if (!BringToFrontNS::bringToFront(
                    _searchConf.processName,
                    _searchConf.windowClass,
                    _searchConf.windowTitle,
                    _rect))
        {
            qWarning() << Text::format("BringToFrontButton::pressed | Process [%1] with class [%2] and title [%3] not found",
                          _searchConf.processName,
                          _searchConf.windowClass,
                          _searchConf.windowTitle);
        }

        return;
    }

    if (_searchConf.findByProcessName)
    {
        if (!BringToFrontNS::bringToFront(_searchConf.processName, _rect))
        {
            qWarning() << Text::format("BringToFrontButton::pressed | Process [%1] not found", _searchConf.processName);
        }

        return;
    }

    if (_searchConf.findByWindowTitleAndClass)
    {
        if (!BringToFrontNS::bringToFront(_searchConf.windowClass, _searchConf.windowTitle, _rect))
        {
            qWarning() << Text::format("Window with class [%1] and title [%2] not found",
                          _searchConf.windowClass,
                          _searchConf.windowTitle);
        }

        return;
    }
}



}
