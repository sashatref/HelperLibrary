#pragma once

#include <Windows.h>
#include <QString>

#include "../export.h"

class HELPERLIBRARY_EXPORT WinApiHelper
{
public:
    WinApiHelper();

    bool findWindow(const QString &_className, const QString &_windowName);


    //получить текстовое представление ошибки Windows по коду
    static QString parseError(ulong _error);

    //получить текстовое представление последней ошибки Windows
    static QString getLastErrorMsg();


    static void pressDownKey(Qt::Key _key);
    static void pressUpKey(Qt::Key _key);
    static void clickKey(Qt::Key _key);                 //presDown + presUp
    static void clickKeyGroup(QList<Qt::Key> _keys);    //presDown 1 -> pressDown 2 -> pressUp 2 -> pressUp 1

    HWND getWindowWnd() const;

    HWND m_window;

    static int mapKeyToWinApi(Qt::Key _key);


    static QString getComputerName();
    static bool setComputerName(const QString &_name);

    static QString expandEnvironmentString(const QString& _path);
};

QString HELPERLIBRARY_EXPORT qExpandEnv(const QString &_in);
void HELPERLIBRARY_EXPORT qExpandEnv(std::initializer_list<QString*> _arr);
