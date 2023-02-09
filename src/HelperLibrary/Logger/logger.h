#ifndef LOGGER_H
#define LOGGER_H

#include "../export.h"


/*!
 * ConfigExample
 *
 * TSStudent_vc14.ini
 *
 * @example
 *  [logger]
    textPattern=                //паттерн вывода сообщений

    [fileLogger]

    deleteAfterDays=true            //удалять ли файлы старше <dayCount> дней
    dayCount=15

    deleteAfterLogsSize=true        //удалять ли файлы, если логи стали занимать > <logsSize> места
    logsSize=500M

    maxLogFileSize=50M              //рабивать файлы, если становятся больше <maxLogFileSize>
 */

namespace LoggerQt
{

struct LoggerPrivate;
class AbstractAppender;

class HELPERLIBRARY_EXPORT Logger
{
public:

    /*!
     * \brief Logger
     * \param _appName имя, которое успользуется для загрузки файла конфига <_appName.ini> и формирования
     * названия файлов лога _appName_yyyy.MM.dd_hh.mm.ss.txt, если оставить пустым, то будет использоваться
     * qAppName();
     */
    Logger(const char* _appName = 0);
    virtual ~Logger();

    static QString msgTypeName(QtMsgType _type);

    static void setPattern(const QString &_patter);

    static void msgHandler(QtMsgType _msgType, const QMessageLogContext &_context, const QString &_msg);

    static bool loadSettings();

    static void addAppender(AbstractAppender *_appender);

private:
    static LoggerPrivate *loggerP;

    static bool m_inDelete;
};

}

#endif //LOGGER_H
