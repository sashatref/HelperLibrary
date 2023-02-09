#include "serializeconfig.h"

namespace SerializerQt
{

SerializeConfig *SerializeConfig::get()
{
    static SerializeConfig ins;
    return &ins;
}

void SerializeConfig::registerConverter(int _type, IConverter *_func)
{
    m_converters[_type] = QSharedPointer<IConverter>(_func);
}

IConverter *SerializeConfig::getConverter(int _type)
{
    return m_converters[_type].data();
}

}
