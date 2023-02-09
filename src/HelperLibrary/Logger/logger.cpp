#include "project_pch.h"
#include "logger.h"
#include "abstractappender.h"
#include "consoleappender.h"
#include "fileappender.h"
#include "loggersettings.h"

#include <locale>

namespace LoggerQt
{

struct LoggerPrivate
{
    QList<QSharedPointer<AbstractAppender>> m_appenderList;
};

LoggerPrivate *Logger::loggerP = nullptr;

bool Logger::m_inDelete = false;

Logger::Logger(const char *_appName)
{
    loggerP = new LoggerPrivate();
    AbstractAppender::m_appName = _appName ? _appName : qAppName();

    loadSettings();

    setlocale(LC_ALL, "");
    qInstallMessageHandler(msgHandler);

    QList<AbstractAppender *> appenders;
    appenders << new LoggerQt::ConsoleAppender();
    appenders << new LoggerQt::FileAppender();

    foreach (AbstractAppender* item, appenders)
    {
        addAppender(item);
    }

    foreach (AbstractAppender* item, appenders)
    {
        item->startupChecks();
    }

    qCInfo(loggerCat) << sgSettings::ins();
}

Logger::~Logger()
{
    m_inDelete = true;
    qInstallMessageHandler(nullptr);
    delete loggerP;
}


QString Logger::msgTypeName(QtMsgType _type)
{
    QString text;
    switch(_type)
    {
    case QtInfoMsg:
        text = "Info";
        break;
    case QtWarningMsg:
        text = "Warning";
        break;
    case QtCriticalMsg:
        text = "Critical";
        break;
    case QtDebugMsg:
        text = "Debug";
        break;
    case QtFatalMsg:
        text = "Fatal";
        break;
    }

    return text;
}

void Logger::setPattern(const QString &_patter)
{
    qSetMessagePattern(_patter);
}

void Logger::msgHandler(QtMsgType _msgType, const QMessageLogContext &_context, const QString &_msg)
{
    if(m_inDelete) return;

    for(int i = 0 ; i < loggerP->m_appenderList.size(); i++)
    {
        loggerP->m_appenderList[i]->onMessage(_msgType, _context, _msg);
    }
}

bool Logger::loadSettings()
{
    LoggerSettings *s = sgSettings::instance();

    QString configPath = AbstractAppender::m_appName + ".ini";
    s->loadSettings(configPath);

    if(s->textPattern.isEmpty())
    {  
        qSetMessagePattern(s->textPattern);
    } else
    {
        return false;
    }

    return true;
}

void Logger::addAppender(AbstractAppender *_appender)
{
    QSharedPointer<AbstractAppender> sharedPtr;
    sharedPtr.reset(_appender);
    loggerP->m_appenderList.append(sharedPtr);
}

}
