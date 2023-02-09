#pragma once

#include "export.h"

namespace Randomizer
{
    template<class Type>
    Type createRand()
    {
        Type out;
        rand(out);
        return out;
    }

    template<class Type>
    QList<Type> createArr(int _minCount, int _maxCount)
    {
        int count = 0;
        rand(count, _minCount, _maxCount);

        QList<Type> out;

        for(int i = 0 ; i < count; i++)
        {
            Type v;
            rand(v);
            out << v;
        }

        return out;
    }

    template<class Type>
    QList<Type> & rand(QList<Type> &_v, int _minCount = 3, int _maxCount = 8)
    {
        _v = createArr<Type>(_minCount, _maxCount);
        return _v;
    }

    template<class Type>
    std::vector<Type> & rand(std::vector<Type> &_v, int _minCount = 3, int _maxCount = 8)
    {
        _v = createArr<Type>(_minCount, _maxCount).toVector().toStdVector();
        return _v;
    }

    template<class Type>
    QVector<Type> & rand(QVector<Type> &_v, int _minCount = 3, int _maxCount = 8)
    {
        _v = createArr<Type>(_minCount, _maxCount).toVector();
        return _v;
    }

    template<class Type>
    QSet<Type> & rand(QSet<Type> &_v, int _minCount = 3, int _maxCount = 8)
    {
        _v = createArr<Type>(_minCount, _maxCount).toSet();
        return _v;
    }

    template<class Key, class Value>
    QMap<Key, Value> & rand(QMap<Key, Value> &_v, int _minCount = 3, int _maxCount = 8)
    {
        _v.clear();

        int num = 0;
        rand(num, _minCount, _maxCount);

        for(int i = 0 ; i < num; i++)
        {
            Key key;
            Value value;
            rand(key);
            rand(value);
            _v[key] = value;
        }

        return _v;
    }

    template<class Key, class Value>
    std::map<Key, Value> & rand(std::map<Key, Value> &_v, int _minCount = 3, int _maxCount = 8)
    {
        QMap<Key, Value> qtMap;
        rand(qtMap, _minCount, _maxCount);
        _v = qtMap.toStdMap();
        return _v;
    }

    template<class EnumType>
    EnumType &randEnum(EnumType &_v, EnumType _min, EnumType _max)
    {
        int temp = 0;
        rand(temp, _min, _max);
        _v = static_cast<EnumType>(temp);
        return _v;
    }

//    template<class EnumType>
//    EnumType &randEnum(QFlags<EnumType> &_v, EnumType _min, EnumType _max)
//    {
//        _v.

//        int temp = 0;
//        rand(temp, _min, _max);
//        _v.Int = static_cast<EnumType>(temp);
//        return _v;
//    }

    bool HELPERLIBRARY_EXPORT & rand(bool &_v);
    char HELPERLIBRARY_EXPORT & rand(char &_v, char _min = -128, char _max = 127);
    int HELPERLIBRARY_EXPORT & rand(int &_v, int _min = 0, int _max = 1000000);
    double HELPERLIBRARY_EXPORT & rand(double &_v, double _min = 0, double _max = 1000000);
    QString HELPERLIBRARY_EXPORT & rand(QString &_v, int _minLen = 3, int _maxLen = 8);
    std::string HELPERLIBRARY_EXPORT & rand(std::string &_v, int _minLen = 3, int _maxLen = 8);
    QByteArray HELPERLIBRARY_EXPORT & rand(QByteArray &_v, int _minLen = 3, int _maxLen = 50);
    QDate HELPERLIBRARY_EXPORT & rand(QDate &_v);
    QDateTime HELPERLIBRARY_EXPORT & rand(QDateTime &_v);
    QTime HELPERLIBRARY_EXPORT & rand(QTime &_v);

    QRect HELPERLIBRARY_EXPORT & rand(QRect &_v);
    QPoint HELPERLIBRARY_EXPORT & rand(QPoint &_v);
    QSize HELPERLIBRARY_EXPORT & rand(QSize &_v);


}

