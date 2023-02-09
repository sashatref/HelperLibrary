#include "FileBasedProject.h"
#include "filebasedprojectp.h"

#ifdef _WIN32
    #include "../Win/winapiqt.h"
#endif

#include <QFileSystemWatcher>

namespace HelperLibraryNS
{

FileBasedProject::FileBasedProject(QWidget *_parent):
    QObject(_parent),
    p(new FileBasedProjectP(this))
{
    p->m_parent = _parent;
    p->m_parent->installEventFilter(p);

    p->createToolBar();
    p->createCurrentProjEdit();
    p->createLastProjectsMenu();

    p->updateLanguage();
    p->updateStyle();

    p->m_saveAction->setEnabled(false);
    p->m_saveAsAction->setEnabled(false);
    p->m_openInBrowserAction->setEnabled(false);

    setFileExt(ffXml);

    connect(this, &FileBasedProject::projectDisplayPathChanged, p, &FileBasedProjectP::onDisplayPathChanged);
}

FileBasedProject::~FileBasedProject()
{

}

void FileBasedProject::setAutoLoadLastProject(bool _autoLoad)
{
    p->m_autoloadLastProject = _autoLoad;
}

void FileBasedProject::setCheckFileChanges(bool _check)
{
    p->m_checkFileChanged = _check;
}

void FileBasedProject::setLastProjectsMaxCount(int _count)
{
    p->m_lastProjectMaxCount = _count;
}

void FileBasedProject::setFileExt(const QString &_filter)
{
    p->m_fileFilter = _filter;
}

void FileBasedProject::setFileExt(FileBasedProject::FileFormat _fileFormat)
{
    switch(_fileFormat)
    {
    case ffBin:
        setFileExt("Bin-file(*.bin)");
        break;
    case ffJson:
        setFileExt("Json-file(*.json)");
        break;
    case ffXml:
        setFileExt("Xml-file(*.xml)");
        break;
    }
}

bool FileBasedProject::hasChangesSinceSaved() const
{
    return p->m_hasChangedSinceSave;
}

void FileBasedProject::setChangedFlag(bool _isChanged)
{
    p->m_hasChangedSinceSave = _isChanged;
    p->m_saveAction->setEnabled(_isChanged);

    if(_isChanged)
    {
        p->m_currentProjectEdit->setStyleSheet("background-color: yellow");
        p->m_currentProjectEdit->setToolTip(tr("Есть несохраненные изменения в проекте"));
    }
    else
    {
        p->m_currentProjectEdit->setStyleSheet("");
        p->m_currentProjectEdit->setToolTip("");
    }

    emit projectDisplayPathChanged(getDisplayCurrentProjectPath());
}


void FileBasedProject::save()
{
    if(p->m_currentProjectPath.isEmpty())
    {
        return;
    }

    if(p->m_editMode == false)
    {
        int res = QMessageBox::warning(p->m_parent,
                             tr("Ошибка"),
                             tr("Данный проект защищен от записи. Хотите сохранить в другой файл?"),
                             QMessageBox::Yes, QMessageBox::No);
        if(res == QMessageBox::Yes)
        {
            saveAs();
        }

        return;
    }

    saveProjectPriv(p->m_currentProjectPath);
}

void FileBasedProject::saveAs()
{
    QString path = QFileDialog::getSaveFileName(p->m_parent,
                                                tr("Выберите файл для сохранения"),
                                                p->m_lastSavePath,
                                                p->m_fileFilter);
    if(path.isEmpty())
    {
        return;
    }

    p->m_lastSavePath = path;
    p->m_currentProjectPath = path;
    saveProjectPriv(path);
}

void FileBasedProject::openInExplorer()
{
#ifdef _WIN32
    HelperLibraryNS::WinApiQt::openFileInExplorer(p->m_currentProjectPath);
#endif
}

void FileBasedProject::reloadFromDisk()
{
    if(checkProjectForSave() == rCancel) return;

    loadProjectPriv(p->m_currentProjectPath);
}

void FileBasedProject::setEditMode(bool _editMode)
{
    p->m_editMode = _editMode;
}

QToolBar *FileBasedProject::getToolBar()
{
    return p->m_toolbar;
}

QLineEdit *FileBasedProject::getCurrentProjectEdit()
{
    return p->m_currentProjectEdit;
}

QMenu *FileBasedProject::createLastProjectsMenu()
{
    return p->createLastProjectsMenu();
}

QString FileBasedProject::getCurrentProjectPath() const
{
    return p->m_currentProjectPath;
}

QString FileBasedProject::getDisplayCurrentProjectPath() const
{
    return QString("%1%2")
            .arg(hasChangesSinceSaved() ? "*" : "")
            .arg(getCurrentProjectPath());
}



bool FileBasedProject::getEditMode() const
{
    return p->m_editMode;
}



void FileBasedProject::createNew(bool _withPromt)
{
    if(_withPromt)
    {
        if(checkProjectForSave() == rCancel)
        {
            return;
        }
    }

    const QString fPath = QFileDialog::getSaveFileName(p->m_parent, tr("Сохранить новый файл"),
                                                       p->m_lastSavePath,
                                                       p->m_fileFilter);
    if(fPath.isEmpty())
    {
        return;
    }

    createEmptyProject(fPath);

    p->setCurrentProjectPath(fPath);
    p->m_editMode = true;
    save();

    loadProjectPriv(fPath);
}

void FileBasedProject::load()
{
    if(checkProjectForSave() == rCancel) return;

    const QString path = QFileDialog::getOpenFileName(p->m_parent,
                                                tr("Выберите файл для загрузки"),
                                                p->m_currentProjectPath,
                                                p->m_fileFilter);
    if(path.isEmpty())
    {
        return;
    }

    loadProjectPriv(path);
}

void FileBasedProject::loadProjectPriv(QString _fileName)
{
    _fileName = QDir::toNativeSeparators(_fileName);

    QFile f(_fileName);
    if(!f.open(QIODevice::ReadOnly))
    {
        emit message(tr("Ошибка чтения файла [%1] - [%2]")
                     .arg(f.fileName()).arg(f.errorString()), QtCriticalMsg);
        return;
    }

    if(!p->m_currentProjectPath.isEmpty())
    {
        emit saveStateForProject(p->m_currentProjectPath);
    }

    try
    {
        emit projectPreload(_fileName);

        loadProject(f.readAll(), _fileName);
        p->setCurrentProjectPath(_fileName);

        emit message(tr("Проект <%1> успешно загружен").arg(f.fileName()), QtInfoMsg);
        emit projectPathChanged(_fileName);
        emit projectDisplayPathChanged(getDisplayCurrentProjectPath());

        p->m_hasChangedSinceSave = false;
        p->m_saveAction->setEnabled(false);
        p->m_saveAsAction->setEnabled(true);
        p->m_openInBrowserAction->setEnabled(true);

        setChangedFlag(false);

        p->updateRecentList(_fileName);

        emit projectLoaded();
        emit loadStateForProject(_fileName);

        p->createFSWatcher();

    } catch(std::exception &e)
    {
        emit message(tr("Ошибка загруки проекта из файла [%1] - [%2]")
                   .arg(f.fileName())
                   .arg(e.what()), QtCriticalMsg);
    }
}

void FileBasedProject::saveProjectPriv(QString _fileName)
{
    _fileName = QDir::toNativeSeparators(_fileName);

    QFile f(_fileName);
    if(!f.open(QIODevice::WriteOnly))
    {
        emit message(tr("Ошибка записи в файл [%1] - [%2]")
                   .arg(f.fileName()).arg(f.errorString()), QtCriticalMsg);
        return;
    }

    delete p->m_fsWatcher;
    p->m_fsWatcher = nullptr;

    try
    {
        QByteArray projectData = saveProject(_fileName);
        setChangedFlag(false);
        p->setCurrentProjectPath(_fileName);

        f.write(projectData);
        emit message(tr("Проект <%1> успешно сохранен").arg(f.fileName()), QtInfoMsg);
    } catch(std::exception &e)
    {
        emit message(tr("Ошибка сохранения проекта в файл <%1> - <%2>")
                   .arg(f.fileName())
                   .arg(e.what()), QtCriticalMsg);
    }

    //запускаем асинхронно, потому что запись файла может произойти уже после создания FSWatcher'а
    //и будет ложное срабатывание сигнала наличия изменений в файле
    QTimer::singleShot(1000, this, [=]
    {
        p->createFSWatcher();
    });
}

void FileBasedProject::emitProjectPathChanged()
{
    emit projectPathChanged(p->m_currentProjectPath);
}

FileBasedProject::DialogResult FileBasedProject::checkProjectForSave(bool _withCancel)
{
    if(p->m_hasChangedSinceSave)
    {
        int res = QMessageBox::warning(p->m_parent, tr("Проект"),
                                       tr("В проекте [%1] остались несохраненные данные. Что делать?")
                                       .arg(p->m_currentProjectPath),
                                       tr("Сохранить и закрыть"),
                                       tr("Закрыть не сохраняя"),
                                       _withCancel ? tr("Отмена") : "");

        switch(res)
        {
        case rSaveAndClose:
            save();
            break;
        case rCloseWithoutSave:
            break;
        case rCancel:
            break;
        }

        return static_cast<DialogResult>(res);
    }

    return rNotChanded;
}

void FileBasedProject::promtToReloadProject()
{
    if(p->m_changesFileFlag)
    {
        return;
    }

    p->m_changesFileFlag = true;
    if(QMessageBox::question(p->m_parent,
                                tr("Обновление файл"),
                                tr("[%1]\n\n"
                                   "Файл был изменен другой программой\n"
                                    "Вы хотите обновить его?")
                             .arg(p->m_currentProjectPath))
            == QMessageBox::Yes)
    {
        loadProjectPriv(p->m_currentProjectPath);
    }

    p->m_changesFileFlag = false;
}

void FileBasedProject::loadFile(const QString &_filePath)
{
    if(checkProjectForSave() == rCancel) return;

    loadProjectPriv(_filePath);
}

void FileBasedProject::emitSaveProjectState()
{
    emit saveStateForProject(p->m_currentProjectPath);
}


QString FileBasedProject::getWidgetUniqueName() const
{
    return objectName();
}

void FileBasedProject::loadState(const LayoutSaver &_saver)
{
    QString newPath;

    _saver.load(newPath, "currentProjectPath");
    _saver.load(p->m_lastSavePath, "lastSavePath");
    _saver.load(p->m_lastProjectsList, "lastProjectList");

    p->recreateActions();
    if(!newPath.isEmpty() && p->m_autoloadLastProject)
    {
        loadProjectPriv(newPath);
    }
}

void FileBasedProject::saveState(LayoutSaver &_saver) const
{
    _saver.save(p->m_currentProjectPath, "currentProjectPath");
    _saver.save(p->m_lastSavePath, "lastSavePath");
    _saver.save(p->m_lastProjectsList, "lastProjectList");
}

}
