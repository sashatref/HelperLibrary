#pragma once

#include "../simplecrypt.h"
#include <QDate>

namespace HelperLibraryNS
{

class HELPERLIBRARY_EXPORT AppLocker
{
public:
    struct LicenseFailInfo
    {
        QString machineGuid;
        QString appName;
        QString failReason;
    };

    struct LicenseInfo
    {
        QString machineGuid;
        QString appName;
        QDate expired;
    };

    enum LicenseResult
    {
        lExpired,
        lNoLicenseFile,
        lFailedReadLecenseFile,
        lWrongMachineGuid,
        lWrongAppName,
        lSuccess
    };

    static QString licenseResultToString(LicenseResult _res);

    AppLocker();

    QString getMachineGuid();

    LicenseResult checkLicense();

    void writeLicenseFail(LicenseResult _failReason);

    bool generateLicense(const QString &_filePath, const LicenseInfo &_licenseInfo);

    LicenseFailInfo loadLicenseFailFile(const QString &_filePath);
    LicenseInfo loadLicenseFile(const QString &_filePath);
private:
    SimpleCrypt m_crypt;
    QString m_licensePath;
    QString m_licenseFailPath;

};

}
