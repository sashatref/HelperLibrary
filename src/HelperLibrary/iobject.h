#pragma once

#include <QObject>
#include <QVariant>
#include <QMetaMethod>

#include "export.h"

namespace ObjectHelper
{

class IPrivateObjectBase : public QObject
{
    Q_OBJECT
public:
    Q_INVOKABLE virtual QObject* getPrivateObject() = 0;
};


template<class T>
T* castObject(QObject *const _obj)
{
    T *base = dynamic_cast<T*>(_obj);
    if(base) return base;

    const QMetaObject *mo = _obj->metaObject();
    int index = mo->indexOfMethod("getPrivateObject()");

    if(index != -1)
    {
        QObject *subObject = 0;
        mo->method(index).invoke(_obj,
                                 Qt::DirectConnection,
                                 Q_RETURN_ARG(QObject*, subObject));

        base = dynamic_cast<T*>(subObject);
    }
    return base;
}

QObject HELPERLIBRARY_EXPORT *getObject(QVariant &_value, bool _throwException = true);
QObject HELPERLIBRARY_EXPORT *getObject(const QVariant &_value, bool _throwException = true);

//регистрирует конвертер к QObject* в метасистеме
template<class T>
void registerToQObjectConverter()
{
    if(!QMetaType::hasRegisteredConverterFunction<T, QObject*>())
    {
        QMetaType::registerConverter<T, QObject*>([](const T &_value) -> QObject*
        {
            return const_cast<T*>(&_value);
        });
    }
}

}
