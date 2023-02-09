#pragma once

#include "../export.h"

namespace SerializerQt
{

class HELPERLIBRARY_EXPORT IConverter
{
public:
    IConverter()
    {

    }

    virtual ~IConverter()
    {

    }

    virtual QString toString(const QVariant &_v, QString &_typeName) const = 0;
    virtual QVariant fromString(const QString &_in) const = 0;
};

class HELPERLIBRARY_EXPORT ConverterByFunc : public IConverter
{
public:
    typedef std::function<QString(const QVariant&, QString&)> ConvertToString;
    typedef std::function<QVariant(const QString&)> ConvertFromString;

    ConverterByFunc(ConvertToString _toString, ConvertFromString _fromString);

    virtual QString toString(const QVariant &_v, QString &_typeName) const override;
    virtual QVariant fromString(const QString &_in) const override;

private:
    ConvertToString m_toString;
    ConvertFromString m_fromString;
};

}

