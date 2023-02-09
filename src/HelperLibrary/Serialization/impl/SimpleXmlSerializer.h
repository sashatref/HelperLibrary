#pragma once

#include "../../simplecrypt.h"

#include "../serializer.h"
#include "../serializerexception.h"

class QDomDocument;
class QDomElement;

static SimpleCrypt simpleCryptoXml;

namespace SerializerQt
{

class SimpleXmlSerializerPrivate;
class HELPERLIBRARY_EXPORT SimpleXmlSerializer : public Serializer
{
    friend class Serializer;
    friend class SimpleXmlSerializerPrivate;

    SimpleXmlSerializerPrivate *const d;

    void createXmlHeader();

protected:
    enum XmlType
    {
        XmlFile,
        XmlNode
    };

    SimpleXmlSerializer(ActionType _type, ErrorAction _errorAction, XmlType _xmlType);
    using Serializer::serialize;
    using Serializer::deserialize;

    virtual ~SimpleXmlSerializer();

    bool serialize(const QVariantMap &_valueMap, const QString &_nodeName, const QString &_containerType, const QString &_key) override;
    bool serialize(const QVariantList &_valueList, const QString &_nodeName, const QString &_containerType, const QString &_key) override;
    bool serialize(const QVariant &_value, const QString &_nodeName,const QString &_key) override;
    bool serialize(const QString &_value, const QString &_nodeName, const QString &_typeName, const QString &_key) override;
    bool deserialize(QString &_value, const QString &_nodeName, QString &_key) override;
    bool deserialize(QVariant &_value, const QString &_nodeName) override;
    bool deserialize(QVariantList &_value, const QString &_nodeName) override;
    bool deserialize(QVariantMap &_value, const QString &_nodeName) override;

    QByteArray saveToByteArray() const override;
    void loadFromByteArray(const QByteArray &_content) override;

    QString getTypeName(const QVariant &_nodeName);
    QString getKey(const QString &_nodeName);

    const QString &getVersion() const;
    static QString parseVersion(const QString &_string);
    void deleteIfExists(const QString &_nodeName) override;

    QVariant encode(const QVariant &_val);
    QVariant decode(const QVariant &_val);

    int m_arrayElementId = 0;

public:
    static QDomDocumentFragment saveToElement(const QVariant &_value);
};

}
