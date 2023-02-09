#include "registry.h"

#include "Exceptions/userexception.h"

#include <QSettings>

bool Registry::checkAdminRights()
{
    QSettings adminPrivSettings("HKEY_LOCAL_MACHINE", QSettings::NativeFormat);
    QVariant currentAdminStatus = adminPrivSettings.value("(Default)");
    adminPrivSettings.setValue("(Default)", currentAdminStatus);
    adminPrivSettings.sync();

    return adminPrivSettings.status() != QSettings::AccessError;
}

bool Registry::setRegisrtyValue(Brunch _branch, const QString &_path, const QString &_attr, const QString &_value)
{
    HKEY hKey;

    int result = RegOpenKeyExA(HKEY(_branch), _path.toStdString().c_str(), 0, KEY_ALL_ACCESS | KEY_WOW64_64KEY, &hKey);

    if(result != NOERROR)
    {
        return false;
    }

    result = RegSetValueExA(hKey,
                             _attr.toStdString().c_str(),
                             0,
                             REG_SZ,
                             (BYTE*)_value.toStdString().c_str(),
                             _value.size());
    RegCloseKey(hKey);

    return result == NOERROR;
}

bool Registry::setRegisrtyValue(Brunch _branch, const QString &_path, const QString &_attr, int _value)
{
    HKEY hKey;

    int result = RegOpenKeyExA(HKEY(_branch), _path.toStdString().c_str(), 0, KEY_ALL_ACCESS | KEY_WOW64_64KEY, &hKey);

    if(result != NOERROR)
    {
        return false;
    }

    result = RegSetValueExA(hKey,
                             _attr.toStdString().c_str(),
                             0,
                             REG_DWORD,
                             (BYTE*)&_value,
                             sizeof(_value));

    RegCloseKey(hKey);

    return result == NOERROR;
}

bool Registry::removeRegistryKey(Registry::Brunch _branch, const QString &_path, const QString &_key)
{
    HKEY hKey;

    int result = RegOpenKeyExA(HKEY(_branch), _path.toStdString().c_str(), 0, KEY_ALL_ACCESS | KEY_WOW64_64KEY, &hKey);

    if(result != NOERROR)
    {
        return false;
    }

    result = RegDeleteKeyExA(hKey, _key.toStdString().c_str(), KEY_WOW64_64KEY, 0);

    RegCloseKey(hKey);

    return result == NOERROR;
}

bool Registry::setRegionalParams()
{
    {
        QSettings decimal("HKEY_CURRENT_USER\\Control Panel\\International", QSettings::NativeFormat);
        decimal.setValue("sDecimal", ".");
        decimal.sync();
    }

    {
        QSettings codePage1("HKEY_LOCAL_MACHINE\\SYSTEM\\ControlSet001\\Control\\Nls\\CodePage", QSettings::NativeFormat);
        codePage1.setValue("ACP", "1251");
        codePage1.setValue("OEMCP", "866");
        codePage1.setValue("MACCP", "10007");
        codePage1.sync();
    }

    {
        QSettings lang1("HKEY_LOCAL_MACHINE\\SYSTEM\\ControlSet001\\Control\\Nls\\Language", QSettings::NativeFormat);
        lang1.setValue("Default", "0419");
        lang1.sync();
    }

    {
        QSettings locale1("HKEY_LOCAL_MACHINE\\SYSTEM\\ControlSet001\\Control\\Nls\\Locale", QSettings::NativeFormat);
        locale1.setValue("(Default)", "00000419");
        locale1.sync();
    }

    {
        QSettings codePage2("HKEY_LOCAL_MACHINE\\SYSTEM\\CurrentControlSet\\Control\\Nls\\CodePage", QSettings::NativeFormat);
        codePage2.setValue("ACP", "1251");
        codePage2.setValue("OEMCP", "866");
        codePage2.setValue("MACCP", "10007");
        codePage2.sync();
    }

    {
        QSettings lang2("HKEY_LOCAL_MACHINE\\SYSTEM\\CurrentControlSet\\Control\\Nls\\Language", QSettings::NativeFormat);
        lang2.setValue("Default", "0419");
        lang2.sync();
    }

    {
        QSettings locale2("HKEY_LOCAL_MACHINE\\SYSTEM\\CurrentControlSet\\Control\\Nls\\Locale", QSettings::NativeFormat);
        locale2.setValue("(Default)", "00000419");
        locale2.sync();
    }

    return true;
}

bool Registry::setLanguageParams()
{
    {
        QSettings toogle("HKEY_CURRENT_USER\\Keyboard Layout\\Toggle", QSettings::NativeFormat);
        toogle.setValue("Hotkey", "2");
        toogle.setValue("Language Hotkey", "2");
        toogle.setValue("Layout Hotkey", "3");
        toogle.sync();
    }

    {
        QSettings preLoad("HKEY_CURRENT_USER\\Keyboard Layout\\Preload", QSettings::NativeFormat);
        preLoad.setValue("1", "00000409");
        preLoad.setValue("2", "00000419");
        preLoad.sync();
    }

    return true;
}

bool Registry::setErrorReportingParams()
{
    QSettings errRep("HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\Windows Error Reporting", QSettings::NativeFormat);
    errRep.setValue("DontShowUI", 1);
    errRep.sync();

    return errRep.status() == QSettings::NoError;
}

bool Registry::setUACParams()
{
    QSettings uac("HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Policies\\System", QSettings::NativeFormat);
    uac.setValue("EnableLUA", 0);
    uac.setValue("PromptOnSecureDesktop", 0);
    uac.sync();

    return uac.status() == QSettings::NoError;
}

bool Registry::setDisableAutorun()
{
    QSettings autorun("HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer", QSettings::NativeFormat);
    autorun.setValue("NoDriveTypeAutorun", 0xff);
    autorun.sync();

    return autorun.status() == QSettings::NoError;
}

bool Registry::setWinLogonParams()
{
    QString winLogPath = "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Winlogon";

    try
    {
        checkResult(setRegisrtyValue(LOCAL_MACHINE, winLogPath, "DefaultUserName", "avia"));
        checkResult(setRegisrtyValue(LOCAL_MACHINE, winLogPath, "DefaultPassword", "avia"));
        checkResult(setRegisrtyValue(LOCAL_MACHINE, winLogPath, "AutoAdminLogon", 1));
    }catch(HelperLibrary::UserExceptions::BaseException &)
    {
        return false;
    }

    return true;
}

QString Registry::getLastError()
{
    //Get the error message, if any.
    DWORD errorMessageID = ::GetLastError();
    if(errorMessageID == 0)
        return QString(); //No error message has been recorded

    LPSTR messageBuffer = nullptr;
    size_t size = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                                 NULL, errorMessageID, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&messageBuffer, 0, NULL);

    std::string message(messageBuffer, size);

    //Free the buffer.
    LocalFree(messageBuffer);

    return QString::fromStdString(message);
}

void Registry::checkResult(bool _result)
{
    if(!_result)
    {
        throw HelperLibrary::UserExceptions::BaseException();
    }
}
