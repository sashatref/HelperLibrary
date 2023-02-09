#include "project_pch.h"
#include "fileappender.h"
#include "logger.h"
#include "loggersettings.h"

namespace LoggerQt
{

QMutex FileAppender::m_mutex;

static const QString logFolder = makePathAbsolute("logs");

FileAppender::FileAppender():
    m_file      (nullptr),
    m_stream    (nullptr)
{
    s = sgSettings::instance();

    QDir logDir(logFolder);
    if(!logDir.exists())
    {
        QDir().mkdir(logFolder);
    }

    createNewFile();
}



FileAppender::~FileAppender()
{
    writeEndOfFile();
    m_stream->flush();
    m_file->close();
    delete m_file;
    delete m_stream;
}

void FileAppender::startupChecks()
{
    QDir logDir(logFolder);

    checkDeleteAfterDays(logDir);
    checkDeleteAfterLogsSize(logDir);
}

void FileAppender::onMessage(QtMsgType _msgType,
                             const QMessageLogContext &_context,
                             const QString &_msg)
{
    if(!m_isOpened) return;

    QString text = QString("%1 | %2 | %3 | %4\r\n")
            .arg(QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm:ss"))
            .arg(_context.category)
            .arg(Logger::msgTypeName(_msgType))
            .arg(_msg);

    if(s->asHtml)
    {
        text = text.toHtmlEscaped();
        text = QString("<div class='%1'>%2</div>\r\n")
                .arg(Logger::msgTypeName(_msgType))
                .arg(text);
    }

    {
        QMutexLocker locker(&m_mutex);
        *m_stream << text;
        m_stream->flush();
    }

    checkFileSize();
}

void FileAppender::createNewFile()
{
    QMutexLocker locker(&m_mutex);

    if(m_file)
    {
        m_stream->flush();
        m_file->close();
        delete m_file;
        delete m_stream;
    }

    m_file = new QFile(QString("%3/%1_%2.%4")
                       .arg(m_appName)
                       .arg(QDateTime::currentDateTime().toString("yyyy.MM.dd_hh.mm.ss"))
                       .arg(logFolder)
                       .arg(s->asHtml ? "html" : "txt"));

    m_isOpened = m_file->open(QIODevice::WriteOnly);
    m_stream = new QTextStream(m_file);
    m_stream->setCodec("UTF-8");

    if(s->asHtml)
    {
        *m_stream << Text::readFromFile(":/htmltemplate.html").arg(qApp->applicationName());
    }
}

void FileAppender::checkFileSize()
{
    if(s->maxLogFileSize == 0) return;

    if(m_file->size() > s->maxLogFileSize)
    {
        writeEndOfFile();
        createNewFile();
    }
}

void FileAppender::writeEndOfFile()
{
    if(s->asHtml)
    {
        *m_stream << "</body></html>";
    }
}

void FileAppender::checkDeleteAfterDays(const QDir &_dir)
{
    if(!s->deleteAfterDays) return;

    QStringList filters;
    filters << QString("%1_????.??.??_??.??.??.%2").arg(m_appName).arg(s->asHtml ? "html" : "txt");

    QFileInfoList infoList = _dir.entryInfoList(filters, QDir::Files | QDir::NoDotAndDotDot);

    foreach (const QFileInfo &_item, infoList)
    {
        QDateTime lastModif = _item.lastModified().addDays(s->deleteDays);

        if(lastModif < QDateTime::currentDateTime())
        {
            QFile(_item.absoluteFilePath()).remove();
            qCInfo(loggerCat) << QString("Log file <%1> removed").arg(_item.absoluteFilePath());
        }
    }
}

void FileAppender::checkDeleteAfterLogsSize(const QDir &_dir)
{
    if(!s->deleteAfterLogsSize) return;

    QStringList filters;
    filters << QString("%1_????.??.??_??.??.??.%2").arg(m_appName).arg(s->asHtml ? "html" : "txt");

    QFileInfoList infoList = _dir.entryInfoList(filters, QDir::Files | QDir::NoDotAndDotDot);

    std::sort(infoList.begin(), infoList.end(), [](const QFileInfo &_item1, const QFileInfo &_item2)
    {
        return _item1.lastModified() < _item2.lastModified();
    });

    while(getFilesSize(infoList) > s->deleteLogSize)
    {
        const QString path = infoList.first().absoluteFilePath();
        if(QFile(path).remove())
        {
           qCInfo(loggerCat) << QString("Log file <%1> removed").arg(path);
        }

        infoList.removeFirst();
    }
}

qint64 FileAppender::getFilesSize(const QFileInfoList &_list)
{
    qint64 totalSize = 0;

    foreach (const QFileInfo &_item, _list)
    {
        totalSize += _item.size();
    }

    return totalSize;
}

}




