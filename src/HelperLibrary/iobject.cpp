#include "project_pch.h"
#include "iobject.h"

#include "Exceptions/userexception.h"

namespace ObjectHelper
{

QObject *getObject(QVariant &_value, bool _throwException)
{
    QObject *obj = _value.value<QObject*>();
    if(!obj)
    {
        if(_throwException)
        {
            throw HelperLibrary::UserExceptions::ToObjectException(_value.typeName());
        }
    }

    return obj;
}

QObject *getObject(const QVariant &_value, bool _throwException)
{
    QObject *obj = _value.value<QObject*>();
    if(!obj)
    {
        if(_throwException)
        {
            throw HelperLibrary::UserExceptions::ToObjectException(_value.typeName());
        }
    }

    return obj;
}

}

