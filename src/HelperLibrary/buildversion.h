#pragma once

#include "export.h"

class HELPERLIBRARY_EXPORT BuildVersion
{
public:
    BuildVersion(int _major = 1, int _minor = 0, int _maintenance = 0, int _build = 1);

    int m_major;
    int m_minor;
    int m_maintenance;
    int m_build;

    QString toString(const QString &_delim = ".") const;

    static BuildVersion getModuleVersion(const QString &_filePath);
    static BuildVersion getCurrentAppVersion();
};

bool HELPERLIBRARY_EXPORT operator !=(const BuildVersion &_item1, const BuildVersion &_item2);
bool HELPERLIBRARY_EXPORT operator ==(const BuildVersion &_item1, const BuildVersion &_item2);
bool HELPERLIBRARY_EXPORT operator <(const BuildVersion &_item1, const BuildVersion &_item2);
bool HELPERLIBRARY_EXPORT operator >(const BuildVersion &_item1, const BuildVersion &_item2);
bool HELPERLIBRARY_EXPORT operator >=(const BuildVersion &_item1, const BuildVersion &_item2);
bool HELPERLIBRARY_EXPORT operator <=(const BuildVersion &_item1, const BuildVersion &_item2);

