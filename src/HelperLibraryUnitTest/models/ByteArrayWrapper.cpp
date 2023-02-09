#include "ByteArrayWrapper.h"


ByteArrayWrapper &Randomizer::rand(ByteArrayWrapper &v)
{
    rand(v.data);
    return v;
}

QVariant JsonUtils::toVariant(const ByteArrayWrapper &v)
{
    return QVariantMap {
        { "data", toVariant(v.data) }
    };
}

void JsonUtils::fromVariant(const QVariant &_variant, ByteArrayWrapper &_value)
{
    const QVariantMap m = _variant.toMap();

    fromVariant(m.value("data"), _value.data);
}
