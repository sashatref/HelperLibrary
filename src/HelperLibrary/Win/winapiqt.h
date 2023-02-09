#pragma once

#include "../export.h"

#include <Windows.h>

namespace HelperLibraryNS
{


class HELPERLIBRARY_EXPORT WinApiQt
{
public:
    static QRect findWindowRect(const QString &_className, const QString &_windowName);

    /*!
     * \brief findWindow возвращает хэндл окна по заданным именам окна и класса
     * \param _className
     * \param _windowName
     * \return
     */
    static HWND findWindow(const QString &_className, const QString &_windowName);

    /*!
     * \brief getWindowRect позвращает размер окна
     * \param _hWnd хэндл окна
     * \return
     */
    static QRect getWindowRect(HWND _hWnd);

    static QString getLastErrorMsg();

    static QString getComputerName();

    static QString parseError(unsigned long _error);

    static MEMORYSTATUSEX getRamInfo();

    static void openFileInExplorer(const QString &_filePath);
    static void openFolderInExplorer(const QString &_folderPath);

    /*
     * Преобразовует имя компьютера в IP адрес
     */
    static QString getNetAddress(const QString &_inAddr);

    static void pingExternal(const QString &_addr);
};

}
