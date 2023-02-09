#include "xmlserializer.h"
#include "../../igadget.h"

#include <QStack>


namespace SerializerQt
{

static SimpleCrypt cryptoXml = SimpleCrypt(0x0c2ad3a4a2b9f011);

class XmlSerializerPrivate
{
    friend class XmlSerializer;
    XmlSerializer *const d;
    QString m_version;
    QDomDocument m_doc;
    QStack<QDomElement> m_elements;
    XmlSerializer::XmlType m_xmlType;

    XmlSerializerPrivate(XmlSerializer *const _d):
        d(_d)
    {

    }

    QMap<QString, SerPropertyInfo> getPropMap(QObject *const _obj, IGadget *const _gadget)
    {
        QMap<QString, SerPropertyInfo> m;

        ISerializeBase *base = nullptr;
        if(_obj)
        {
            base = d->getIBase(_obj);
        }
        if(_gadget)
        {
            base = d->getIBase(_gadget);
        }

        if(base)
        {
            base->propertyMap(m);
        }

        return m;
    }
};



void XmlSerializer::createXmlHeader()
{
    QDomElement root;
    d->m_doc.appendChild(d->m_doc.createProcessingInstruction("xml",
                                                        QString("version=\"%1\" encoding=\"%2\"")
                                                        .arg("1.0")
                                                        .arg("UTF-8")));

    root = d->m_doc.createElement("root");
    d->m_elements.push(root);
    d->m_doc.appendChild(root);
}

XmlSerializer::XmlSerializer(ActionType _type, ErrorAction _errorAction, XmlType _xmlType):
    Serializer(Xml, _type, _errorAction),
    d(new XmlSerializerPrivate(this))
{
    d->m_xmlType = _xmlType;
    switch(_type)
    {
    case Load:

        break;
    case Save:
        if(_xmlType == XmlFile)
        {
            createXmlHeader();
        }
        break;
    }
}

XmlSerializer::~XmlSerializer()
{
    delete d;
}

QDomDocumentFragment XmlSerializer::saveToElement(const QVariant &_value)
{
    XmlSerializer *ser = new XmlSerializer(Save, Serializer::IgnoreErrors, XmlNode);
    ser->serialize(_value, "SomeNode");
    QDomDocumentFragment element = ser->d->m_doc.toDocumentFragment();
    delete ser;
    return element;
}

bool XmlSerializer::serialize(const QVariantMap &_valueMap, const QString &_nodeName, const QString &_containerType, const QString &_key)
{
    QDomElement subElement;
    subElement = d->m_doc.createElement(_nodeName);
    subElement.setAttribute("type", _containerType);
    if(!_key.isEmpty()) subElement.setAttribute("key", _key);

    if(d->m_elements.size() == 0)
    {
        d->m_doc.appendChild(subElement);
    } else
    {
        d->m_elements.last().appendChild(subElement);
    }
    d->m_elements.push(subElement);

    for(auto it = _valueMap.begin(); it != _valueMap.end(); ++it)
    {
        serialize(it.value(), "element", it.key());
    }

    d->m_elements.pop();

    return true;
}

bool XmlSerializer::serialize(const QVariantList &_valueList, const QString &_nodeName, const QString &_containerType, const QString &_key)
{
    QDomElement subElement;
    subElement = d->m_doc.createElement(_nodeName);
    subElement.setAttribute("type", _containerType);
    if(!_key.isEmpty()) subElement.setAttribute("key", _key);

    if(d->m_elements.size() == 0)
    {
        d->m_doc.appendChild(subElement);
    } else
    {
        d->m_elements.last().appendChild(subElement);
    }

    d->m_elements.push(subElement);

    for(int i = 0 ; i < _valueList.size(); i++)
    {
        serialize(_valueList.at(i), "element");
    }

    d->m_elements.pop();

    return true;
}

bool XmlSerializer::serialize(const QString &_value, const QString &_nodeName, const QString &_typeName, const QString &_key)
{
    QDomElement subElement;

    subElement = d->m_doc.createElement(_nodeName);
    subElement.appendChild(d->m_doc.createTextNode(_value));
    subElement.setAttribute("type", _typeName);
    if(!_key.isEmpty())
    {
        subElement.setAttribute("key", _key);
    }

    if(d->m_elements.size() == 0)
    {
        d->m_doc.appendChild(subElement);
    } else
    {
        d->m_elements.last().appendChild(subElement);
    }

    return true;
}

bool XmlSerializer::deserialize(QString &_value, const QString &_nodeName, QString &_key)
{
    QDomElement element;
    if(_nodeName.isEmpty())
    {
        element = d->m_elements.last();
    } else
    {
        element = d->m_elements.last().firstChildElement(_nodeName);
    }

    _value = element.text();

    if(element.hasAttribute("key"))
    {
        _key = element.attribute("key");
    }

    return true;
}


bool XmlSerializer::deserialize(QVariantList &_value, const QString &_nodeName)
{
    QDomElement element;
    if(_nodeName.isEmpty())
    {
        element = d->m_elements.last();
    } else
    {
        element = d->m_elements.last().firstChildElement(_nodeName);
    }

    QDomNodeList nodeList = element.childNodes();

    for(int i = 0, count = nodeList.size(); i < count; i++)
    {
        d->m_elements.push(nodeList.at(i).toElement());

        QVariant item;
        deserialize(item, "");
        _value.push_back(item);
        d->m_elements.pop();
    }

    return true;
}

bool XmlSerializer::deserialize(QVariantMap &_value, const QString &_nodeName)
{
    QDomElement element;
    if(_nodeName.isEmpty())
    {
        element = d->m_elements.last();
    } else
    {
        element = d->m_elements.last().firstChildElement(_nodeName);
    }

    QDomNodeList nodeList = element.childNodes();

    for(int i = 0 ; i < nodeList.size(); i++)
    {
        d->m_elements.push(nodeList.at(i).toElement());

        QString key = getKey("");
        if(key.isEmpty())   qWarning() << "Key is empty!";
        QVariant item;
        deserialize(item, "");
        _value[key] = item;
        d->m_elements.pop();
    }

    return true;
}

QString XmlSerializer::getTypeName(const QString &_nodeName)
{
    QDomElement subElement;
    if(_nodeName.isEmpty())
    {
        subElement = d->m_elements.last().cloneNode().toElement();
    } else
    {
        subElement = d->m_elements.last().firstChildElement(_nodeName);
    }

    return subElement.attribute("type");
}

QString XmlSerializer::getKey(const QString &_nodeName)
{
    QDomElement subElement;
    if(_nodeName.isEmpty())
    {
        subElement = d->m_elements.last().cloneNode().toElement();
    } else
    {
        subElement = d->m_elements.last().firstChildElement(_nodeName);
    }

    return subElement.attribute("key");
}

QByteArray XmlSerializer::saveToByteArray() const
{
    return d->m_doc.toByteArray(4);
}

void XmlSerializer::loadFromByteArray(const QByteArray &_content)
{
    QString error;
    int line = 0;
    int column = 0;

    if(!d->m_doc.setContent(_content, &error, &line, &column))
    {
        QString errMsg = QString("XmlSerializer::loadFromByteArray | "
                                 "Error while parse xml on line [%1] columns [%2] [%3]")
                .arg(line)
                .arg(column)
                .arg(error);

        switch(getErrorAction())
        {
        case IgnoreErrors:
            qWarning() << errMsg;
            break;
        case ExceptOnError:
            throw BaseException(errMsg);
            break;
        }
    }

    d->m_version = parseVersion(d->m_doc.firstChild().toProcessingInstruction().data());
    d->m_elements.push(d->m_doc.documentElement());

    if(d->m_xmlType == XmlFile)
    {
        if(d->m_elements.last().nodeName() != "root")
        {
            d->m_doc.clear();
            d->m_elements.clear();
            createXmlHeader();
        }
    }
}

const QString &XmlSerializer::getVersion() const {return d->m_version;}

QString XmlSerializer::parseVersion(const QString &_string)
{
    QStringList values = _string.split(" ");
    for(int i = 0; i < values.size(); i++)
    {
        QStringList items = values[i].split("=");
        if(items.size() == 2)
        {
            if(items[0] == "version")
            {
                return items[1].replace("'", "").replace("\"", "");
            }
        }
    }
    return "1.0";
}

void XmlSerializer::deleteIfExists(const QString &_nodeName)
{
    QDomElement elem = d->m_elements.first().firstChildElement(_nodeName);
    while(!elem.isNull())
    {
        d->m_elements.first().removeChild(elem);
        elem = d->m_elements.first().firstChildElement(_nodeName);
    }
}

QVariant XmlSerializer::encode(const QVariant &_val)
{
    if(_val.userType() == QVariant::String)
    {
        QString str = _val.toString();
        if(str.isEmpty()) return _val;

        return cryptoXml.encryptToString(str);
    }

    qWarning() << QString("Type <%1> not supported for endoding").arg(_val.typeName());

    return _val;
}

QVariant XmlSerializer::decode(const QVariant &_val)
{
    if(_val.userType() == QVariant::String)
    {
        QString str = _val.toString();
        QString res = cryptoXml.decryptToString(str);
        return res.isEmpty() ? _val : res;
    }

    qWarning() << QString("Type <%1> not supported for decoding").arg(_val.typeName());

    return _val;
}

bool XmlSerializer::serialize(const QVariant &_value, const QString &_nodeName, const QString &_key)
{
    if(!_value.isValid()) return false;

    QDomElement subElement;
    subElement = d->m_doc.createElement(_nodeName);

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
    IGadget *gadget = _value.value<IGadget*>();

    if(!obj && !gadget)
    {
        switch(getErrorAction())
        {
        case IgnoreErrors:
            qWarning() << QString("Serialization | Unsupported type <%1> <%2>")
                          .arg(_value.userType())
                          .arg(_value.typeName());
            qWarning() << Q_FUNC_INFO;
            return false;
            break;
        case ExceptOnError:
            throw ToObjectException(_value.typeName());
            break;
        }
    }

    if(!_key.isEmpty())
    {
        subElement.setAttribute("key", _key);
    }

    subElement.setAttribute("type", _value.typeName());

    if(d->m_elements.size() == 0)
    {
        d->m_doc.appendChild(subElement);
    } else
    {
        d->m_elements.last().appendChild(subElement);
    }

    d->m_elements.push(subElement);


    //получаем список свойств, которые необходимо исключить из сериализации
    QMap<QString, SerPropertyInfo> propMap = d->getPropMap(obj, gadget);

    //сериализуем все свойства, кроме списка исключенных
    if(obj)
    {
        const QMetaObject *mo = obj->metaObject();
        for(int i = mo->propertyOffset(), count = mo->propertyCount() ; i < count; i++)
        {
            QMetaProperty property = mo->property(i);
            if(propMap[property.name()].isSkipped) continue;

            QVariant variantValue =  property.read(obj);

            if(propMap[property.name()].isEncoded) variantValue = encode(variantValue);

            serialize(variantValue, property.name(), "");
        }
    } else if(gadget)
    {

        const QMetaObject *mo = gadget->getMetaObject();
        for(int i = mo->propertyOffset(), count = mo->propertyCount() ; i < count; i++)
        {
            QMetaProperty property = mo->property(i);
            if(propMap[property.name()].isSkipped) continue;

            QVariant variantValue = property.readOnGadget(gadget);

            if(propMap[property.name()].isEncoded) variantValue = encode(variantValue);

            serialize(variantValue, property.name(), "");
        }
    }

    d->m_elements.pop();


    return true;
}

bool XmlSerializer::deserialize(QVariant &_value, const QString &_nodeName)
{
    QDomElement subElement;
    if(_nodeName.isEmpty())
    {
        subElement = d->m_elements.last().cloneNode().toElement();
    } else
    {
        subElement = d->m_elements.last().firstChildElement(_nodeName);
    }
    //если узел не найден
    if(subElement.isNull()) return false;

    QString typeName = getTypeName(_nodeName);
    d->m_elements.push(subElement);

    if(deserializeKnownVariant(_value, typeName))
    {
        d->m_elements.pop();
        return true;
    }

    if(QMetaType::type(typeName.toStdString().c_str()) == QVariant::Invalid)
    {
        qWarning() << Q_FUNC_INFO << "\n" << QString(QObject::tr("Serialization | Тип <%1> не зарегестрирован!")).arg(typeName);
        d->m_elements.pop();
        return false;
    }

    _value = QVariant(QMetaType::type(typeName.toStdString().c_str()), nullptr);
    if(!_value.isValid())
    {
        qWarning() << "XmlSerializer::deserialize(QVariant &_value, const QString &_nodeName)";
        qWarning() << QObject::tr("Ошибка создания типа \"QVariant\" из \"%1\"").arg(typeName);
        qWarning() << QObject::tr("Возможно пропущено выполение \"qMetaTypeId<%1>()\"").arg(typeName);
        d->m_elements.pop();
        return false;
    }

    if(_value.canConvert<QVariantList>())
    {
        QList<QVariant> list = _value.value<QList<QVariant>>();
        bool result = deserialize(list, "");
        _value = QVariant::fromValue(list);
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
    IGadget *gadget = _value.value<IGadget*>();
    if(!obj && !gadget)
    {   switch(getErrorAction())
        {
        case IgnoreErrors:
            qWarning() << "Serialization | Unsupported type <" << _value.userType() << ">";
            d->m_elements.pop();
            return false;
            break;
        case ExceptOnError:
            throw ToObjectException(_value.typeName());
            break;
        }
    }

    //получаем список свойств, которые необходимо исключить из десериализации
    QMap<QString, SerPropertyInfo> propMap = d->getPropMap(obj, gadget);

    if(obj)
    {
        //десериализуем все свойства, кроме списка исключенных
        const QMetaObject *mo = obj->metaObject();
        for(int i = mo->propertyOffset(), count = mo->propertyCount(); i < count; i++)
        {
            QMetaProperty property = mo->property(i);
            if(!property.isWritable()) continue;

            QVariant variantValue(property.read(obj));
            deserialize(variantValue, property.name());

            if(propMap[property.name()].isEncoded) variantValue = decode(variantValue);

            property.write(obj, variantValue);
        }
    } else if(gadget)
    {
        const QMetaObject *mo = gadget->getMetaObject();
        for(int i = mo->propertyOffset(), count = mo->propertyCount(); i < count; i++)
        {
            QMetaProperty property = mo->property(i);
            if(!property.isWritable()) continue;

            QVariant variantValue(property.readOnGadget(gadget));
            deserialize(variantValue, property.name());

            if(propMap[property.name()].isEncoded) variantValue = decode(variantValue);

            property.writeOnGadget(gadget, variantValue);
        }
    }

    d->m_elements.pop();

    return true;
}
}
