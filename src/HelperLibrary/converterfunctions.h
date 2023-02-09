#pragma once

#include <QMap>
#include <QString>
#include <QVariantMap>
#include <QMutex>

#include "export.h"
#include "mylist.hpp"
#include "myvector.hpp"

struct HELPERLIBRARY_EXPORT ContainerTypes
{
    static ContainerTypes &ins();

    template<class Container, class Element>
    void registerArray()
    {
        registerArray(qMetaTypeId<Container>(), qMetaTypeId<Element>());
    }

    template<class Container, class Key, class Element>
    void registerMap()
    {
        registerMap(qMetaTypeId<Container>(), qMetaTypeId<Key>(), qMetaTypeId<Element>());
    }

    void registerArray(int _containerType, int _elementType);
    void registerMap(int _containerType, int _keyType, int _elementType);

    int getElementTypeForContainer(int _containerType) const;
    QPair<int, int> getTypesForMap(int _containerType) const;

private:
    ContainerTypes() = default;
    Q_DISABLE_COPY(ContainerTypes)

    QMap<int, int> m_arrayTypes;    // container type, element type
    QMap<int, QPair<int, int>> m_mapTypes;  //container type , key type, value type
    mutable QMutex m_mutex;
};

namespace Converters
{
    QStringList HELPERLIBRARY_EXPORT convertToStringList(const QList<int> &_list);

    template<class T>
    void initFromVariant(T &_value, const QVariant &_var)
    {
        _value = _var.value<T>();
    }

    //конвертирование QVariantMap в QMap<T1, T2>
    template<class T1, class T2>
    QMap<T1, T2> variantMapToMap(const QVariantMap &_input)
    {
        QMap<T1, T2> output;

        for(auto it = _input.begin(); it != _input.end(); ++it)
        {
            output[QVariant(it.key()).value<T1>()] = it.value().value<T2>();
        }

        return output;
    }

    //регистрирует конвертерт QVariantMap => QMap<T1, T2> в метасистеме
    template<class T1, class T2>
    void registerVariantMapToMapConverter()
    {
        ContainerTypes::ins().registerMap<QMap<T1, T2>, T1, T2>();
        if(!QMetaType::hasRegisteredConverterFunction<QVariantMap, QMap<T1, T2>>())
        {
            QMetaType::registerConverter<QVariantMap, QMap<T1, T2>>(&variantMapToMap<T1, T2>);
        }
    }

    //регистрирует конвертрер QVariantMap => QMap<QString, bool> в метасистеме
    //частный случай предыдущего шаблона registerVariantMapToMapConverter
    void HELPERLIBRARY_EXPORT registerVariantMapToQStringBoolMapConverter();

    //регистрирует конвертер QVarianList => QVector<T> и QVector<T> => QVariantList
    //в метасистеме
    template<class T>
    void registerToVectorConverter()
    {
        ContainerTypes::ins().registerArray<QVector<T>, T>();

        if(!QMetaType::hasRegisteredConverterFunction<QVariantList, QVector<T>>())
        {
            QMetaType::registerConverter<QVariantList, QVector<T>>([](const QVariantList &_list) -> QVector<T>
            {
                int _listSize =  _list.size();
                QVector<T> output;
                output.reserve(_listSize);
                for(int i = 0 ; i < _listSize; i++)
                {
                    output.append(_list[i].value<T>());
                }
                return output;
            });
        }

        if(!QMetaType::hasRegisteredConverterFunction<QVector<T>, QVariantList>())
        {
            QMetaType::registerConverter<QVector<T>, QVariantList>([](const QVector<T> &_list) -> QVariantList
            {
                int _listSize =  _list.size();
                QVariantList output;
                output.reserve(_listSize);
                for(int i = 0 ; i < _listSize; i++)
                {
                    output.append(QVariant::fromValue(_list[i]));
                }
                return output;
            });
        }
    }


    //регистрирует конвертер QVarianList => QList<T> и QList<T> => QVariantList
    //в метасистеме
    template<class T>
    void registerToListConverter()
    {
        ContainerTypes::ins().registerArray<QList<T>, T>();

        if(!QMetaType::hasRegisteredConverterFunction<QVariantList, QList<T>>())
        {
            QMetaType::registerConverter<QVariantList, QList<T>>([](const QVariantList &_list) -> QList<T>
            {
                int _listSize =  _list.size();
                QList<T> output;
                output.reserve(_listSize);
                for(int i = 0 ; i < _listSize; i++)
                {
                    output.append(_list[i].value<T>());
                }
                return output;
            });
        }

        if(!QMetaType::hasRegisteredConverterFunction<QList<T>, QVariantList>())
        {
            QMetaType::registerConverter<QList<T>, QVariantList>([](const QList<T> &_list) -> QVariantList
            {
                int _listSize =  _list.size();
                QVariantList output;
                output.reserve(_listSize);
                for(int i = 0 ; i < _listSize; i++)
                {
                    output.append(QVariant::fromValue(_list[i]));
                }
                return output;
            });
        }
    }

    template<class T>
    void registerQSetConverter()
    {
        ContainerTypes::ins().registerArray<QSet<T>, T>();

        if(!QMetaType::hasRegisteredConverterFunction<QVariantList, QSet<T>>())
        {
            QMetaType::registerConverter<QVariantList, QSet<T>>([](const QVariantList &_list) -> QSet<T>
            {
                int _listSize =  _list.size();
                QSet<T> output;
                output.reserve(_listSize);
                for(int i = 0 ; i < _listSize; i++)
                {
                    output.insert(_list[i].value<T>());
                }
                return output;
            });
        }

        if(!QMetaType::hasRegisteredConverterFunction<QSet<T>, QVariantList>())
        {
            QMetaType::registerConverter<QSet<T>, QVariantList>([](const QSet<T> &_list) -> QVariantList
            {
                QVariantList output;
                foreach (const T &_item, _list)
                {
                    output.append(QVariant::fromValue(_item));
                }
                return output;
            });
        }
    }

    //регистрирует конвертер QVarianList => MyList<T> и MyList<T> => QVariantList
    //в метасистеме
    template<class T>
    void registerToMyListConverter()
    {
        ContainerTypes::ins().registerArray<LinqContainers::MyList<T>, T>();

        if(!QMetaType::hasRegisteredConverterFunction<QVariantList, LinqContainers::MyList<T>>())
        {
            QMetaType::registerConverter<QVariantList, LinqContainers::MyList<T>>([](const QVariantList &_list) -> LinqContainers::MyList<T>
            {
                LinqContainers::MyList<T> output;
                return output.fromVariantList(_list);
            });
        }

        if(!QMetaType::hasRegisteredConverterFunction<LinqContainers::MyList<T>, QVariantList>())
        {
            QMetaType::registerConverter<LinqContainers::MyList<T>, QVariantList>([](const LinqContainers::MyList<T> &_list) -> QVariantList
            {
                return _list.toVariantList();
            });
        }
    }

    //регистрирует конвертер QVarianList => MyVector<T> и MyVector<T> => QVariantList
    //в метасистеме
    template<class T>
    void registerToMyVectorConverter()
    {
        ContainerTypes::ins().registerArray<LinqContainers::MyVector<T>, T>();

        if(!QMetaType::hasRegisteredConverterFunction<QVariantList, LinqContainers::MyVector<T>>())
        {
            QMetaType::registerConverter<QVariantList, LinqContainers::MyVector<T>>([](const QVariantList &_list) -> LinqContainers::MyVector<T>
            {
                LinqContainers::MyVector<T> output;
                return output.fromVariantList(_list);
            });
        }

        if(!QMetaType::hasRegisteredConverterFunction<LinqContainers::MyVector<T>, QVariantList>())
        {
            QMetaType::registerConverter<LinqContainers::MyVector<T>, QVariantList>([](const LinqContainers::MyVector<T> &_list) -> QVariantList
            {
                return _list.toVariantList();
            });
        }
    }
}
