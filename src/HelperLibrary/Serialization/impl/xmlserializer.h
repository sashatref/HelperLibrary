#pragma once

#include "../../simplecrypt.h"

#include "../serializer.h"
#include "../serializerexception.h"

class QDomDocument;
class QDomElement;

static SimpleCrypt cryptoXml;

namespace SerializerQt
{

class XmlSerializerPrivate;
class HELPERLIBRARY_EXPORT XmlSerializer : public Serializer
{
    friend class Serializer;
    friend class XmlSerializerPrivate;

    XmlSerializerPrivate *const d;

    void createXmlHeader();

protected:
    enum XmlType
    {
        XmlFile,
        XmlNode
    };

    XmlSerializer(ActionType _type, ErrorAction _errorAction, XmlType _xmlType);
    using Serializer::serialize;
    using Serializer::deserialize;

    virtual ~XmlSerializer();

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

    QString getTypeName(const QString &_nodeName);
    QString getKey(const QString &_nodeName);

    const QString &getVersion() const;
    static QString parseVersion(const QString &_string);
    void deleteIfExists(const QString &_nodeName) override;

    QVariant encode(const QVariant &_val);
    QVariant decode(const QVariant &_val);

public:
    static QDomDocumentFragment saveToElement(const QVariant &_value);
};

}
