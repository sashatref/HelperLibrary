#ifndef FILEAPPENDER_H
#define FILEAPPENDER_H

#include "abstractappender.h"

#include <QQueue>
#include <QMutex>
#include <QDir>

class QFile;
class QTextStream;
struct LoggerSettings;

namespace LoggerQt
{

class HELPERLIBRARY_EXPORT FileAppender : public AbstractAppender
{
public:
    FileAppender();
    ~FileAppender();

    virtual void onMessage(QtMsgType _msgType, const QMessageLogContext &_context, const QString &_msg) override;
    virtual void startupChecks() override;

private:
    void createNewFile();
    void checkFileSize();

    void writeEndOfFile();

    void checkDeleteAfterDays(const QDir &_dir);
    void checkDeleteAfterLogsSize(const QDir &_dir);

    qint64 getFilesSize(const QFileInfoList&_list);

    QFile *m_file;
    QTextStream *m_stream;
    bool m_isOpened;
    QQueue<QString> m_queue;
    static QMutex m_mutex;

    LoggerSettings *s;
};

}

#endif //FILEAPPENDER_H
