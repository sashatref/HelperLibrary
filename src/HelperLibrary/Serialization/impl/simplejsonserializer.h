#pragma once

#include "../serializer.h"

namespace SerializerQt
{

class SimpleJsonSerializerPrivate;

class HELPERLIBRARY_EXPORT SimpleJsonSerializer : public Serializer
{
    friend class Serializer;
    friend class SimpleJsonSerializerPrivate;
    SimpleJsonSerializerPrivate * const d;

public:
    SimpleJsonSerializer(ActionType _type, ErrorAction _errorAction);

    using Serializer::serialize;
    using Serializer::deserialize;
    virtual ~SimpleJsonSerializer();

    virtual bool serialize(const QVariantMap &_valueMap, const QString &_nodeName, const QString &_containerType, const QString &_key) override;
    virtual bool serialize(const QVariantList &_valueList, const QString &_nodeName, const QString &_containerType, const QString &_key) override;
    virtual bool serialize(const QVariant &_value, const QString &_nodeName, const QString &_key) override;
    virtual bool serialize(const QString &_value, const QString &_nodeName, const QString &_typeName, const QString &_key) override;
    virtual bool deserialize(QString &_value, const QString &_nodeName, QString &_typeName) override;
    virtual bool deserialize(QVariant &_value, const QString &_nodeName) override;
    virtual bool deserialize(QVariantList &_value, const QString &_nodeName) override;
    virtual bool deserialize(QVariantMap &_value, const QString &_nodeName) override;

protected:
    virtual QByteArray saveToByteArray() const override;
    virtual void loadFromByteArray(const QByteArray &_content) override;
};

}
