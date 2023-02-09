#include "project_pch.h"
#include "loggerhelper.h"


namespace LoggerQt
{

void LoggerHelper::logMessage(const QString &_text, QtMsgType _type)
{
    switch(_type)
    {
    case QtDebugMsg:
        qDebug() << _text;
        break;
    case QtInfoMsg:
        qInfo() << _text;
        break;
    case QtWarningMsg:
        qWarning() << _text;
        break;
    case QtCriticalMsg:
        qCritical() << _text;
        break;
    case QtFatalMsg:
        qCritical() << _text;
    }
}

}
