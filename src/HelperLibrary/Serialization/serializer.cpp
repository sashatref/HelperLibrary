#include "../project_pch.h"
#include "serializer.h"

#include "impl/xmlserializer.h"
#include "impl/binaryserializer.h"
#include "impl/jsonserializer.h"
#include "impl/simplejsonserializer.h"
#include "impl/SimpleXmlSerializer.h"

#include "serializerexception.h"
#include "../igadget.h"
#include "../ivariant.h"
#include "serializeconfig.h"
#include "converfuncimpl.h"


namespace SerializerQt
{

Serializer::Serializer(Serializer::SerializerType _type,
                       Serializer::ActionType _action,
                       ErrorAction _errorAction):
    m_type(_type),
    m_actionType(_action),
    m_errorAction(_errorAction)
{
    m_serConfig = SerializeConfig::get();

    registerBaseConverters();
}

Serializer::~Serializer()
{

}

Serializer::SerializerType Serializer::getType() const
{
    return m_type;
}


Serializer::ActionType Serializer::getAction() const
{
    return m_actionType;
}

void Serializer::setCurrentKey(const QString &_key)
{
    m_currentKey = _key;
}

const QString &Serializer::getCurrentKey() const
{
    return m_currentKey;
}

const Serializer::ErrorAction &Serializer::getErrorAction() const
{
    return m_errorAction;
}

bool Serializer::serializeKnownVariant(const QVariant &_value, const QString &_nodeName, const QString &_key)
{
    if(IConverter *conv = m_serConfig->getConverter(_value.userType()))
    {
        QString type;
        QString stringValue = conv->toString(_value, type);
        serialize(stringValue, _nodeName, type, _key);
        return true;
    }
    return false;
}

bool Serializer::deserializeKnownVariant(QVariant &_value, const QString &_typeName)
{
    QVariant var(QMetaType::type(_typeName.toStdString().c_str()), 0);

    if(IConverter *conv = m_serConfig->getConverter(var.userType()))
    {
        QString stringValue;
        QString typeName;
        deserialize(stringValue, "", typeName);
        _value = conv->fromString(stringValue);
        return true;
    }

    return false;
}

void Serializer::deleteIfExists(const QString &_nodeName)
{
    Q_UNUSED(_nodeName);
}

void Serializer::registerConverter(int _type, ConvertFromString _from, ConvertToString _to)
{
    SerializeConfig::get()->registerConverter(_type, new ConverterByFunc(_to, _from));
}

void Serializer::registerConverter(int _type, IConverter *_conv)
{
    SerializeConfig::get()->registerConverter(_type, _conv);
}

void Serializer::registerEnumConverter(int _type)
{
    registerConverter(_type, new ConverterInt());
}

void Serializer::registerBaseConverters()
{
    registerConverter<int,          ConverterInt>();
    registerConverter<QString,      ConverterString>();
    registerConverter<double,       ConverterDouble>();
    registerConverter<bool,         ConverterBool>();
    registerConverter<QByteArray,   ConverterByteArray>();
    registerConverter<QDate,        ConverterDate>();
    registerConverter<QDateTime,    ConverterDateTime>();
    registerConverter<QTime,        ConverterTime>();
    registerConverter<QRect,        ConverterRect>();
    registerConverter<QSize,        ConverterSize>();
    registerConverter<QColor,       ConverterColor>();
    registerConverter<QFont,        ConverterFont>();
    registerConverter<QUrl,         ConverterUrl>();
    registerConverter<QPoint,       ConverterPoint>();
    registerConverter<QPointF,      ConverterPointF>();
}

ISerializeBase *Serializer::getIBase(QObject * const _obj)
{
    return ObjectHelper::castObject<ISerializeBase>(_obj);
}

ISerializeBase* Serializer::getIBase(IGadget * const _gadget)
{
    return GadgetHelper::castObject<ISerializeBase>(_gadget);
}

Serializer *Serializer::createInstanse(SerializerType _type, ActionType _actionType, ErrorAction _errorAction)
{
    Serializer *ser;
    switch(_type)
    {
    case Xml:
        ser = new XmlSerializer(_actionType, _errorAction, XmlSerializer::XmlFile);
        break;
    case XmlNode:
        ser = new XmlSerializer(_actionType, _errorAction, XmlSerializer::XmlNode);
        break;
    case Json:
        ser = new JsonSerializer(_actionType, _errorAction);
        break;
    case Binary:
        ser = new BinarySerializer(_actionType, _errorAction);
        break;
    case SimpleJson:
        ser = new SimpleJsonSerializer(_actionType, _errorAction);
        break;
    case SimpleXml:
        ser = new SimpleXmlSerializer(_actionType, _errorAction, SimpleXmlSerializer::XmlFile);
        break;
    default:
        throw BaseException(QString("Type <%1> not supported").arg(_type).toStdString().c_str());
    }

    return ser;
}

QByteArray readFromFile(const QString &_path)
{
    QByteArray result;

    QFile file(_path);
    if(file.open(QIODevice::ReadOnly))
    {
        result = file.readAll();
        file.close();
    }

    return result;
}

bool writeToFile(const QString &_path, const QByteArray &_data)
{
    QFile file(_path);
    if(file.open(QIODevice::WriteOnly))
    {
        file.write(_data);
        file.close();
        return true;
    }

    return false;
}

}
