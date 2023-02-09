#include "resourcecompilier.h"
#include "rcc.h"
#include "../Exceptions/userexception.h"
#include "../functions.h"

#include <QResource>

ResourceCompilier::ResourceCompilier(QObject *_parent):
    QObject(_parent)
{

}

void ResourceCompilier::setResourcePath(const QString &_path)
{
    m_resourcePath = _path;
}

QStringList ResourceCompilier::completeCompile()
{
    QStringList rawRes = searchRawResources(m_resourcePath);
    if(rawRes.size() == 0)
    {
        throwException(tr("Ресурсы [*.qrc] не найдены в каталоге [%1]").arg(m_resourcePath));
    }

    QString outFile = m_resourcePath + QDir::separator() + "resources.rcc";
    compileRawResources(rawRes, outFile);
    registerCompiliedResources({outFile});
    return rawRes;
}

bool ResourceCompilier::registerCompiliedResource()
{
    QString outFile = m_resourcePath + QDir::separator() + "resources.rcc";
    if(!QFile::exists(outFile))
    {
        return false;
    }

    registerCompiliedResources({outFile});
    reregisterResources(m_resourcePath);
    return true;
}

void ResourceCompilier::reregisterResources(const QString &_path)
{
    QString filePath = _path + QDir::separator() + "resources.rcc";

    if(!QResource::unregisterResource(filePath))
    {
        throwException(tr("Resource [%1] unregister error").arg(filePath));
    }

    if(!QResource::registerResource(filePath))
    {
        throwException(tr("Resource [%1] register error").arg(filePath));
    }
}

QStringList ResourceCompilier::searchRawResources(const QString &_path)
{
    if(_path.isEmpty())
    {
        return {};
    }

    QStringList out;

    QDirIterator it(_path, QStringList("*.qrc"), QDir::Files, QDirIterator::Subdirectories);
    while(it.hasNext())
    {
        out << QFileInfo(it.next()).absoluteFilePath();
    }

    return out;
}

void ResourceCompilier::compileRawResources(const QStringList &_fileList, const QString &_outFile)
{
    quint8 formatVersion = 2;
    RCCResourceLibrary library(formatVersion);
    library.setFormat(RCCResourceLibrary::Binary);
    library.setInputFiles(_fileList);

    {
        QByteArray error;
        QBuffer errorBuf(&error);
        errorBuf.open(QIODevice::ReadWrite);
        if(library.readFiles(false, errorBuf) == false)
        {
            throwException(tr("Error while read files [%1]").arg(QString(error)));
        }
    }

    QFile outFile(_outFile);
    if(!outFile.open(QIODevice::WriteOnly))
    {
        throwException(tr("Ошибка открытия выходного файла | [%1] - [%2]").arg(_outFile).arg(outFile.errorString()));
    }

    {
        QFile temp;
        QByteArray error;
        QBuffer errroBuf(&error);
        errroBuf.open(QIODevice::ReadWrite);

        bool success = library.output(outFile, temp, errroBuf);
        if(success == false)
        {
            outFile.remove();
            throwException(tr("Ошибка вов время компиляции ресурсов"));
        }
    }
}

void ResourceCompilier::registerCompiliedResources(const QStringList &_files)
{
    for(auto &it : _files)
    {
        if(!QResource::registerResource(it))
        {
            qWarning() << Text::format("ResourceCompilier::registerCompiliedResources | Can't register resource [%1]", it);
        }
    }
}

void ResourceCompilier::unregisterCompiliedResources(const QStringList &_files)
{
    for(auto &it : _files)
    {
        QResource::unregisterResource(it);
    }
}
