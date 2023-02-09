#include "programlauncher.h"

namespace HelperLibraryNS
{

ProgramLauncher::ProgramLauncher(QObject *_parent):
    QObject(_parent),
    m_process(new QProcess(this)),
    m_watcher(new QFileSystemWatcher(this))
{

}

void ProgramLauncher::start(const QString &_program, const QString &_projectPath)
{
    m_projectPath = _projectPath;
    m_process->setProgram(_program);
    m_process->setArguments(QStringList() << _projectPath);

    connect(m_process, QOverload<int>::of(&QProcess::finished), this, &ProgramLauncher::finishedPriv);
    connect(m_watcher, &QFileSystemWatcher::fileChanged, this, &ProgramLauncher::fileChangedPriv);

    m_watcher->addPath(_projectPath);
    m_process->start();
}

void ProgramLauncher::finishedPriv(int /*_exitCode*/)
{
    if(m_isProjectChanged)
    {
        emit projectFileChanged(m_projectPath);
    }

    if(m_deleteOnProgramClose)
    {
        deleteLater();
    }
}

void ProgramLauncher::fileChangedPriv(const QString &_path)
{
    if(m_projectPath == _path)
    {
        m_isProjectChanged = true;
    }
}

}
