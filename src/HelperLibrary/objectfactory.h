#pragma once

#include <QMap>
#include <QDebug>

#include <functional>

template <class Base, class TypeId, class CreateFunc = std::function<Base*()>>
class ObjectFactory
{
protected:
    QMap<TypeId, CreateFunc> m_factory;

public:
    ObjectFactory()
    {

    }

    virtual ~ObjectFactory()
    {

    }


    QList<TypeId> keys() const
    {
        return m_factory.keys();
    }

    template <class C>
    void add(const TypeId &_typeId)
    {
        m_factory[_typeId] = [](){return new C();};
    }

    void add(const TypeId &_typeId, CreateFunc _createFunc)
    {
        m_factory[_typeId] = _createFunc;
    }

    void remove(const TypeId &_typeId)
    {
        if(m_factory.contains(_typeId))
        {
            m_factory.remove(_typeId);
        }
    }

    bool isRegistered(const TypeId &_typeId)
    {
        return m_factory.contains(_typeId);
    }

    Base *create(const TypeId &_typeId) const
    {
        if(m_factory.contains(_typeId))
        {
            return m_factory[_typeId]();
        } else
        {
            qDebug() << QString("Type: %1 not registered!").arg(_typeId);
            return 0;
        }
    }

    template <class T1>
    Base *create(const TypeId &_typeId, T1 _param1) const
    {
        if(m_factory.contains(_typeId))
        {
            return m_factory[_typeId](_param1);
        } else
        {
            qDebug() << QString("Type: %1 not registered!").arg(_typeId);
            return 0;
        }
    }

    template <class T1, class T2>
    Base *create(const TypeId &_typeId, T1 _param1, T2 _param2) const
    {
        if(m_factory.contains(_typeId))
        {
            return m_factory[_typeId](_param1, _param2);
        } else
        {
            qDebug() << QString("Type: %1 not registered!").arg(_typeId);
            return 0;
        }
    }

    template <class T1, class T2, class T3>
    Base *create(const TypeId &_typeId, T1 _param1, T2 _param2, T3 _param3) const
    {
        if(m_factory.contains(_typeId))
        {
            return m_factory[_typeId](_param1, _param2, _param3);
        } else
        {
            qDebug() << QString("Type: %1 not registered!").arg(_typeId);
            return 0;
        }
    }

    template <class T1, class T2, class T3, class T4>
    Base *create(const TypeId &_typeId, T1 _param1, T2 _param2, T3 _param3, T4 _param4) const
    {
        if(m_factory.contains(_typeId))
        {
            return m_factory[_typeId](_param1, _param2, _param3, _param4);
        } else
        {
            qDebug() << QString("Type: %1 not registered!").arg(_typeId);
            return 0;
        }
    }


private:
    ObjectFactory(const ObjectFactory&);
    ObjectFactory& operator = (const ObjectFactory&);
};
