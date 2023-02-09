#include "myclass.h"

#include <helperLibrary/functions.h>
#include <helperLibrary/helperscontainter.h>
#include <helperLibrary/converterfunctions.h>
#include <QFileDialog>

bool MyClass::operator ==(const MyClass &other) const
{
    if(m_field1 != other.m_field1) return false;
    if(m_field2 != other.m_field2) return false;
    if(m_field3 != other.m_field3) return false;
    if(m_field4 != other.m_field4) return false;
    if(m_field5 != other.m_field5) return false;
    return true;
}

bool MyClass::operator !=(const MyClass &other) const
{
    return !operator ==(other);
}

bool MyClass::operator <(const MyClass &other) const
{
    if(m_field1 < other.m_field1) return true;
    if(m_field2 < other.m_field2) return true;
    if(m_field3 < other.m_field3) return true;
    if(m_field4 < other.m_field4) return true;
    if(m_field5 < other.m_field5) return true;
    return false;
}


QString MyClass::toString(const MyClass &_value)
{
    QString result;
    result = QString::number(_value.m_field1)
            + " | "
            + _value.m_field2
            + " | "
            + QString::number(_value.m_field3)
            + " | "
            + QString::number(_value.m_field4);
            + " | "
            + _value.m_field5.toString("dd.MM.yyyy");
    return result;
}

void MyClass::registerType()
{
    if(!QMetaType::hasRegisteredComparators<MyClass>())
    {
        QMetaType::registerComparators<MyClass>();
    }

    GadgetHelper::registerToIGadgetConverter<MyClass>();
    QMetaType::registerConverter<MyClass, QString>(&toString);
}

void Randomizer::rand(MyClass &v)
{
    rand(v.m_field1);
    rand(v.m_field2);
    rand(v.m_field3);
    rand(v.m_field4);
    rand(v.m_field5);
}

QVariant JsonUtils::toVariant(const MyClass &v)
{
    return QVariantMap {
        { "field1", toVariant(v.m_field1) },
        { "field2", toVariant(v.m_field2) },
        { "field3", toVariant(v.m_field3) },
        { "field4", toVariant(v.m_field4) },
        { "field5", toVariant(v.m_field5) },
    };
}

void JsonUtils::fromVariant(const QVariant &_variant, MyClass &_value)
{
    const QVariantMap m = _variant.toMap();

    fromVariant(m.value("field1"), _value.m_field1);
    fromVariant(m.value("field2"), _value.m_field2);
    fromVariant(m.value("field3"), _value.m_field3);
    fromVariant(m.value("field4"), _value.m_field4);
    fromVariant(m.value("field5"), _value.m_field5);
}
