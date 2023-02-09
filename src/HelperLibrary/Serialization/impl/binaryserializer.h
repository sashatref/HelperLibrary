#pragma once

#include "../serializer.h"

namespace SerializerQt
{

class BinarySerializerPrivate;

class HELPERLIBRARY_EXPORT BinarySerializer : public Serializer
{
    friend class Serializer;
    friend class BinarySerializerPrivate;
    BinarySerializerPrivate * const d;

protected:
    BinarySerializer(ActionType _type, ErrorAction _errorAction);
    using Serializer::serialize;
    using Serializer::deserialize;
    virtual ~BinarySerializer();

    bool serialize(const QVariantMap &_valueMap, const QString &_nodeName, const QString &_containerType, const QString &_key) override;
    bool serialize(const QVariantList &_valueList, const QString &_nodeName, const QString &_containerType, const QString &_key) override;
    bool serialize(const QVariant &_value, const QString &_nodeName,const QString &_key) override;
    bool serialize(const QString &_value, const QString &_nodeName, const QString &_typeName, const QString &_key) override;
    bool deserialize(QString &_value, const QString &_nodeName, QString &_typeName) override;
    bool deserialize(QVariant &_value, const QString &_nodeName) override;
    bool deserialize(QVariantList &_value, const QString &_nodeName) override;
    bool deserialize(QVariantMap &_value, const QString &_nodeName) override;

    QByteArray saveToByteArray() const override;
    void loadFromByteArray(const QByteArray &_content) override;

    QString getTypeName(const QString &_nodeName);
    QString getKey(const QString &_nodeName);


};
}

