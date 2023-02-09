#pragma once

#include "../export.h"

#include <QCoreApplication>

namespace HelperLibraryNS
{

//template<class InterfaceType>
//class BaseDecorator
//{
//public:
//    using Func = std::function<InterfaceType*(const QVariant &)>;
//    template<class ClassType>
//    using ClassFunc = InterfaceType* (ClassType::*)(const QVariant&);


//    template <class Type, class ClassType>
//    void registerHandler(ClassType *_object, ClassFunc<ClassType> _func)
//    {
//        auto newFunc = std::bind(_func, _object, std::placeholders::_1);
//        registerHandler(qMetaTypeId<Type>(), newFunc);
//    }

//    void registerHandler(int _type, Func _func)
//    {
//        m_factory[_type] = _func;
//    }

//    InterfaceType* createIntefaceInst(int _type, const QVariant &_value)
//    {
//        auto it = m_factory.find(_type);
//        if(it != m_factory.end())
//        {
//            return it.value()(_value);
//        }

//        return 0;
//    }

//private:
//     QMap<int, Func> m_factory;
//};

template<class DecoratorType>
class BaseDecoratorFactory
{
public:
    using CreatorFunc = std::function<DecoratorType*()>;

    template<class Type, class TableBaseType>
    void add()
    {
        add(qMetaTypeId<Type>(), []{return new TableBaseType();});
    }

    void add(int _type, CreatorFunc _func)
    {
        m_funcMap[_type] = _func;
    }

    template<class TableBaseType>
    void add(int _metaType)
    {
        add(_metaType, []{return new TableBaseType();});
    }

    QSharedPointer<DecoratorType> create(int _type)
    {
        auto it = m_funcMap.find(_type);
        if(it == m_funcMap.end())
        {
            return QSharedPointer<DecoratorType>();
        }

        return QSharedPointer<DecoratorType>(it.value()());
    }
private:
    QMap<int, CreatorFunc> m_funcMap;
};
}
