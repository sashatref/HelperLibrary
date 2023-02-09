#include "project_pch.h"
#include "abstractappender.h"

namespace LoggerQt
{

QString AbstractAppender::m_appName;

AbstractAppender::AbstractAppender()
{

}

void AbstractAppender::startupChecks()
{

}

AbstractAppender::~AbstractAppender()
{

}

QString AbstractAppender::getFormatted(QtMsgType _msgType, const QMessageLogContext &_context, const QString &_msg)
{
    return qFormatLogMessage(_msgType, _context, _msg);
}

}
