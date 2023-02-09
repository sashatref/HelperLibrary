#pragma once

#include <QObject>
#include <QDataStream>
#include <QVariant>

#include <QVector>
#include <helperLibrary/setgetMacro.h>


class MyClass : public IGadget
{
    Q_GADGET
public:
    DEFINE_MO
    buildPropertyD(int, field1, 10)
    buildPropertyD(QString, field2, "hello")
    buildPropertyD(double, field3, 5.6)
    buildPropertyD(bool, field4, false)
    buildPropertyP(QDate, field5)

    bool operator ==(const MyClass &other) const;
    bool operator !=(const MyClass &other) const;
    bool operator <(const MyClass &other) const;

    friend QDataStream &operator <<(QDataStream &in, const MyClass &_obj)
    {
        QVariantMap m;
        m["field1"] = QVariant::fromValue(_obj.m_field1);
        m["field2"] = QVariant::fromValue(_obj.m_field2);
        m["field3"] = QVariant::fromValue(_obj.m_field3);
        m["field4"] = QVariant::fromValue(_obj.m_field4);
        m["field5"] = QVariant::fromValue(_obj.m_field5);
        in << m;
        return in;
    }

    template <class T>
    static void convert(const QVariant &_val, T &result)
    {
        result = _val.value<T>();
    }

    friend QDataStream &operator >>(QDataStream &out, MyClass &_obj)
    {
        QVariantMap m;
        out >> m;
        convert(m["field1"], _obj.m_field1);
        convert(m["field2"], _obj.m_field2);
        convert(m["field3"], _obj.m_field3);
        convert(m["field4"], _obj.m_field4);
        convert(m["field5"], _obj.m_field5);

        qRegisterMetaTypeStreamOperators<QList<MyClass>>("QList<MyClass>");
        qRegisterMetaTypeStreamOperators<QVector<MyClass>>("QVector<MyClass>");

        return out;
    }

    static QString toString(const MyClass &_value);

    static void registerType();
};

namespace Randomizer
{
    void rand(MyClass &v);
}

namespace JsonUtils
{
    QVariant toVariant(const MyClass &v);
    void fromVariant(const QVariant &_variant, MyClass &_value);
}


Q_DECLARE_METATYPE(MyClass)
Q_DECLARE_METATYPE(QList<MyClass>)
