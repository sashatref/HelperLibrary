#include "jsonserializer.h"

#include "../serializerexception.h"

#include <QStack>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>

namespace SerializerQt
{

class JsonSerializerPrivate
{
    friend class JsonSerializer;
    JsonSerializer const *q;
    QJsonDocument m_doc;
    QStack<QJsonObject> m_elements;

    JsonSerializerPrivate(JsonSerializer *_q):
        q(_q)
    {
        QJsonObject root;
        m_elements.push(root);
    }
};

JsonSerializer::JsonSerializer(Serializer::ActionType _type, Serializer::ErrorAction _errorAction):
    Serializer(Json, _type, _errorAction),
    d(new JsonSerializerPrivate(this))
{

}

JsonSerializer::~JsonSerializer()
{
    delete d;
}

bool JsonSerializer::serialize(const QVariantMap &_valueMap, const QString &_nodeName, const QString &_containerType, const QString &_key)
{
    QJsonObject subElement;
    QJsonArray array;

    subElement["type"] = _containerType;
    if(!_key.isEmpty()) subElement["key"] = _key;

    for(int i = 0 ; i < _valueMap.keys().size(); i++)
    {
        QString key = _valueMap.keys().at(i);
        d->m_elements.push(QJsonObject());
        serialize(_valueMap[key], "element", key);
        array.append(d->m_elements.pop());
    }

    subElement["value"] = array;

    d->m_elements.last()[_nodeName] = subElement;

    return true;
}

bool JsonSerializer::serialize(const QVariantList &_valueList, const QString &_nodeName, const QString &_containerType, const QString &_key)
{
    QJsonObject subElement;
    QJsonArray array;

    subElement["type"] = _containerType;
    if(!_key.isEmpty()) subElement["key"] = _key;

    for(int i = 0 ; i < _valueList.size(); i++)
    {
        d->m_elements.push(QJsonObject());
        serialize(_valueList.at(i), "element");
        array.append(d->m_elements.pop());
    }

    subElement["value"] = array;

    d->m_elements.last()[_nodeName] = subElement;

    return true;
}

bool JsonSerializer::serialize(const QVariant &_value, const QString &_nodeName, const QString &_key)
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

    QObject *obj = _value.value<QObject*>();
    if(!obj)
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

    if(!_key.isEmpty())
    {
        subElement["key"] = _key;
    }
    subElement["type"] = _value.typeName();

    d->m_elements.push(subElement);

    //сериализуем все свойства, кроме списка исключенных
    for(int i = obj->metaObject()->propertyOffset() ; i < obj->metaObject()->propertyCount(); i++)
    {
        QMetaProperty property = obj->metaObject()->property(i);
        QVariant variantValue = property.read(obj);

        serialize(variantValue, property.name(), "");
    }

    d->m_elements.last()[_nodeName] = d->m_elements.pop();;


    return true;
}

bool JsonSerializer::serialize(const QString &_value,
                               const QString &_nodeName,
                               const QString &_typeName,
                               const QString &_key)
{
    QJsonObject subElement;
    subElement["value"] = _value;
    subElement["type"] = _typeName;
    if(!_key.isEmpty()) subElement["key"] = _key;

    d->m_elements.last()[_nodeName] = subElement;

    return true;
}

bool JsonSerializer::deserialize(QString &_value, const QString &_nodeName, QString &_key)
{
    QJsonObject element;

    if(_nodeName.isEmpty())
    {
        element = d->m_elements.last();
    } else
    {
        element = d->m_elements.last().value(_nodeName).toObject();
    }

    if(element.isEmpty()) return false;

    _value = element["value"].toString();
    if(element.contains("key"))
    {
        _key = element["key"].toString();
    }

    return true;
}

bool JsonSerializer::deserialize(QVariant &_value, const QString &_nodeName)
{
    QJsonObject subElement;
    if(_nodeName.isEmpty())
    {
        subElement = d->m_elements.last();
    } else
    {
        subElement = d->m_elements.last()[_nodeName].toObject();
    }
    //если узел не найден
    if(subElement.isEmpty()) return false;

    QString typeName = getTypeName(_nodeName);
    d->m_elements.push(subElement);

    if(deserializeKnownVariant(_value, typeName))
    {
        d->m_elements.pop();
        return true;
    }

    if(QMetaType::type(typeName.toStdString().c_str()) == QVariant::Invalid)
    {
        qWarning() << Q_FUNC_INFO << "\n" << QString(QObject::tr("Тип <%1> не зарегестрирован!")).arg(typeName);
        d->m_elements.pop();
        return false;
    }

    _value = QVariant(QMetaType::type(typeName.toStdString().c_str()), 0);
    if(!_value.isValid())
    {
        qWarning() << "JsonSerializer::deserialize(QVariant &_value, const QString &_nodeName)";
        qWarning() << QObject::tr("Ошибка создания типа \"QVariant\" из \"%1\"").arg(typeName);
        qWarning() << QObject::tr("Возможно пропущено выполение \"qMetaTypeId<%1>()\"").arg(typeName);
        d->m_elements.pop();
        return false;
    }

    if(_value.canConvert<QVariantList>())
    {
        QVariantList list = _value.value<QVariantList>();
        bool result = deserialize(list, "");
        _value = list;
        if(!_value.convert(QMetaType::type(typeName.toStdString().c_str())))
        {
            qWarning() << "XmlSerializer::deserialize(QVariant &_value, const QString &_nodeName)";
            qWarning() << QObject::tr("Ошибка конвертирования \"QVariantList\" в \"%1\"").arg(typeName);
            qWarning() << QObject::tr("Необходимо зарегестрировать соостветствующий конвертер");
        }
        d->m_elements.pop();
        return result;
    }

    if(_value.canConvert<QVariantMap>())
    {
        QVariantMap map = _value.value<QVariantMap>();
        bool result = deserialize(map, "");
        _value = map;
        if(!_value.convert(QMetaType::type(typeName.toStdString().c_str())))
        {
            qWarning() << "XmlSerializer::deserialize(QVariant &_value, const QString &_nodeName)";
            qWarning() << QObject::tr("Ошибка конвертирования \"QVariantMap\" в \"%1\"").arg(typeName);
            qWarning() << QObject::tr("Необходимо зарегестрировать соостветствующий конвертер");
        }
        d->m_elements.pop();
        return result;
    }


    QObject *obj = _value.value<QObject*>();
    if(!obj)
    {   switch(getErrorAction())
        {
        case IgnoreErrors:
            qWarning() << "Unsupported type <" << _value.userType() << ">";
            d->m_elements.pop();
            return false;
            break;
        case ExceptOnError:
            throw ToObjectException(_value.typeName());
            break;
        }
    }

    //десериализуем все свойства, кроме списка исключенных
    for(int i = obj->metaObject()->propertyOffset() ; i < obj->metaObject()->propertyCount(); i++)
    {
        QMetaProperty property = obj->metaObject()->property(i);
        QVariant variantValue(obj->property(property.name()));
        deserialize(variantValue, property.name());
        obj->setProperty(property.name(), variantValue);
    }

    d->m_elements.pop();

    return true;
}

bool JsonSerializer::deserialize(QVariantList &_value, const QString &_nodeName)
{
    QJsonObject element;
    if(_nodeName.isEmpty())
    {
        element = d->m_elements.last();
    } else
    {
        element = d->m_elements.last()[_nodeName].toObject();
    }

    QJsonArray array = element["value"].toArray();
    for(int i = 0 ; i < array.size(); i++)
    {
        d->m_elements.push(array.at(i).toObject());
        QVariant item;
        deserialize(item, "element");
        _value.push_back(item);
        d->m_elements.pop();
    }

    return true;
}

bool JsonSerializer::deserialize(QVariantMap &_value, const QString &_nodeName)
{
    QJsonObject element;
    if(_nodeName.isEmpty())
    {
        element = d->m_elements.last();
    } else
    {
        element = d->m_elements.last()[_nodeName].toObject();
    }

    QJsonArray array = element["value"].toArray();
    for(int i = 0 ; i < array.size(); i++)
    {
        d->m_elements.push(array.at(i).toObject());

        QString key = getKey("element");
        if(key.isEmpty()) qWarning() << "Key is empty!";

        QVariant item;
        deserialize(item, "element");
        _value[key] = item;
        d->m_elements.pop();
    }

    return true;
}

QByteArray JsonSerializer::saveToByteArray() const
{
    QJsonDocument doc(d->m_elements.first());
    return doc.toJson(QJsonDocument::Indented);
}

void JsonSerializer::loadFromByteArray(const QByteArray &_content)
{
    d->m_doc = QJsonDocument::fromJson(_content);
    d->m_elements.clear();
    d->m_elements.push(d->m_doc.object());
}

QString JsonSerializer::getTypeName(const QString &_nodeName)
{
    QJsonObject subElement;
    if(_nodeName.isEmpty())
    {
        subElement = d->m_elements.last();
    } else
    {
        subElement = d->m_elements.last()[_nodeName].toObject();
    }

    return subElement["type"].toString();
}

QString JsonSerializer::getKey(const QString &_nodeName)
{
    QJsonObject subElement;
    if(_nodeName.isEmpty())
    {
        subElement = d->m_elements.last();
    } else
    {
        subElement = d->m_elements.last()[_nodeName].toObject();
    }

    return subElement["key"].toString();
}

}
