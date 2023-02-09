#include "jsonprotocolhelper.h"

#include <QJsonParseError>

namespace JsonProtocolNS
{

JsonMessage JsonProtocolHelper::parseMessage(const QVariantMap &_map)
{
    return JsonMessage(_map["command"].toString(), _map["value"]);
}

JsonMessageList JsonProtocolHelper::parseMessageList(const QVariantList &_list)
{
    JsonMessageList out;

    for(auto &item : _list)
    {
        out << parseMessage(item.toMap());
    }

    return out;
}

JsonMessageList JsonProtocolHelper::parseJson(const QByteArray &_data)
{
    JsonMessageList out;

    QJsonParseError errorParse;
    QVariant var = QJsonDocument::fromJson(_data, &errorParse).toVariant();

    if(errorParse.error != QJsonParseError::NoError)
    {
        qWarning() << __FUNCTION__ << " | " << errorParse.errorString();
    }

    if(var.canConvert<QVariantList>())
    {
        out = parseMessageList(var.toList());
    }

    if(var.canConvert<QVariantMap>())
    {
        out << parseMessage(var.toMap());
    }

    return out;
}

QByteArray JsonProtocolHelper::makeMessageList(const JsonMessageList &_list)
{
    QVariantList list;

    for(auto &item : _list)
    {
        QVariantMap mapItem;
        mapItem["command"] = item.command;
        mapItem["value"] = item.value;
        list << mapItem;
    }

    return QJsonDocument::fromVariant(list).toJson(QJsonDocument::Compact);
}

QByteArray JsonProtocolHelper::makeMessage(const JsonMessage &_message)
{
    return makeMessageList(JsonMessageList() << _message);
}

QByteArray JsonProtocolHelper::makeMessage(const QString &_command, const QVariant &_value)
{
    return makeMessage(JsonMessage(_command, _value));
}

}
