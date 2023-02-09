#pragma once
#include "../igadget.h"

namespace GadgetHelper
{

class HELPERLIBRARY_EXPORT VariantMapHelper
{
public:
    VariantMapHelper();
    ~VariantMapHelper();

    QVariantList toList(const QVariantList &_gadgetList);

    template<class Type>
    QVariantList toList(const QList<Type> &_gadgetList)
    {
        QVariantList out;

        for(const auto &item : qAsConst(_gadgetList))
        {
            out << toMap(&item);
        }

        return out;
    }

    QVariantMap toMap(const QVariant &_gadgetItem);

    QVariantMap toMap(const IGadget *_gadget, const QStringList &_fields = QStringList());
    void fromMap(IGadget *_gadget, const QVariantMap &_props);
};

}
