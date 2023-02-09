#include "jsonmessage.h"

namespace JsonProtocolNS
{

JsonMessage::JsonMessage(const QString &_command, const QVariant &_value):
    command (_command),
    value   (_value)
{

}

}
