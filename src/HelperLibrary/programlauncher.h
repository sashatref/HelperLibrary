#pragma once

#include <QObject>
#include <QProcess>
#include <QDebug>
#include <QFileSystemWatcher>
#include "export.h"

namespace HelperLibraryNS
{

class HELPERLIBRARY_EXPORT ProgramLauncher : public QObject
{
    Q_OBJECT
public:
    ProgramLauncher(QObject *_parent = nullptr);
    void start(const QString &_program, const QString &_projectPath);

signals:
    void projectFileChanged(const QString &_path);

private slots:
    void finishedPriv(int _exitCode);
    void fileChangedPriv(const QString &_path);

private:
    bool m_deleteOnProgramClose = true;
    bool m_isProjectChanged = false;
    QProcess *m_process = nullptr;
    QFileSystemWatcher *m_watcher;
    QString m_projectPath;
};

}
