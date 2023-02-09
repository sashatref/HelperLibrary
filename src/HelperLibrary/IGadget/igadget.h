#pragma once

#include "../export.h"

#include <QVariant>

class HELPERLIBRARY_EXPORT IGadget
{
public:
    virtual const QMetaObject *getMetaObject() const = 0;
    virtual IGadget *getPrivateGadget() const;
    virtual ~IGadget() {}
    virtual IGadget *createNew() const;
    virtual IGadget *clone() const;
    virtual QString classDescription() const;

    QString tr(const char *sourceText, const char *disambiguation = Q_NULLPTR, int n = -1) const;

    virtual void setProperty(const QString &_propertyName, const QVariant &_value);
    virtual QVariant getProperty(const QString &_propertyName) const;
    QStringList getPropertyNameList() const;
};

namespace GadgetHelper
{
    IGadget HELPERLIBRARY_EXPORT *getIGadget(QVariant &_value, bool _throwException = true);
    IGadget HELPERLIBRARY_EXPORT *getIGadget(const QVariant &_value, bool _throwException = true);

    QVariantMap HELPERLIBRARY_EXPORT toMap(const IGadget *_gadget, const QStringList &_fields = QStringList());
    void HELPERLIBRARY_EXPORT fromMap(IGadget *_gadget, const QVariantMap &_props);

    QString HELPERLIBRARY_EXPORT getClassDescription(const QVariant &_val);

    template<class T>
    T* castObject(IGadget *const _gadget)
    {
        if(_gadget == nullptr) return nullptr;

        T *base = dynamic_cast<T*>(_gadget);
        if(base) return base;

        IGadget *subGadget = _gadget->getPrivateGadget();
        base = dynamic_cast<T*>(subGadget);

        return base;
    }

    //регистрирует конвертер к IGadget* в метасистеме
    template<class T>
    void registerToIGadgetConverter()
    {
        if(!QMetaType::hasRegisteredConverterFunction<T, IGadget*>())
        {
            QMetaType::registerConverter<T, IGadget*>([](const T &_value) -> IGadget*
            {
                return const_cast<T*>(&_value);
            });
        }
    }

    template<class T>
    void registerToIGadgetConverterStar()
    {
        if(!QMetaType::hasRegisteredConverterFunction<T*, IGadget*>())
        {
            QMetaType::registerConverter<T*, IGadget*>([](const T *_value) -> IGadget*
            {
                return const_cast<T*>(_value);
            });
        }
    }
}

Q_DECLARE_METATYPE(IGadget*)

#define DEFINE_MO    \
    virtual const QMetaObject *getMetaObject() const override\
    {\
        return &staticMetaObject;\
    }

