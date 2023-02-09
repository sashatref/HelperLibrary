#include "VariantMapHelper.h"

namespace GadgetHelper
{

VariantMapHelper::VariantMapHelper()
{

}

VariantMapHelper::~VariantMapHelper()
{

}

QVariantList VariantMapHelper::toList(const QVariantList &_gadgetList)
{
    QVariantList vList;

    for(const auto &item : _gadgetList)
    {
        const IGadget *igad = item.value<IGadget*>();
        QVariantMap vMap = toMap(igad);
        vList << vMap;
    }

    return vList;
}

QVariantMap VariantMapHelper::toMap(const QVariant &_gadgetItem)
{
    const IGadget *igad = _gadgetItem.value<IGadget*>();
    return toMap(igad);
}

QVariantMap VariantMapHelper::toMap(const IGadget *_gadget, const QStringList &_fields)
{
    QVariantMap out;

    if(_gadget == nullptr) return out;

    const QMetaObject *mo = _gadget->getMetaObject();

    QStringList props = _fields.isEmpty() ? _gadget->getPropertyNameList() : _fields;
    for(int i = 0 ; i < props.size(); i++)
    {
        int propIndex = mo->indexOfProperty(props[i].toStdString().c_str());
        QMetaProperty property = mo->property(propIndex);
        QVariant val = _gadget->getProperty(props.at(i));

        if(property.isEnumType())
        {
            if(val.canConvert<int>())
            {
                val.convert(qMetaTypeId<int>());
            }
        }

        out[props.at(i)] = val;
    }

    return out;
}

void VariantMapHelper::fromMap(IGadget *_gadget, const QVariantMap &_props)
{
    if(_gadget == nullptr) return;
    const QMetaObject *mo = _gadget->getMetaObject();

    for(auto it = _props.begin(); it != _props.end(); ++it)
    {
        int propIndex = mo->indexOfProperty(it.key().toStdString().c_str());
        QVariant newValue = it.value();

        QMetaProperty prop = mo->property(propIndex);
        if(prop.isEnumType())
        {
            newValue.convert(qMetaTypeId<int>());
        }

        _gadget->setProperty(it.key(), newValue);
    }
}

}
