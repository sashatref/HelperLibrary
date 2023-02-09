#include "consoleappender.h"
#include "logger.h"

#include <string>
#include <iostream>

namespace LoggerQt
{

QMutex ConsoleAppender::m_mutex;

void ConsoleAppender::onMessage(QtMsgType _msgType,
                                const QMessageLogContext &_context,
                                const QString &_msg)
{
#ifdef Q_OS_WIN
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_SCREEN_BUFFER_INFO Info;
        GetConsoleScreenBufferInfo(hConsole, &Info);

        static QMap<QtMsgType, int> colors = {
            { QtDebugMsg, 2 },
            { QtWarningMsg, 224},
            { QtInfoMsg, 15 },
            { QtCriticalMsg, 79 },
            { QtFatalMsg , 79 }
        };

        SetConsoleTextAttribute(hConsole, colors[_msgType]);
#endif

        QString text = QString("%1 | %2 | %3 | %4")
                .arg(QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm:ss"))
                .arg(_context.category)
                .arg(Logger::msgTypeName(_msgType))
                .arg(_msg);
        QMutexLocker mLocker(&m_mutex);
        std::wcout << text.toStdWString() << std::endl;

#ifdef Q_OS_WIN
      SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Info.wAttributes);
#endif
}

}
