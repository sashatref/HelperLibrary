#ifndef FILEROTATION_H
#define FILEROTATION_H

#include "../../functions.h"

struct RotationConfig
{
    bool deleteAfterDays = true;
    qint64 deleteDays = 15;

    bool deleteAfterLogsSize = true;
    qint64 deleteLogSize = 500_mb;

    qint64 maxLogFileSize = 0;

    QString fileBaseName;
    QString directory;
    QString fileExt;
};

class FileRotation
{
public:
    FileRotation();
    ~FileRotation();

    void closeFile();

    QFile *getFileDevice();

    void createNewFile();

    void checkFileSize();
    void checkDeleteAfterDays();
    void checkDeleteAfterLogsSize();

    QString getLastFile() const;

    static qint64 getFilesSize(const QFileInfoList &_list);

    virtual void afterCreateNewFile(QFile *_f);
    virtual void afterCloseFile();
    virtual void writeEndOfFile();

    RotationConfig config;
private:
    void writeEndOfFilePriv();

    QFile *m_file = nullptr;
};

#endif // FILEROTATION_H
