#include "stylefilewatcher.h"
#include "../functions.h"

#include <QFileSystemWatcher>
#include <QApplication>

namespace HelperLibraryNS
{

StyleFileWatcher::StyleFileWatcher(QObject *_parent):
    QObject(_parent)
{

}

void StyleFileWatcher::setStyleFilePath(const QString &_path)
{
    m_styleFilePath = _path;

    if(m_watcher)
    {
        delete m_watcher;
        m_watcher = nullptr;
    }

    if(!m_styleFilePath.isEmpty())
    {
        m_watcher = new QFileSystemWatcher(this);
        m_watcher->addPath(m_styleFilePath);

        connect(m_watcher, &QFileSystemWatcher::fileChanged, this, &StyleFileWatcher::styleFileChanged);
        styleFileChanged(m_styleFilePath);
    }
}

void StyleFileWatcher::styleFileChanged(const QString &_path)
{
    qApp->setStyleSheet(Text::readFromFile(_path));
}

}
