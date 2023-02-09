#include "autostartwrapper.h"

#include <QSettings>

namespace HelperLibraryNS
{

AutoStartWrapper::AutoStartWrapper(const QString &_appName, const QStringList &_args):
    m_appName(_appName),
    m_args(_args)
{

}

void AutoStartWrapper::setAppName(const QString &_appName)
{
    m_appName = _appName;
}

void AutoStartWrapper::setArgs(const QStringList &_args)
{
    m_args = _args;
}

QString AutoStartWrapper::getAutoStartParam() const
{
    QSettings autorun(regEditPath(), QSettings::NativeFormat);
    return autorun.value(m_appName, "").toString();
}

bool AutoStartWrapper::checkForAutoStart() const
{
    return !getAutoStartParam().isEmpty();
}

void AutoStartWrapper::setAutoStart(bool _enable)
{
    QSettings autorun(regEditPath(), QSettings::NativeFormat);
    if(_enable)
    {
        QString appPath = QDir::toNativeSeparators(QCoreApplication::applicationFilePath());
        autorun.setValue(m_appName, appPath + " " + m_args.join(" "));
    }
    else
    {
        autorun.remove("SimpleWebServer");
    }

    autorun.sync();
}

QString AutoStartWrapper::regEditPath()
{
    return "HKEY_CURRENT_USER\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run";
}

}

