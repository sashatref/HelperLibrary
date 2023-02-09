#include "project_pch.h"
#include "igadget.h"

#include "Exceptions/userexception.h"

namespace GadgetHelper
{

IGadget *getIGadget(QVariant &_value, bool _throwException)
{
    IGadget *obj = _value.value<IGadget*>();
    if(!obj)
    {
        if(_throwException)
        {
            throw HelperLibrary::UserExceptions::ToIGadgetException(_value.typeName());
        }
    }

    return obj;
}



IGadget *getIGadget(const QVariant &_value, bool _throwException)
{
    IGadget *obj = _value.value<IGadget*>();
    if(!obj)
    {
        if(_throwException)
        {
            throw HelperLibrary::UserExceptions::ToIGadgetException(_value.typeName());
        }
    }

    return obj;
}


QVariantMap toMap(const IGadget *_gadget, const QStringList &_fields)
{
    QVariantMap out;

    const QMetaObject *mo = _gadget->getMetaObject();


    QStringList props = _fields.isEmpty() ? _gadget->getPropertyNameList() : _fields;
    for(int i = 0 ; i < props.size(); i++)
    {
        int propIndex = mo->indexOfProperty(props[i].toStdString().c_str());
        QMetaProperty property = mo->property(propIndex);
        QVariant val = _gadget->getProperty(props.at(i));
        bool isUserType = val.userType() > (int)QVariant::UserType;

        if(property.isEnumType())
        {
            if(val.canConvert<int>())
            {
                val.convert(qMetaTypeId<int>());
            }
        }

        if(isUserType)
        {
            if(val.canConvert<QString>())
            {
                val.convert(qMetaTypeId<QString>());
            }else if(val.canConvert<int>())
            {
                val.convert(qMetaTypeId<int>());
            }
        }

        out[props.at(i)] = val;
    }

    return out;
}

void fromMap(IGadget *_gadget, const QVariantMap &_props)
{
    const QMetaObject *mo = _gadget->getMetaObject();

    for(auto it = _props.begin(); it != _props.end(); ++it)
    {
        int propIndex = mo->indexOfProperty(it.key().toStdString().c_str());
        if(propIndex == -1)
        {
            continue;
        }

        QVariant newValue = it.value();

        QMetaProperty prop = mo->property(propIndex);

        if(!prop.isWritable())
        {
            continue;
        }

        if(prop.isEnumType())
        {
            newValue.convert(qMetaTypeId<int>());
        }

        _gadget->setProperty(it.key(), newValue);
    }
}

QString getClassDescription(const QVariant &_val)
{
    QString desc;

    const IGadget *gad = _val.value<IGadget*>();

    if(gad)
    {
        desc = gad->classDescription();
    }

    return desc;
}

}

IGadget *IGadget::getPrivateGadget() const
{
    return 0;
}

IGadget *IGadget::createNew() const
{
    qWarning() << QString("Method <createNew> not implemented in class <%1>").arg(getMetaObject()->className());
    return 0;
}

IGadget *IGadget::clone() const
{
    qWarning() << QString("Method <clone> not implemented in class <%1>").arg(getMetaObject()->className());
    return 0;
}

QString IGadget::classDescription() const
{
    return getMetaObject()->className();
}

QString IGadget::tr(const char *sourceText, const char *disambiguation, int n) const
{
    return QCoreApplication::translate(this->getMetaObject()->className(), sourceText, disambiguation, n);
}

void IGadget::setProperty(const QString &_propertyName, const QVariant &_value)
{
    const QMetaObject *mo = getMetaObject();

    int index = mo->indexOfProperty(_propertyName.toStdString().c_str());
    if(index != -1)
    {
        if(!mo->property(index).writeOnGadget(this, _value))
        {
            qWarning() << QString("Can't set property <%1> - <%2> with value <%3> - <%4>")
                          .arg(_propertyName)
                          .arg(mo->property(index).typeName())
                          .arg(_value.typeName())
                          .arg(_value.toString());
        }
    } else
    {
        qWarning() << QString("Property <%1> not found on Class <%2>")
                      .arg(_propertyName)
                      .arg(mo->className());
    }
}

QVariant IGadget::getProperty(const QString &_propertyName) const
{
    const QMetaObject *mo = getMetaObject();

    int index = mo->indexOfProperty(_propertyName.toStdString().c_str());
    if(index != -1)
    {
        return mo->property(index).readOnGadget(this);
    }

    return QVariant();
}

QStringList IGadget::getPropertyNameList() const
{
    const QMetaObject *mo = getMetaObject();

    QStringList out;

    for(int i = mo->propertyOffset(); i < mo->propertyCount(); i++)
    {
        out << mo->property(i).name();
    }
    return out;
}
