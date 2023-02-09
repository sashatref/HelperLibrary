#include "project_pch.h"
#include "filerotation.h"



FileRotation::FileRotation()
{

}

FileRotation::~FileRotation()
{

}

void FileRotation::closeFile()
{
    writeEndOfFilePriv();
}

QFile *FileRotation::getFileDevice()
{
    return m_file;
}

void FileRotation::createNewFile()
{
    writeEndOfFilePriv();

    QDir logDir(config.directory);
    if(!logDir.exists())
    {
        QDir().mkdir(config.directory);
    }

    m_file = new QFile(QString("%3/%1_%2.%4")
                       .arg(config.fileBaseName)
                       .arg(QDateTime::currentDateTime().toString("yyyy.MM.dd_hh.mm.ss"))
                       .arg(config.directory)
                       .arg(config.fileExt));

    m_file->open(QIODevice::WriteOnly);
    afterCreateNewFile(m_file);
}

void FileRotation::checkFileSize()
{
    if(config.maxLogFileSize == 0) return;

    if(m_file->size() > config.maxLogFileSize)
    {
        writeEndOfFile();
        createNewFile();
    }
}

void FileRotation::checkDeleteAfterDays()
{
    if(!config.deleteAfterDays) return;

    QStringList filters;
    filters << QString("%1_????.??.??_??.??.??.%2")
               .arg(config.fileBaseName)
               .arg(config.fileExt);

    QFileInfoList infoList = QDir(config.directory)
            .entryInfoList(filters, QDir::Files | QDir::NoDotAndDotDot);

    foreach (const QFileInfo &_item, infoList)
    {
        QDateTime lastModif = _item.lastModified().addDays(config.deleteDays);

        if(lastModif < QDateTime::currentDateTime())
        {
            QFile(_item.absoluteFilePath()).remove();
            qCInfo(loggerCat) << QString("FileRotation | File <%1> removed").arg(_item.absoluteFilePath());
        }
    }
}

void FileRotation::checkDeleteAfterLogsSize()
{
    if(!config.deleteAfterLogsSize) return;

    QStringList filters;
    filters << QString("%1_????.??.??_??.??.??.%2")
               .arg(config.fileBaseName)
               .arg(config.fileExt);

    QFileInfoList infoList = QDir(config.directory)
            .entryInfoList(filters, QDir::Files | QDir::NoDotAndDotDot);

    std::sort(infoList.begin(), infoList.end(), [](const QFileInfo &_item1, const QFileInfo &_item2)
    {
        return _item1.lastModified() < _item2.lastModified();
    });

    while(getFilesSize(infoList) > config.deleteLogSize)
    {
        const QString path = infoList.first().absoluteFilePath();
        if(QFile(path).remove())
        {
            qCInfo(loggerCat) << QString("FileRotation | File <%1> removed").arg(path);
        }

        infoList.removeFirst();
    }
}

QString FileRotation::getLastFile() const
{
    QStringList filters;
    filters << QString("%1_????.??.??_??.??.??.%2")
               .arg(config.fileBaseName)
               .arg(config.fileExt);

    QFileInfoList infoList = QDir(config.directory)
            .entryInfoList(filters, QDir::Files | QDir::NoDotAndDotDot);

    std::sort(infoList.begin(), infoList.end(), [](const QFileInfo &_item1, const QFileInfo &_item2)
    {
        return _item1.lastModified() > _item2.lastModified();
    });

    if(infoList.size())
    {
        return infoList.first().absoluteFilePath();
    }

    return QString();
}

qint64 FileRotation::getFilesSize(const QFileInfoList &_list)
{
    qint64 totalSize = 0;

    foreach (const QFileInfo &_item, _list)
    {
        totalSize += _item.size();
    }

    return totalSize;
}

void FileRotation::afterCreateNewFile(QFile *_f)
{
    Q_UNUSED(_f);
}

void FileRotation::writeEndOfFile()
{

}

void FileRotation::writeEndOfFilePriv()
{
    if(m_file)
    {
        writeEndOfFile();
        m_file->close();
        delete m_file;
        m_file = nullptr;
        afterCloseFile();
    }
}

void FileRotation::afterCloseFile()
{

}
