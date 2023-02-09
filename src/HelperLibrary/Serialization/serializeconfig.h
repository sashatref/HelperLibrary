#ifndef SERIALIZECONFIG_H
#define SERIALIZECONFIG_H

#include "../export.h"
#include "iconverter.h"

namespace SerializerQt
{

class HELPERLIBRARY_EXPORT SerializeConfig
{
    SerializeConfig() = default;
    ~SerializeConfig() = default;

    QMap<int, QSharedPointer<IConverter>> m_converters;
public:
    static SerializeConfig *get();

    void registerConverter(int _type, IConverter *_func);

    IConverter *getConverter(int _type);
};

}

#endif // SERIALIZECONFIG_H
