#pragma once

#include "../export.h"
#include "jsonmessage.h"

namespace JsonProtocolNS
{

class HELPERLIBRARY_EXPORT JsonProtocolHelper
{
public:
    static JsonMessage parseMessage(const QVariantMap &_map);
    static JsonMessageList parseMessageList(const QVariantList &_list);

    static JsonMessageList parseJson(const QByteArray &_data);

    static QByteArray makeMessageList(const JsonMessageList &_list);
    static QByteArray makeMessage(const JsonMessage &_message);
    static QByteArray makeMessage(const QString &_command, const QVariant &_value);
};

}

