#include "SimpleTextFilter.h"

namespace HelperLibraryNS
{

bool SimpleTextFilter::checkText(const QString &_text) const
{
    if(enabled == false)
    {
        return true;
    }

    QRegExp rx;
    rx.setCaseSensitivity(sensitivity);
    rx.setPatternSyntax(pattern);

    for(auto &rule : rules)
    {
        rx.setPattern(rule);
        bool res = rx.exactMatch(_text);

        if(checkType == WhiteList)
        {
            if(res)
            {
                return true;
            }
        } else if(checkType == BlackList)
        {
            if(res)
            {
                return false;
            }
        }
    }

    return checkType == BlackList;
}

QVariant SimpleTextFilter::save() const
{
    QVariantMap m = {
        { "enabled", enabled },
        { "checkType", checkType },
        { "rules", rules },
        { "sensitivity", sensitivity },
        { "pattern", pattern }
    };
    return m;
}

void SimpleTextFilter::load(const QVariant &_v)
{
    const QVariantMap m = _v.toMap();
    enabled = m.value("enabled", false).toBool();
    checkType = (CheckType)m.value("checkType", WhiteList).toInt();
    rules = m.value("rules").toStringList();
    sensitivity = (Qt::CaseSensitivity)m.value("sensitivity", Qt::CaseInsensitive).toInt();
    pattern = (QRegExp::PatternSyntax)m.value("pattern", QRegExp::Wildcard).toInt();
}

}
