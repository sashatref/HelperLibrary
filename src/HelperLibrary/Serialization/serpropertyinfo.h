#ifndef SERPROPERTYINFO_H
#define SERPROPERTYINFO_H

#include <QString>
#include <QMap>

namespace SerializerQt
{

class SerPropertyInfo
{
public:
    bool isSkipped = false;
    bool isEncoded = false;
};

typedef QMap<QString, SerPropertyInfo> SerPropertyMap;

}

#endif // SERPROPERTYINFO_H
