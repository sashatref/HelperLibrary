#pragma once

struct ByteArrayWrapper
{
    QByteArray data;

    bool operator!=(const ByteArrayWrapper &v) const
    {
        return data != v.data;
    }
};

namespace Randomizer
{
    ByteArrayWrapper &rand(ByteArrayWrapper &v);
}

namespace JsonUtils
{
    QVariant toVariant(const ByteArrayWrapper &v);
    void fromVariant(const QVariant &_variant, ByteArrayWrapper &_value);
}
