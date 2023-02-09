#pragma once

#include "iobject.h"
#include "igadget.h"
#include "export.h"

/*!
 *Набор методов, которые пытаются привести QVariant к QObject и IGadget
 * и если один из них обнаружен, то выполнить какие-то действия
 */

namespace VariantHelper
{
    void HELPERLIBRARY_EXPORT setProperty(QVariant &_object,
                                          const QString &_propertyName,
                                          const QVariant &_propertyValue);

    QVariant HELPERLIBRARY_EXPORT getProperty(const QVariant &_object,
                                              const QString &_propertyName);

    const QMetaObject HELPERLIBRARY_EXPORT *getMetaObject(const QVariant &_object);

    template<class T>
    T* castObject(const QVariant &_val)
    {
        QObject *object = ObjectHelper::getObject(_val, false);
        IGadget *gadget = GadgetHelper::getIGadget(_val, false);

        T *base = 0;

        if(gadget)
        {
            base = GadgetHelper::castObject<T>(gadget);
        } else if(object)
        {
            base = ObjectHelper::castObject<T>(object);
        }

        return base;
    }
}

