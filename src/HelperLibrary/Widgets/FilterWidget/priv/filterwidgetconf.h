#pragma once

namespace HelperLibraryNS
{

class FilterWidgetConf
{
    Q_DECLARE_TR_FUNCTIONS(FilterWidgetConf)
public:
    QRegExp::PatternSyntax pattern = QRegExp::Wildcard;
    Qt::CaseSensitivity caseSensitivity = Qt::CaseInsensitive;

    QVariant save() const
    {
        QVariantMap out;

        out["pattern"] = (int)pattern;
        out["caseSensitivity"] = (int)caseSensitivity;

        return out;
    }

    void load(const QVariant &_v)
    {
        const QVariantMap map = _v.toMap();

        pattern = (QRegExp::PatternSyntax)map.value("pattern", QRegExp::Wildcard).toInt();
        caseSensitivity = (Qt::CaseSensitivity)map.value("caseSensitivity", Qt::CaseInsensitive).toInt();
    }

    QString patternToString() const
    {
        QMap<QRegExp::PatternSyntax, QString> m = {
            {QRegExp::Wildcard, "Wildcard" },
            {QRegExp::RegExp, "RegExp" },
            {QRegExp::FixedString, tr("Обычный поиск") }
        };

        return m.value(pattern, "Wildcard");
    }
};

}

