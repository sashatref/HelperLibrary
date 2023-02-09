#ifndef CONVERFUNCIMPL_H
#define CONVERFUNCIMPL_H

#include "iconverter.h"

namespace SerializerQt
{
    class ConverterInt : public IConverter
    {
    public:
        virtual QString toString(const QVariant &_v, QString &_typeName) const override;
        virtual QVariant fromString(const QString &_in) const override;
    };

    class ConverterString : public IConverter
    {
    public:
        virtual QString toString(const QVariant &_v, QString &_typeName) const override;
        virtual QVariant fromString(const QString &_in) const override;
    };

    class ConverterDouble : public IConverter
    {
    public:
        virtual QString toString(const QVariant &_v, QString &_typeName) const override;
        virtual QVariant fromString(const QString &_in) const override;
    };

    class ConverterBool : public IConverter
    {
    public:
        virtual QString toString(const QVariant &_v, QString &_typeName) const override;
        virtual QVariant fromString(const QString &_in) const override;
    };

    class ConverterByteArray : public IConverter
    {
    public:
        virtual QString toString(const QVariant &_v, QString &_typeName) const override;
        virtual QVariant fromString(const QString &_in) const override;

    private:
        static QString byteArrayToString(const QByteArray &_data);
        static QByteArray stringToByteArray(const QString &_string);
    };

    class ConverterDate : public IConverter
    {
    public:
        virtual QString toString(const QVariant &_v, QString &_typeName) const override;
        virtual QVariant fromString(const QString &_in) const override;
    };

    class ConverterDateTime : public IConverter
    {
    public:
        virtual QString toString(const QVariant &_v, QString &_typeName) const override;
        virtual QVariant fromString(const QString &_in) const override;
    };

    class ConverterTime : public IConverter
    {
    public:
        virtual QString toString(const QVariant &_v, QString &_typeName) const override;
        virtual QVariant fromString(const QString &_in) const override;
    };

    class ConverterRect : public IConverter
    {
    public:
        virtual QString toString(const QVariant &_v, QString &_typeName) const override;
        virtual QVariant fromString(const QString &_in) const override;
    };

    class ConverterSize : public IConverter
    {
    public:
        virtual QString toString(const QVariant &_v, QString &_typeName) const override;
        virtual QVariant fromString(const QString &_in) const override;
    };

    class ConverterColor : public IConverter
    {
    public:
        virtual QString toString(const QVariant &_v, QString &_typeName) const override;
        virtual QVariant fromString(const QString &_in) const override;
    };

    class ConverterFont : public IConverter
    {
    public:
        virtual QString toString(const QVariant &_v, QString &_typeName) const override;
        virtual QVariant fromString(const QString &_in) const override;
    };

    class ConverterUrl : public IConverter
    {
    public:
        virtual QString toString(const QVariant &_v, QString &_typeName) const override;
        virtual QVariant fromString(const QString &_in) const override;
    };

    class ConverterPoint : public IConverter
    {
    public:
        virtual QString toString(const QVariant &_v, QString &_typeName) const override;
        virtual QVariant fromString(const QString &_in) const override;
    };

    class ConverterPointF : public IConverter
    {
    public:
        virtual QString toString(const QVariant &_v, QString &_typeName) const override;
        virtual QVariant fromString(const QString &_in) const override;
    };
}


#endif // CONVERFUNCIMPL_H
