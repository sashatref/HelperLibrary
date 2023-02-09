#ifndef LOGGERSETTINGS_H
#define LOGGERSETTINGS_H

#include "../project_pch.h"
#include "../singleton.hpp"
#include "../functions.h"

struct LoggerSettings
{
    QString textPattern;

    bool deleteAfterDays;
    qint64 deleteDays;

    bool deleteAfterLogsSize;
    qint64 deleteLogSize;

    qint64 maxLogFileSize;

    bool asHtml;

    LoggerSettings();

    void loadSettings(const QString &_path);

    friend QDebug operator <<(QDebug _in, const LoggerSettings &_s)
    {
        QString params("TextPatter <%1>, "
                       "DeleteAfterDays <%2>, "
                       "DeleteDays <%3>, "
                       "DeleteAfterLogSize <%4>, "
                       "DeleteLogSize <%5>, "
                       "MaxLogFileSize <%6>, "
                       "AsHtml <%7>");
        params = params
                .arg(_s.textPattern)
                .arg(_s.deleteAfterDays ? "true" : "false")
                .arg(_s.deleteDays)
                .arg(_s.deleteAfterLogsSize ? "true" : "false")
                .arg(Text::fileSizeToString(_s.deleteLogSize))
                .arg(Text::fileSizeToString(_s.maxLogFileSize))
                .arg(_s.asHtml ? "true" : "false");

        _in << QString("LoggerSettings(%1)").arg(params);

        return _in;
    }
};

typedef Singleton<LoggerSettings> sgSettings;

#endif // LOGGERSETTINGS_H
