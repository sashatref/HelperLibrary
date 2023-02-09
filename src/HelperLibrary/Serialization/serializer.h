#ifndef H_SERIALIZER
#define H_SERIALIZER

#include "../export.h"
#include "iserializebase.h"

#include <QString>
#include <QVariant>
#include <QDir>
#include <functional>

/*!
 *Для регистрации кастомного типа, необходимо реализовать две функции для преобразования своего типа в строку и обратно
 * Пример:
    QString serializeInt(const QVariant &_value, QString &_typeName)
    {
        _typeName = "int";
        return QString::number(_value.toInt());
    }

    QVariant deserializeInt(const QString &_stringValue)
    {
        QVariant result = _stringValue.toInt();
        return result;
    }

    И в любом месте своей программы до момента сериализации/десериализации выполнить метод:
    registerConverter(QVariant::Int, deserializeInt, serializeInt);
 */


class IGadget;

namespace SerializerQt
{

class SerializeConfig;
class IConverter;

typedef std::function<QString(const QVariant&, QString&)> ConvertToString;
typedef std::function<QVariant(const QString&)> ConvertFromString;

HELPERLIBRARY_EXPORT bool writeToFile(const QString &_path, const QByteArray &_data);
HELPERLIBRARY_EXPORT QByteArray readFromFile(const QString &_path);



class HELPERLIBRARY_EXPORT Serializer
{
public:
    enum SerializerType
    {
        Invalid = 0,
        Xml,
        XmlNode,
        Json,
        Binary,
        SimpleJson,
        SimpleXml
    };

    enum ActionType
    {
        Load,
        Save
    };

    enum ErrorAction
    {
        IgnoreErrors,
        ExceptOnError
    };

    template<class T>
    bool serialize(const T &_value, const QString &_nodeName)
    {
        return serialize(QVariant::fromValue(_value), _nodeName);
    }

    template<class T>
    bool deserialize(T &_value, const QString &_nodeName)
    {
        QVariant tempValue = QVariant::fromValue(_value);
        bool result = deserialize(tempValue, _nodeName);
        _value = tempValue.value<T>();
        return result;
    }

    template<class T1, class T2>
    bool deserialize(QMap<T1, T2> &_value, const QString &_nodeName)
    {
        _value.clear();
        QVariant tempValue = QVariant::fromValue(_value);
        bool result = deserialize(tempValue, _nodeName);

        QVariantMap varMap = tempValue.toMap();

        for(int i = 0 ; i < varMap.keys().size(); i++)
        {
            T1 key = QVariant(varMap.keys().at(i)).value<T1>();
            _value[key] = varMap[varMap.keys().at(i)].value<T2>();
        }

        return result;
    }

    template<class T>
    bool deserialize(QVector<T> &_value, const QString &_nodeName)
    {
        _value.clear();
        QVariant tempValue = QVariant::fromValue(_value);
        bool result = deserialize(tempValue, _nodeName);
        QList<QVariant> varList = tempValue.value<QList<QVariant>>();
        foreach (const auto &item, varList)
        {
            _value.append(item.value<T>());
        }
        return result;
    }

    template<class T>
    bool deserialize(QList<T> &_value, const QString &_nodeName)
    {
        _value.clear();
        QVariant tempValue = QVariant::fromValue(_value);
        bool result = deserialize(tempValue, _nodeName);
        QList<QVariant> varList = tempValue.value<QList<QVariant>>();
        foreach (const auto &item, varList)
        {
            _value.append(item.value<T>());
        }
        return result;
    }


    template<class T>
    static void save(const T &_value,
                     const QDir &_fileToSave,
                     const QString &_nodeName,
                     ErrorAction _errorLevel = ExceptOnError,
                     SerializerType _type = Xml)
    {
        QByteArray data;
        save(_value, data, _nodeName, _errorLevel, _type);
        writeToFile(_fileToSave.path(), data);
    }

    template<class T>
    static void save(const T &_value,
                     QByteArray &_data,
                     const QString &_nodeName,
                     ErrorAction _errorLevel = ExceptOnError,
                     SerializerType _type = Xml)
    {
        Serializer *ser = createInstanse(_type, Save, _errorLevel);
        ser->serialize(_value, _nodeName);
        _data = ser->saveToByteArray();
        delete ser;
    }

    template<class T>
    static void saveXmlNode(const T &_value,
                     QByteArray &_data,
                     ErrorAction _errorLevel = ExceptOnError)
    {
        save(_value, _data, "XmlNode", _errorLevel, XmlNode);
    }

    template<class T>
    static void append(T &_value,
                     const QDir &_fileToSave,
                     const QString &_nodeName,
                     ErrorAction _errorLevel = ExceptOnError,
                     SerializerType _type = Xml)
    {
        QByteArray data = readFromFile(_fileToSave.path());
        append(_value, data, _nodeName, _errorLevel, _type);
        writeToFile(_fileToSave.path(), data);
    }

    template<class T>
    static void append(T &_value,
                       QByteArray &_data,
                     const QString &_nodeName,
                     ErrorAction _errorLevel = ExceptOnError,
                     SerializerType _type = Xml)
    {
        Serializer *ser = createInstanse(_type, Load, _errorLevel);
        ser->loadFromByteArray(_data);
        ser->deleteIfExists(_nodeName);
        ser->m_actionType = Save;
        ser->serialize(_value, _nodeName);

        Q_ASSERT_X(_type != Binary, "Only Xml or Json supports append", "Only Xml or Json supports append");
        _data = ser->saveToByteArray();
        delete ser;
    }

    template<class T>
    static void load(T &_value,
                     const QDir &_fileToLoad,
                     const QString &_nodeName,
                     ErrorAction _errorLevel = ExceptOnError,
                     SerializerType _type = Xml)
    {
        QByteArray data = readFromFile(_fileToLoad.path());
        load(_value, data, _nodeName, _errorLevel, _type);
    }

    template<class T>
    static void load(T &_value,
                     const QByteArray &_data,
                     const QString &_nodeName,
                     ErrorAction _errorLevel = ExceptOnError,
                     SerializerType _type = Xml)
    {
        Serializer *ser = createInstanse(_type, Load, _errorLevel);
        ser->loadFromByteArray(_data);
        ser->deserialize(_value, _nodeName);
        delete ser;
    }

    template<class T>
    static void loadXmlNode(T &_value,
                     const QByteArray &_data,
                     ErrorAction _errorLevel = IgnoreErrors)
    {
        load(_value, _data, "", _errorLevel, XmlNode);
    }


    virtual bool serialize(const QVariantMap &_valueMap, const QString &_nodeName, const QString &_containerType, const QString &_key) = 0;
    virtual bool serialize(const QVariantList &_valueList, const QString &_nodeName, const QString &_containerType, const QString &_key) = 0;
    virtual bool serialize(const QVariant &_value, const QString &_nodeName, const QString &_key = "") = 0;
    virtual bool serialize(const QString &_value, const QString &_nodeName, const QString &_typeName, const QString &_key) = 0;
    virtual bool deserialize(QString &_value, const QString &_nodeName, QString &_typeName) = 0;
    virtual bool deserialize(QVariant &_value, const QString &_nodeName) = 0;
    virtual bool deserialize(QVariantList &_value, const QString &_nodeName) = 0;
    virtual bool deserialize(QVariantMap &_value, const QString &_nodeName) = 0;

    SerializerType getType() const;

    static void registerConverter(int _type, ConvertFromString _from, ConvertToString _to);

    static void registerConverter(int _type, IConverter *_conv);

    template<class Type, class Converter>
    static void registerConverter()
    {
        registerConverter(qMetaTypeId<Type>(), new Converter());
    }

    static void registerEnumConverter(int _type);

    template<class Type>
    static void registerEnumConverter()
    {
        registerEnumConverter(qMetaTypeId<Type>());
    }

protected:
    Serializer(SerializerType _type, ActionType _action, ErrorAction _errorAction);
    virtual ~Serializer();

    ActionType getAction() const;
    void setCurrentKey(const QString &_key);
    const QString &getCurrentKey() const;
    const ErrorAction &getErrorAction() const;

    bool serializeKnownVariant(const QVariant &_value, const QString &_nodeName, const QString &_key);
    bool deserializeKnownVariant(QVariant &_value, const QString &_typeName);

    virtual QByteArray saveToByteArray() const = 0;
    virtual void loadFromByteArray(const QByteArray &_content) = 0;
    virtual void deleteIfExists(const QString &_nodeName);


    void registerBaseConverters();

    ISerializeBase *getIBase(QObject *const _obj);
    ISerializeBase *getIBase(IGadget *const _gadget);

private:
    SerializerType m_type;
    ActionType m_actionType;
    ErrorAction m_errorAction;
    QString m_currentKey;
    SerializeConfig *m_serConfig = nullptr;

    static Serializer *createInstanse(SerializerType _type, ActionType _actionType, ErrorAction _errorAction);
};

}

#endif //H_SERIALIZER
