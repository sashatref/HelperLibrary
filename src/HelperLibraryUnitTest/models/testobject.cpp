#include "testobject.h"

#include <QSize>

#include <helperLibrary/converterfunctions.h>
#include <helperLibrary/functions.h>

bool TestObject::operator ==(const TestObject &other) const
{
    if(m_intValue != other.m_intValue) {qDebug() << "m_intValue not equal"; return false;}
    if(m_boolValue != other.m_boolValue) {qDebug() << "m_boolValue not equal"; return false;}
    if(!qFuzzyCompare(m_doubleValue, other.m_doubleValue)) {qDebug() << "m_doubleValue not equal"; return false;}
    if(m_stringValue != other.m_stringValue) {qDebug() << "m_stringValue not equal"; return false;}
    if(m_dateValue != other.m_dateValue) {qDebug() << "m_dateValue not equal"; return false;}
    if(m_dateTimeValue != other.m_dateTimeValue) {qDebug() << "m_dateTimeValue not equal"; return false;}
    if(m_myClassList != other.m_myClassList) {qDebug() << "m_myClassList not equal"; return false;}
    if(m_stringListValue != other.m_stringListValue) {qDebug() << "m_stringListValue not equal"; return false;}
    if(m_myClassValue != other.m_myClassValue) {qDebug() << "m_myClassValue not equal"; return false;}
    if(m_myClassMap != other.m_myClassMap) {qDebug() << "m_myClassMap not equal"; return false;}
    if(m_variantList != other.m_variantList) {qDebug() << "m_variantList not equal"; return false;}

    return true;
}

bool TestObject::operator !=(const TestObject &other) const
{
    bool res = operator ==(other);
    return !res;
}

void TestObject::registerType()
{
    GadgetHelper::registerToIGadgetConverter<TestObject>();

    QMetaType::registerEqualsComparator<TestObject>();
    Converters::registerToListConverter<MyClass>();
    Converters::registerToListConverter<TestObject>();
    Converters::registerVariantMapToMapConverter<QString, MyClass>();
}

const QMetaObject *TestObject::getMetaObject() const
{
    return &staticMetaObject;
}

void Randomizer::rand(TestObject &v)
{
    rand(v.m_boolValue);
    rand(v.m_dateTimeValue);
    rand(v.m_dateValue);
    rand(v.m_doubleValue);
    randEnum(v.m_enumValue, TestObject::Value1, TestObject::Key3);
    rand(v.m_intValue);
    rand(v.m_myClassList);
    rand(v.m_myClassValue);
    rand(v.m_rect);
    rand(v.m_stringListValue);
    rand(v.m_stringValue);
    rand(v.m_myClassMap);

    v.m_variantList
            << QVariant(10)
            << QVariant("myStr")
            << QVariant(0.5)
            << QStringList({"v1", "v2", "v2"})
            << QVariantMap({ {"key1", "value1"}, {"key2", "value2"} });
}

QVariant JsonUtils::toVariant(const TestObject &v)
{
    return QVariantMap{
        { "rect", toVariant(v.m_rect) },
        { "enumValue", toVariant(v.m_enumValue) },
        { "intValue", toVariant(v.m_intValue) },
        { "boolValue", toVariant(v.m_boolValue) },
        { "doubleValue", toVariant(v.m_doubleValue) },
        { "stringValue", toVariant(v.m_stringValue) },
        { "dateValue", toVariant(v.m_dateValue) },
        { "dateTimeValue", toVariant(v.m_dateTimeValue) },
        { "stringListValue", toVariant(v.m_stringListValue) },
        { "myClassValue", toVariant(v.m_myClassValue) },
        { "myClassList", toVariant(v.m_myClassList) },
        { "myClassMap", toVariant(v.m_myClassMap) },
        { "variantList", toVariant(v.m_variantList) }
    };
}

void JsonUtils::fromVariant(const QVariant &_variant, TestObject &_value)
{
    const QVariantMap m = _variant.toMap();

    fromVariant(m.value("rect"), _value.m_rect);
    fromVariant(m.value("enumValue"), _value.m_enumValue);
    fromVariant(m.value("intValue"), _value.m_intValue);
    fromVariant(m.value("boolValue"), _value.m_boolValue);
    fromVariant(m.value("doubleValue"), _value.m_doubleValue);
    fromVariant(m.value("stringValue"), _value.m_stringValue);
    fromVariant(m.value("dateValue"), _value.m_dateValue);
    fromVariant(m.value("dateTimeValue"), _value.m_dateTimeValue);
    fromVariant(m.value("stringListValue"), _value.m_stringListValue);
    fromVariant(m.value("myClassValue"), _value.m_myClassValue);
    fromVariant(m.value("myClassList"), _value.m_myClassList);
    fromVariant(m.value("myClassMap"), _value.m_myClassMap);
    fromVariant(m.value("variantList"), _value.m_variantList);
}

void JsonUtils::fromVariant(const QVariant &_variant, TestObject::MyEnum &_value)
{
    _value = static_cast<TestObject::MyEnum>(_variant.toInt());
}
