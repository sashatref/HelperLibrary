#pragma once

#include <functional>

namespace ContainerHelper
{
    template<class OutType, class InType>
    QList<OutType> mapArr(const QList<InType> &_list, std::function<OutType(const InType &_item)> _func)
    {
        QList<OutType> out;

        for(auto &item : _list)
        {
            out << _func(item);
        }

        return out;
    }


    template<class T1, class T2>
    QVector<T1> Convert(const QVector<T2> &_container, std::function<T1(const T2&)> conv_func)
    {
        QVector<T1> outputContainter;
        for(int i = 0 ; i < _container.size(); i++)
        {
            outputContainter.append(conv_func(_container.at(i)));
        }
        return outputContainter;
    }


    template<class T>
    QList<T> Select(const QList<T> &_container, std::function<bool(const T&)> if_func)
    {
        QList<T> outputContainter;
        for(int i = 0 ; i < _container.size(); i++)
        {
            if(if_func(_container.at(i)))
            {
                outputContainter.append(_container.at(i));
            }
        }
        return outputContainter;
    }

    template<class T>
    QVector<T> Select(const QVector<T> &_container, std::function<bool(const T&)> if_func)
    {
        QVector<T> outputContainter;
        for(int i = 0 ; i < _container.size(); i++)
        {
            if(if_func(_container.at(i)))
            {
                outputContainter.append(_container.at(i));
            }
        }
        return outputContainter;
    }

    template<class T>
    T FindLastItem(const QVector<T> &_container, std::function<bool(const T&)> if_func)
    {
        for(int i = _container.size() - 1 ; i > -1; i--)
        {
            if(if_func(_container.at(i)))
            {
                return _container.at(i);
            }
        }
        return T();
    }

    template<class T>
    QVariantMap toVariantMap(const QMap<QString, T> &_map)
    {
        QVariantMap resultMap;
        for(int i = 0 ; i < _map.keys().size(); i++)
        {
            resultMap.insert(_map.keys().at(i), QVariant::fromValue(_map[_map.keys().at(i)]));
        }
        return resultMap;
    }

    template<class T>
    QMap<QString, T> fromVariantMap(const QVariantMap &_map)
    {
        QMap<QString, T> resultMap;

        for(int i = 0 ; i < _map.keys().size(); i++)
        {
            resultMap.insert(_map.keys().at(i), _map[_map.keys().at(i)].value<T>());
        }
        return resultMap;
    }

    template<class T>
    QVector<T> fromVariantVector(const QVector<QVariant> &_vec)
    {
        QVector<T> resultVector;
        for(int i = 0 ; i < _vec.size(); i++)
        {
            resultVector.append(_vec[i].value<T>());
        }
        return resultVector;
    }

    template<class T>
    QVector<QVariant> toVariantVector(const QVector<T> &_vec)
    {
        QVector<QVariant> resultVector;
        for(int i = 0 ; i < _vec.size(); i++)
        {
            resultVector.append(QVariant::fromValue(_vec[i]));
        }
        return resultVector;
    }

    template<class T>
    QList<T> fromVariantList(const QList<QVariant> &_list)
    {
        QList<T> resultList;
        for(int i = 0 ; i < _list.size(); i++)
        {
            resultList.append(_list[i].value<T>());
        }
        return resultList;
    }

    template<class T>
    QList<QVariant> toVariantList(const QList<T> &_list)
    {
        QList<QVariant> resultList;
        for(int i = 0 ; i < _list.size(); i++)
        {
            resultList.append(QVariant::fromValue(_list[i]));
        }
        return resultList;
    }


    template <class Type>
    QList<QList<Type>> splitList(const QList<Type> &_source, int _maxItemCount)
    {
        QList<QList<Type>> out;

        int num = 0;
        for(int i = 0, count = _source.size(); i < count; i += _maxItemCount)
        {
            out << _source.mid(num * _maxItemCount, _maxItemCount);;
            num++;
        }

        return out;
    }

}
