#pragma once

#include <QObject>
#include "../export.h"

class QFileSystemWatcher;

namespace HelperLibraryNS
{

class HELPERLIBRARY_EXPORT StyleFileWatcher : public QObject
{
    Q_OBJECT
public:
    StyleFileWatcher(QObject *_parent = nullptr);

    void setStyleFilePath(const QString &_path);

private slots:
    void styleFileChanged(const QString &_path);

private:
    QString m_styleFilePath;
    QFileSystemWatcher *m_watcher = nullptr;
};

}

