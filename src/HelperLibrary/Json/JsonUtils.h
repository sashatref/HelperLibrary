#pragma once

#include "../export.h"

#include <QVariantList>
#include <QJsonDocument>

namespace JsonUtils
{
    template<class Type>
    bool toFile(const Type &_v, const QString &_filePath)
    {
        QFile f(_filePath);
        if(!f.open(QIODevice::WriteOnly))
        {
            return false;
        }

        f.write(QJsonDocument::fromVariant(toVariant(_v)).toJson());

        return true;
    }

    template<class Type>
    bool fromFile(Type &_v, const QString &_filePath)
    {
        QFile f(_filePath);
        if(!f.open(QIODevice::ReadOnly))
        {
            return false;
        }

        QVariant v = QJsonDocument::fromJson(f.readAll()).toVariant();
        fromVariant(v, _v);

        return true;
    }

    template<class Type>
    QString toString(const Type &_v)
    {
        return QJsonDocument::fromVariant(toVariant(_v)).toJson();
    }

    template<class Type>
    void fromString(const QString &_json, Type &_v)
    {
        fromVariant(QJsonDocument::fromJson(_json.toUtf8()).toVariant(), _v);
    }

    template<class Type>
    QVariant toVariant(const std::vector<Type> &v)
    {
        QVariantList out;

        for(auto &it : v)
        {
            out << toVariant(it);
        }

        return out;
    }

    template<class Type>
    QVariant toVariant(const QList<Type> &v)
    {
        return toVariant(v.toVector().toStdVector());
    }

    template<class Type>
    QVariant toVariant(const QVector<Type> &v)
    {
        return toVariant(v.toStdVector());
    }

    template<class Type>
    QVariant toVariant(const std::map<int, Type> &v)
    {
        QVariantMap out;

        for(auto &it : v)
        {
            out[QString::number(it.first)] = toVariant(it.second);
        }

        return out;
    }

    template<class Type>
    void fromVariant(const QVariant &_variant, std::map<int, Type> &_value)
    {
        _value.clear();

        const QVariantMap m = _variant.toMap();

        for(auto it = m.begin(); it != m.end(); ++it)
        {
            Type t;
            fromVariant(it.value(), t);

            _value[it.key().toInt()] = t;
        }
    }

    template<class Type>
    QVariant toVariant(const std::map<QString, Type> &v)
    {
        QVariantMap out;

        for(auto &it : v)
        {
            out[it.first] = toVariant(it.second);
        }

        return out;
    }

    template<class Type>
    void fromVariant(const QVariant &_variant, std::map<QString, Type> &_value)
    {
        _value.clear();

        const QVariantMap m = _variant.toMap();

        for(auto it = m.begin(); it != m.end(); ++it)
        {
            Type t;
            fromVariant(it.value(), t);

            _value[it.key()] = t;
        }
    }

    template<class Type>
    QVariant toVariant(const QMap<QString, Type> &v)
    {
        return toVariant(v.toStdMap());
    }

    template<class Type>
    void fromVariant(const QVariant &_variant, QMap<QString, Type> &_value)
    {
        _value.clear();

        const QVariantMap m = _variant.toMap();

        for(auto it = m.begin(); it != m.end(); ++it)
        {
            Type t;
            fromVariant(it.value(), t);

            _value[it.key()] = t;
        }
    }

    template<class Type>
    void fromVariant(const QVariant &_variant, std::vector<Type> &_value)
    {
        _value.clear();

        const QVariantList m = _variant.toList();

        for(auto &it : m)
        {
            Type t;
            fromVariant(it, t);
            _value.push_back(t);
        }
    }

    template<class Type>
    void fromVariant(const QVariant &_variant, QList<Type> &_value)
    {
        _value.clear();

        const QVariantList m = _variant.toList();

        for(auto &it : m)
        {
            Type t;
            fromVariant(it, t);
            _value.push_back(t);
        }
    }

    template<class Type>
    void fromVariant(const QVariant &_variant, QVector<Type> &_value)
    {
        _value.clear();

        const QVariantList m = _variant.toList();

        for(auto &it : m)
        {
            Type t;
            fromVariant(it, t);
            _value.push_back(t);
        }
    }


    template<class Type>
    QVariant toVariant(const QMap<int, Type> &v)
    {
        QVariantMap out;

        for(auto it = v.begin(); it != v.end(); ++it)
        {
            out[QString::number(it.key())] = toVariant(it.value());
        }

        return out;
    }

    template<class Type>
    void fromVariant(const QVariant &_variant, QMap<int, Type> &_value)
    {
        _value.clear();

        const QVariantMap m = _variant.toMap();

        for(auto it = m.begin(); it != m.end(); ++it)
        {
            Type t;
            fromVariant(it.value(), t);

            _value[it.key().toInt()] = t;
        }
    }

    template<class Type>
    QVariant toVariant(const QSet<Type> &v)
    {
        return toVariant(v.toList());
    }

    template<class Type>
    void fromVariant(const QVariant &_variant, QSet<Type> &_value)
    {
        _value.clear();

        QList<Type> out;
        fromVariant(_variant, out);
        _value = out.toSet();
    }

    QVariant HELPERLIBRARY_EXPORT toVariant(const int &_v);
    QVariant HELPERLIBRARY_EXPORT toVariant(const QString &_v);
    QVariant HELPERLIBRARY_EXPORT toVariant(const bool &_v);
    QVariant HELPERLIBRARY_EXPORT toVariant(const double &_v);
    QVariant HELPERLIBRARY_EXPORT toVariant(const QVariant &_v);
    QVariant HELPERLIBRARY_EXPORT toVariant(const QVariantMap &_v);
    QVariant HELPERLIBRARY_EXPORT toVariant(const QDate &_v);
    QVariant HELPERLIBRARY_EXPORT toVariant(const QTime &_v);
    QVariant HELPERLIBRARY_EXPORT toVariant(const QDateTime &_v);
    QVariant HELPERLIBRARY_EXPORT toVariant(const QRect &_v);
    QVariant HELPERLIBRARY_EXPORT toVariant(const QSize &_v);
    QVariant HELPERLIBRARY_EXPORT toVariant(const QPoint &_v);
    QVariant HELPERLIBRARY_EXPORT toVariant(const QByteArray &_v);

    void HELPERLIBRARY_EXPORT fromVariant(const QVariant &_variant, int &_value);
    void HELPERLIBRARY_EXPORT fromVariant(const QVariant &_variant, QString &_value);
    void HELPERLIBRARY_EXPORT fromVariant(const QVariant &_variant, bool &_value);
    void HELPERLIBRARY_EXPORT fromVariant(const QVariant &_variant, double &_value);
    void HELPERLIBRARY_EXPORT fromVariant(const QVariant &_variant, QVariant &_value);
    void HELPERLIBRARY_EXPORT fromVariant(const QVariant &_variant, QVariantMap &_value);
    void HELPERLIBRARY_EXPORT fromVariant(const QVariant &_variant, QDate &_value);
    void HELPERLIBRARY_EXPORT fromVariant(const QVariant &_variant, QTime &_value);
    void HELPERLIBRARY_EXPORT fromVariant(const QVariant &_variant, QDateTime &_value);
    void HELPERLIBRARY_EXPORT fromVariant(const QVariant &_variant, QRect &_value);
    void HELPERLIBRARY_EXPORT fromVariant(const QVariant &_variant, QSize &_value);
    void HELPERLIBRARY_EXPORT fromVariant(const QVariant &_variant, QPoint &_value);
    void HELPERLIBRARY_EXPORT fromVariant(const QVariant &_variant, QByteArray &_value);
}
