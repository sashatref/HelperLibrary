#pragma once

#include "../export.h"

#include <QVariant>
#include <QString>

namespace JsonProtocolNS
{

class HELPERLIBRARY_EXPORT JsonMessage
{
public:
    JsonMessage(const QString &_command = QString(), const QVariant &_value = QVariant());

    QString command;
    QVariant value;
};

using JsonMessageList = QList<JsonMessage>;

}
