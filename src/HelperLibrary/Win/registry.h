#pragma once

#include "../export.h"

#include <QString>
#include <QVariant>

class HELPERLIBRARY_EXPORT Registry
{
public:
    //проверить, есть ли права администратора у текущей программы
    static bool checkAdminRights();


    enum Brunch
    {
        CLASSES_ROOT   = 0x80000000,
        CURRENT_USER   = 0x80000001,
        LOCAL_MACHINE  = 0x80000002,
        USERS          = 0x80000003
    };

    //установка значений в x64 реестр
    static bool setRegisrtyValue(Brunch _branch, const QString &_path, const QString &_key, const QString &_value);
    static bool setRegisrtyValue(Brunch _branch, const QString &_path, const QString &_key, int _value);

    //пока не работает
    static bool removeRegistryKey(Brunch _branch, const QString &_path, const QString &_key);

    //установка региональных параметров
    static bool setRegionalParams();

    //установка английского языка по умолчанию
    static bool setLanguageParams();

    //установка параметров errorreporting
    static bool setErrorReportingParams();

    //установка параметров контроля учетных записей
    static bool setUACParams();

    //установка параметров отключение автозапуска всех носителей
    static bool setDisableAutorun();

    //установка параметров автологона
    static bool setWinLogonParams();

    static QString getLastError();

private:
    static void checkResult(bool _result);
};

