#include "JsonUtils.h"

namespace JsonUtils
{



QVariant toVariant(const int &_v)
{
    return QVariant(_v);
}

QVariant toVariant(const double &_v)
{
    return QVariant(_v);
}

QVariant toVariant(const QString &_v)
{
    return _v;
}

QVariant toVariant(const bool &_v)
{
    return _v;
}

void fromVariant(const QVariant &_variant, int &_value)
{
    _value = _variant.toInt();
}

void fromVariant(const QVariant &_variant, QString &_value)
{
    _value = _variant.toString();
}

void fromVariant(const QVariant &_variant, bool &_value)
{
    _value = _variant.toBool();
}

void fromVariant(const QVariant &_variant, double &_value)
{
    _value = _variant.toDouble();
}

QVariant toVariant(const QVariant &_v)
{
    return _v;
}

void fromVariant(const QVariant &_variant, QVariant &_value)
{
    _value = _variant;
}

QVariant toVariant(const QVariantMap &_v)
{
    return _v;
}

void fromVariant(const QVariant &_variant, QVariantMap &_value)
{
    _value = _variant.toMap();
}

QVariant toVariant(const QDate &_d)
{
    return _d.toString("dd.MM.yyyy");
}

QVariant toVariant(const QDateTime &_d)
{
    return _d.toString("dd.MM.yyyy hh:mm:ss.zzz");
}

QVariant toVariant(const QTime &_v)
{
    return _v.toString("hh:mm:ss.zzz");
}

void fromVariant(const QVariant &_variant, QDate &_value)
{
    _value = QDate::fromString(_variant.toString(), "dd.MM.yyyy");
}

void fromVariant(const QVariant &_variant, QTime &_value)
{
    _value = QTime::fromString(_variant.toString(), "hh:mm:ss.zzz");
}

void fromVariant(const QVariant &_variant, QDateTime &_value)
{
    _value = QDateTime::fromString(_variant.toString(), "dd.MM.yyyy hh:mm:ss.zzz");
}

QVariant toVariant(const QRect &_v)
{
    return QVariantMap {
        { "x", _v.x() },
        { "y", _v.y() },
        { "w", _v.width() },
        { "h", _v.height() }
    };
}

void fromVariant(const QVariant &_variant, QRect &_value)
{
    const QVariantMap m = _variant.toMap();

    _value = QRect(m.value("x").toInt(),
                   m.value("y").toInt(),
                   m.value("w").toInt(),
                   m.value("h").toInt());
}

QVariant toVariant(const QSize &_v)
{
    return QVariantMap {
        { "w", _v.width() },
        { "h", _v.height() }
    };
}

void fromVariant(const QVariant &_variant, QSize &_value)
{
    const QVariantMap m = _variant.toMap();

    _value = QSize(m.value("w").toInt(),
                   m.value("h").toInt());
}

QVariant toVariant(const QPoint &_v)
{
    return QVariantMap {
        { "x", _v.x() },
        { "y", _v.y() }
    };
}

void fromVariant(const QVariant &_variant, QPoint &_value)
{
    const QVariantMap m = _variant.toMap();

    _value = QPoint(m.value("x").toInt(),
                    m.value("y").toInt());
}

QVariant toVariant(const QByteArray &_v)
{
    return QString::fromUtf8(_v.toBase64());
}

void fromVariant(const QVariant &_variant, QByteArray &_value)
{
    _value = QByteArray::fromBase64(_variant.toString().toUtf8());
}

}

