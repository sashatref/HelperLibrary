#include "cistring.h"



CIString::CIString(const QString &_str):
    QString(_str)
{

}

CIString::CIString(const char *_ch):
    QString(_ch)
{

}

bool CIString::operator <(const CIString &_other) const
{
    return toLower() < _other.toLower();
}

bool CIString::operator ==(const QString &_other) const
{
    return (0 == compare(_other, Qt::CaseInsensitive));
}


namespace StdHelper
{

bool StringCompIgnoreCase::operator()(const QString &a, const QString &b) const
{
    return a.toLower() < b.toLower();
}

}

uint qHash(const CIString &str, uint seed) {
    return qHash(str.toLower(), seed);
}
