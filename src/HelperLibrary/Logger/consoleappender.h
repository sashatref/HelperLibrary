#ifndef CONSOLE_APPENDER_H
#define CONSOLE_APPENDER_H

#include "../export.h"
#include "abstractappender.h"

#include <QMutex>

namespace LoggerQt
{

class HELPERLIBRARY_EXPORT ConsoleAppender : public AbstractAppender
{
    // AbstractAppender interface
public:
    virtual void onMessage(QtMsgType _msgType,
                           const QMessageLogContext &_context,
                           const QString &_msg) override;

private:
    static QMutex m_mutex;
};

}

#endif //CONSOLE_APPENDER_H
