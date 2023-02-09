#include "AppLocker.h"

namespace HelperLibraryNS
{

QString AppLocker::licenseResultToString(AppLocker::LicenseResult _res)
{
    static QMap<AppLocker::LicenseResult, QString> m = {
        { lExpired, "lExpired" },
        { lNoLicenseFile, "lNoLicenseFile" },
        { lFailedReadLecenseFile, "lFailedReadLecenseFile" },
        { lWrongMachineGuid, "lWrongGuid" },
        { lWrongAppName, "lWrongAppName" },
        { lSuccess, "lSuccess" },
    };

    return m.value(_res, "Unknown");
}

AppLocker::AppLocker()
{
    m_crypt.setKey(0x0c3ad3a4a2b9f013);
    m_licensePath = makePathAbsolute("license.dat");
    m_licenseFailPath = makePathAbsolute("license.FAILED.dat");
}

QString AppLocker::getMachineGuid()
{
#ifdef Q_OS_WIN
     QSettings s("HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Cryptography", QSettings::Registry64Format);
     return s.value("MachineGuid").toString();
#else
    return {};
#endif
}

AppLocker::LicenseResult AppLocker::checkLicense()
{
    if(!QFile::exists(m_licensePath))
    {
        return lNoLicenseFile;
    }

    LicenseInfo lInfo = loadLicenseFile(m_licensePath);
    if(QDate::currentDate().daysTo(lInfo.expired) < 1)
    {
        return lExpired;
    }

    if(lInfo.machineGuid.isEmpty() || lInfo.machineGuid != getMachineGuid())
    {
        return lWrongMachineGuid;
    }

    if(lInfo.appName != qApp->applicationName())
    {
        return lWrongAppName;
    }

    return lSuccess;
}

void AppLocker::writeLicenseFail(AppLocker::LicenseResult _failReason)
{
    QVariantMap m = {
        { "MachineGuidFailed", getMachineGuid() },
        { "AppName", qApp->applicationName() },
        { "FailReason", licenseResultToString(_failReason) }
    };

    if(!m_crypt.cryptJson(m, m_licenseFailPath))
    {
        qCWarning(extendApp) << QString("Can't write license.FAILED file [%1]").arg(m_licenseFailPath);
        return;
    }
}

bool AppLocker::generateLicense(const QString &_filePath, const LicenseInfo &_licenseInfo)
{
    QVariantMap m = {
        { "MachineGuid", _licenseInfo.machineGuid },
        { "Expired", QDate(2020, 1, 1).daysTo(_licenseInfo.expired) },
        { "AppName", _licenseInfo.appName }
    };

    return m_crypt.cryptJson(m, _filePath);
}

AppLocker::LicenseFailInfo AppLocker::loadLicenseFailFile(const QString &_filePath)
{
    QVariantMap v = m_crypt.decryptJson(_filePath).toMap();

    AppLocker::LicenseFailInfo out;
    out.appName = v.value("AppName").toString();
    out.machineGuid = v.value("MachineGuidFailed").toString();
    out.failReason = v.value("FailReason").toString();
    return out;
}

AppLocker::LicenseInfo AppLocker::loadLicenseFile(const QString &_filePath)
{
    QVariantMap m = m_crypt.decryptJson(_filePath).toMap();

    AppLocker::LicenseInfo out;
    out.machineGuid = m["MachineGuid"].toString();
    out.appName = m.value("AppName").toString();
    out.expired = QDate(2020, 1, 1).addDays(m.value("Expired", 0).toInt());
    return out;
}

}
