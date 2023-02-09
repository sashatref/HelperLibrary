#include "uilanginfo.h"
#include "../anymacro.h"


namespace HelperLibrary
{

UILangInfo::UILangInfo(const QString &_fullName,
                       const QString &_shortName,
                       const QString &_iconPath):
    m_fullName(_fullName),
    m_shortName(_shortName),
    m_iconPath(_iconPath)
{

}

void UILangInfo::registerType()
{
    GadgetHelper::registerToIGadgetConverter<UILangInfo>();
}

const QMetaObject *UILangInfo::getMetaObject() const
{
    return &staticMetaObject;
}

QDebug operator<<(QDebug _debug, const UILangInfo &_value)
{
    _debug
            << _value.m_fullName
            << " "
            << _value.m_shortName
            << " "
            << _value.m_iconPath;

    return _debug;
}

}
