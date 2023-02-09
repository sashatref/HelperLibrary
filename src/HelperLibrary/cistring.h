#pragma once

#include "export.h"

class HELPERLIBRARY_EXPORT CIString : public QString
{
public:
    CIString(const QString &_str = "");

    CIString(const char *_ch);

    bool operator <(const CIString &_other) const;
    bool operator ==(const QString &_other) const;
};

uint HELPERLIBRARY_EXPORT qHash(const CIString &str, uint seed);

namespace StdHelper
{

struct HELPERLIBRARY_EXPORT StringCompIgnoreCase {
    bool operator()(const QString& a, const QString& b) const;
};

}
