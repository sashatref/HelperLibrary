#include "buildversion.h"

BuildVersion::BuildVersion(int _major, int _minor, int _maintenance, int _build):
    m_major(_major),
    m_minor(_minor),
    m_maintenance(_maintenance),
    m_build(_build)
{

}

QString BuildVersion::toString(const QString &_delim) const
{
    return (QStringList()
            << QString::number(m_major)
            << QString::number(m_minor)
            << QString::number(m_build)
            << QString::number(m_maintenance)).join(_delim);
}

BuildVersion BuildVersion::getModuleVersion(const QString &_filePath)
{
    BuildVersion prVer;

#ifdef Q_OS_WIN
    DWORD dwHandle, dwLen;
    UINT BufLen;
    LPTSTR lpData;
    VS_FIXEDFILEINFO *pFileInfo;
    dwLen = GetFileVersionInfoSizeA(_filePath.toUtf8(), &dwHandle);
    if (!dwLen)
        return prVer;

    lpData = (LPTSTR)malloc(dwLen);
    if (!lpData)
        return prVer;

    if (!GetFileVersionInfoA(_filePath.toUtf8(), dwHandle, dwLen, lpData))
    {
        free(lpData);
        return prVer;
    }
    if (VerQueryValueA(lpData, "\\", (LPVOID *)&pFileInfo, (PUINT)&BufLen))
    {
        prVer.m_major = HIWORD(pFileInfo->dwFileVersionMS);
        prVer.m_minor = LOWORD(pFileInfo->dwFileVersionMS);
        prVer.m_build = HIWORD(pFileInfo->dwFileVersionLS);
        prVer.m_maintenance = LOWORD(pFileInfo->dwFileVersionLS);
        free(lpData);
        return prVer;
    }
    free(lpData);
#else

#endif
    return prVer;
}

BuildVersion BuildVersion::getCurrentAppVersion()
{
#ifdef Q_OS_WIN
    char moduleName[1024];
    GetModuleFileNameA(0, moduleName, 1024);
    return getModuleVersion(QString(moduleName));
#else
    return getModuleVersion(QString("1.0.0.1"));
#endif
}

bool operator <(const BuildVersion &_item1, const BuildVersion &_item2)
{
    if(_item1.m_major         < _item2.m_major) return true;
    if(_item1.m_major         > _item2.m_major) return false;

    if(_item1.m_minor         < _item2.m_minor) return true;
    if(_item1.m_minor         > _item2.m_minor) return false;

    if(_item1.m_maintenance   < _item2.m_maintenance) return true;
    if(_item1.m_maintenance   > _item2.m_maintenance) return false;

    if(_item1.m_build         < _item2.m_build) return true;
    if(_item1.m_build         > _item2.m_build) return false;

    return false;
}

bool operator >(const BuildVersion &_item1, const BuildVersion &_item2)
{
    if(_item1.m_major         > _item2.m_major) return true;
    if(_item1.m_major         < _item2.m_major) return false;

    if(_item1.m_minor         > _item2.m_minor) return true;
    if(_item1.m_minor         < _item2.m_minor) return false;

    if(_item1.m_maintenance   > _item2.m_maintenance) return true;
    if(_item1.m_maintenance   < _item2.m_maintenance) return false;

    if(_item1.m_build         > _item2.m_build) return true;
    if(_item1.m_build         < _item2.m_build) return false;

    return false;
}

bool operator <=(const BuildVersion &_item1, const BuildVersion &_item2)
{
    if(_item1 == _item2) return true;
    return _item1 < _item2;
}

bool operator >=(const BuildVersion &_item1, const BuildVersion &_item2)
{
    if(_item1 == _item2) return true;
    return _item1 > _item2;
}

bool operator ==(const BuildVersion &_item1, const BuildVersion &_item2)
{
    if(_item1.m_major         != _item2.m_major) return false;
    if(_item1.m_minor         != _item2.m_minor) return false;
    if(_item1.m_maintenance   != _item2.m_maintenance) return false;
    if(_item1.m_build         != _item2.m_build) return false;

    return true;
}

bool operator !=(const BuildVersion &_item1, const BuildVersion &_item2)
{
    return !(_item1 == _item2);
}
