#include "loggersettings.h"
#include "../functions.h"

#include <QSettings>

LoggerSettings::LoggerSettings():
    textPattern             (),
    deleteAfterDays         (true),
    deleteDays              (15),
    deleteAfterLogsSize     (true),
    deleteLogSize           (500_mb),
    maxLogFileSize          (0),
    asHtml                  (true)
{

}

void LoggerSettings::loadSettings(const QString &_path)
{
    QSettings settings(_path, QSettings::IniFormat);
    textPattern = settings.value("logger/textPattern").toString();

    deleteAfterDays = settings.value("fileLogger/deleteAfterDays", "true").toBool();

    int deleteDaysTemp = settings.value("fileLogger/dayCount", "15").toInt();
    if(deleteDaysTemp > 0)
    {
        deleteDays = deleteDaysTemp;
    }

    deleteAfterLogsSize = settings.value("fileLogger/deleteAfterLogsSize", "true").toBool();

    int deleteLogSizeTemp = Text::parseFileSize(settings.value("fileLogger/logsSize").toString());
    if(deleteLogSizeTemp > 0)
    {
        deleteLogSize = deleteLogSizeTemp;
    }

    int maxLogFileSizeTemp = Text::parseFileSize(settings.value("fileLogger/maxLogFileSize").toString());
    if(maxLogFileSizeTemp > 0)
    {
        maxLogFileSize = maxLogFileSizeTemp;
    }

    asHtml = deleteAfterLogsSize = settings.value("fileLogger/asHtml", "true").toBool();
}


