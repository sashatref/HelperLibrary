#ifndef ABSTRACT_APPENDER_H
#define ABSTRACT_APPENDER_H

#include <QString>

#include "../export.h"

namespace LoggerQt
{

class HELPERLIBRARY_EXPORT AbstractAppender
{
public:
    AbstractAppender();

    virtual void startupChecks();

    virtual ~AbstractAppender();

    virtual void onMessage(QtMsgType _msgType, const QMessageLogContext &_context, const QString &_msg) = 0;

    QString getFormatted(QtMsgType _msgType, const QMessageLogContext &_context, const QString &_msg);

    static QString m_appName;
};

}

#endif //ABSTRACT_APPENDER_H
