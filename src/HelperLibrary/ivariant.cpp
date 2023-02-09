#include "ivariant.h"



void VariantHelper::setProperty(QVariant &_object, const QString &_propertyName, const QVariant &_propertyValue)
{
    QObject *object = ObjectHelper::getObject(_object, false);
    IGadget *gadget = GadgetHelper::getIGadget(_object, false);

    if(gadget)
    {
        gadget->setProperty(_propertyName, _propertyValue);
    } else if(object)
    {
        object->setProperty(_propertyName.toStdString().c_str(), _propertyValue);
    }
}

QVariant VariantHelper::getProperty(const QVariant &_object, const QString &_propertyName)
{
    QObject *object = ObjectHelper::getObject(_object, false);
    IGadget *gadget = GadgetHelper::getIGadget(_object, false);
    QVariant val;

    if(gadget)
    {
        val = gadget->getProperty(_propertyName);
    } else if(object)
    {
        val = object->property(_propertyName.toStdString().c_str());
    }

    return val;
}

const QMetaObject *VariantHelper::getMetaObject(const QVariant &_object)
{
    QObject *object = ObjectHelper::getObject(_object, false);
    IGadget *gadget = GadgetHelper::getIGadget(_object, false);

    const QMetaObject *mo = 0;
    if(gadget)
    {
        mo = gadget->getMetaObject();
    } else if(object)
    {
        mo = object->metaObject();
    }

    return mo;
}
