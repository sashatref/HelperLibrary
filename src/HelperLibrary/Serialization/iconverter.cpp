#include "iconverter.h"

namespace SerializerQt
{

ConverterByFunc::ConverterByFunc(ConverterByFunc::ConvertToString _toString,
                                 ConverterByFunc::ConvertFromString _fromString):
    m_toString      (_toString),
    m_fromString    (_fromString)
{

}

QString ConverterByFunc::toString(const QVariant &_v, QString &_typeName) const
{
    return m_toString(_v, _typeName);
}

QVariant ConverterByFunc::fromString(const QString &_in) const
{
    return m_fromString(_in);
}

}
