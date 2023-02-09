#pragma once

#include <QObject>
#include "../export.h"

class HELPERLIBRARY_EXPORT ResourceCompilier : public QObject
{
public:
    ResourceCompilier(QObject *_parent = nullptr);

    void setResourcePath(const QString &_path);

    QStringList completeCompile();
    bool registerCompiliedResource();

signals:
    void resourceFilesChanged();

private:
    QString m_resourcePath;

    static void reregisterResources(const QString &_path);

    static QStringList searchRawResources(const QString &_path);
    static void compileRawResources(const QStringList &_fileList, const QString &_outFile);

    static void registerCompiliedResources(const QStringList &_files);

    static void unregisterCompiliedResources(const QStringList &_files);
};
