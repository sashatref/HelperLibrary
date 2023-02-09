#pragma once

#include <HelperLibrary/igadget.h>

#include <QDate>
#include <QDateTime>
#include <QFont>
#include <QVector>
#include <QDebug>
#include <QVariant>
#include <QUrl>
#include <QDir>
#include <QPixmap>
#include <time.h>
#include <climits>

#include <helperLibrary/setgetMacro.h>
#include <helperLibrary/functions.h>

#include "myclass.h"

using MyClassMap = QMap<QString, MyClass>;

class TestObject : public IGadget
{
    Q_GADGET
public:
    enum MyEnum
    {
        Value1 = 1,
        Valu2 = 5,
        Key3 = 128
    };
    Q_ENUM(MyEnum)

    enum Option
    {
        None = 0,
        OptionA = 1,    // 000001
        OptionB = 2,    // 000010
        OptionC = 4,    // 000100
        OptionD = 8,    // 001000
        OptionE = 16,   // 010000
        OptionF = 32,   // 100000
        All = 63        // 111111
    };

    Q_DECLARE_FLAGS(Options, Option)
    Q_FLAG(Options)

    buildPropertyP(QRect, rect)
//    buildPropertyP(Options, flagsValue)
    buildPropertyP(MyEnum, enumValue)
    buildPropertyP(int, intValue)
    buildPropertyP(bool, boolValue)
    buildPropertyP(double, doubleValue)
    buildPropertyP(QString, stringValue)
    buildPropertyP(QDate, dateValue)
    buildPropertyP(QDateTime, dateTimeValue)
    buildPropertyP(QStringList, stringListValue)
    buildPropertyP(MyClass, myClassValue)
    buildPropertyP(QList<MyClass>, myClassList)
    buildPropertyP(MyClassMap, myClassMap)
    buildPropertyP(QVariantList, variantList)

    bool operator ==(const TestObject &other) const;
    bool operator !=(const TestObject &other) const;


    static void registerType();
public:
    const QMetaObject *getMetaObject() const;
};

namespace Randomizer
{
    void rand(TestObject &v);
}

namespace JsonUtils
{
    QVariant toVariant(const TestObject &v);
    void fromVariant(const QVariant &_variant, TestObject &_value);
    void fromVariant(const QVariant &_variant, TestObject::MyEnum &_value);
}

Q_DECLARE_METATYPE(TestObject)
Q_DECLARE_OPERATORS_FOR_FLAGS(TestObject::Options)
Q_DECLARE_METATYPE(MyClassMap)

