#include "../serializerexception.h"
#include "simplejsonserializer.h"
#include "igadget.h"

#include <QStack>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonParseError>

namespace SerializerQt
{

class SimpleJsonSerializerPrivate
{
//    enum
//    {
//        FromMap = 0,
//        FromList = 1,
//        Simple = 2
//    };

    friend class SimpleJsonSerializer;
    SimpleJsonSerializer const *q;
    QJsonDocument m_doc;
    QStack<QJsonObject> m_elements;
    QStack<QJsonArray> m_arrays;
//    QStack<int> m_status;

    SimpleJsonSerializerPrivate(SimpleJsonSerializer *_q):
        q(_q)
    {
        QJsonObject root;
        m_elements.push(root);
//        m_status.push(Simple);
    }
};

SimpleJsonSerializer::SimpleJsonSerializer(ActionType _type, ErrorAction _errorAction):
    Serializer(SimpleJson, _type, _errorAction),
    d(new SimpleJsonSerializerPrivate(this))
{

}

SimpleJsonSerializer::~SimpleJsonSerializer()
{
    delete d;
}

bool SimpleJsonSerializer::serialize(const QVariantMap &_valueMap,
                                     const QString &_nodeName,
                                     const QString &_containerType,
                                     const QString &_key)
{
    Q_UNUSED(_valueMap);
    Q_UNUSED(_nodeName);
    Q_UNUSED(_containerType);
    Q_UNUSED(_key);

    return true;
}

bool SimpleJsonSerializer::serialize(const QVariantList &_valueList,
                                     const QString &_nodeName,
                                     const QString &_containerType,
                                     const QString &_key)
{
    Q_UNUSED(_containerType);
    Q_UNUSED(_key);

//    d->m_status.push(SimpleJsonSerializerPrivate::FromList);

    d->m_arrays.push(QJsonArray());

    for(int i = 0 ; i < _valueList.size(); i++)
    {
        serialize(_valueList.at(i), "");
    }
    d->m_elements.last()[_nodeName] = d->m_arrays.pop();

//    d->m_status.pop();

    return true;
}

bool SimpleJsonSerializer::serialize(const QVariant &_value, const QString &_nodeName, const QString &_key)
{
    if(!_value.isValid()) return false;
    QJsonObject subElement;

    if(_value.canConvert<QVariantList>())
    {
        return serialize(_value.value<QVariantList>(), _nodeName, _value.typeName(), _key);
    }

    if(_value.canConvert<QVariantMap>())
    {
        return serialize(_value.value<QVariantMap>(), _nodeName, _value.typeName(), _key);
    }

    if(serializeKnownVariant(_value, _nodeName, _key)) return true;

    IGadget *gad = _value.value<IGadget*>();
    if(!gad)
    {
        switch(getErrorAction())
        {
        case IgnoreErrors:
            qWarning() << "Unsupported type <" << _value.userType() << ">";
            return false;
            break;
        case ExceptOnError:
            throw ToObjectException(_value.typeName());
            break;
        }
    }

    if(!_nodeName.isEmpty())
    {
        d->m_elements.push(subElement);
    }

//    if(d->m_status.last() == SimpleJsonSerializerPrivate::FromList)
//    {
//        d->m_elements.push(subElement);
//    }

//    d->m_status.push(SimpleJsonSerializerPrivate::Simple);

    //получаем список свойств, которые необходимо исключить из сериализации
//    QStringList excludeProperties;
//    ISerializeBase *base = getIBase(gad);
//    if(base)
//    {
//        base->excludeSerializer(excludeProperties);
//    }

    QMap<QString, SerPropertyInfo> propMap/* = d->getPropMap(obj, gadget)*/;

    //сериализуем все свойства, кроме списка исключенных

    const QMetaObject *mo = gad->getMetaObject();
    for(int i = mo->propertyOffset(), count = mo->propertyCount() ; i < count; i++)
    {
        QMetaProperty property = mo->property(i);
        //if(excludeProperties.contains(property.name()) || !property.isWritable()) continue;
        if(propMap[property.name()].isSkipped) continue;

        QVariant variantValue = property.readOnGadget(gad);

        //if(propMap[property.name()].isEncoded) variantValue = encode(variantValue);

        serialize(variantValue, property.name(), "");
    }

    if(!_nodeName.isEmpty())
    {
        d->m_elements.last()[_nodeName] = d->m_elements.pop();
    }

//    if(d->m_status.last() == SimpleJsonSerializerPrivate::FromList)
//    {
//        d->m_arrays.last().append(d->m_elements.pop());
//    }

//    d->m_status.pop();


    return true;
}

bool SimpleJsonSerializer::serialize(const QString &_value,
                                     const QString &_nodeName,
                                     const QString &_typeName,
                                     const QString &_key)
{
    Q_UNUSED(_typeName);
    Q_UNUSED(_key);

    if(_nodeName.isEmpty())
    {
        d->m_arrays.last().push_back(_value);
    } else
    {
        d->m_elements.last()[_nodeName] = _value;
    }

    return true;
}

bool SimpleJsonSerializer::deserialize(QString &_value, const QString &_nodeName, QString &_typeName)
{
    Q_UNUSED(_value);
    Q_UNUSED(_nodeName);
    Q_UNUSED(_typeName);

    return true;
}

bool SimpleJsonSerializer::deserialize(QVariant &_value, const QString &_nodeName)
{
    Q_UNUSED(_value);
    Q_UNUSED(_nodeName);

    return true;
}

bool SimpleJsonSerializer::deserialize(QVariantList &_value, const QString &_nodeName)
{
    Q_UNUSED(_value);
    Q_UNUSED(_nodeName);

    return true;
}

bool SimpleJsonSerializer::deserialize(QVariantMap &_value, const QString &_nodeName)
{
    Q_UNUSED(_value);
    Q_UNUSED(_nodeName);

    return true;
}

QByteArray SimpleJsonSerializer::saveToByteArray() const
{
    QJsonDocument doc(d->m_elements.first());
    return doc.toJson(QJsonDocument::Indented);
}

void SimpleJsonSerializer::loadFromByteArray(const QByteArray &_content)
{
    d->m_doc = QJsonDocument::fromJson(_content);
    d->m_elements.clear();
    d->m_elements.push(d->m_doc.object());
}

}
