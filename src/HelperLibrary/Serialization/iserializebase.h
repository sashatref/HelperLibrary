#pragma once

#include <QStringList>

#include "serpropertyinfo.h"

namespace SerializerQt
{

class ISerializeBase
{
public:
    virtual void propertyMap(QMap<QString, SerPropertyInfo> &_m) const
    {
        Q_UNUSED(_m);
    }
};

}
