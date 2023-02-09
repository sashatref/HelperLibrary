#pragma once

#include "export.h"

#include <QStringList>
#include <QRegExp>

namespace HelperLibraryNS
{

class HELPERLIBRARY_EXPORT SimpleTextFilter
{
public:
    enum CheckType
    {
        WhiteList = 0,
        BlackList
    };

    bool enabled = false;
    CheckType checkType = WhiteList;
    QStringList rules;
    Qt::CaseSensitivity sensitivity = Qt::CaseInsensitive;
    QRegExp::PatternSyntax pattern = QRegExp::Wildcard;

    bool checkText(const QString &_text) const;

    QVariant save() const;
    void load(const QVariant &_v);
};

}

