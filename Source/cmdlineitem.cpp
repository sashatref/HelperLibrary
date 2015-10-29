#include "cmdlineitem.h"

CmdLineItem::CmdLineItem(const QString &_name, bool _isRequiried, bool _isMultiValue, bool _canBeEmpty, const QString &_description) :
    m_name(_name),
    m_isRequiried(_isRequiried),
    m_isMultiValue(_isMultiValue),
    m_canBeEmpty(_canBeEmpty),
    m_value(),
    m_isFounded(false),
    m_description(_description)
{}

const QStringList &CmdLineItem::getValue() const
{
    return m_value;
}
