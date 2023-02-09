#include "filebasedprojectp.h"

#include "../Styles/iconsenum.h"
#include "../functions.h"
#include "Widgets/widgethelper.h"

#include <QFileSystemWatcher>
#include <QToolBar>

namespace HelperLibraryNS
{

FileBasedProjectP::FileBasedProjectP(FileBasedProject *_q):
    QObject(_q),
    q(_q)
{

}

void FileBasedProjectP::setCurrentProjectPath(const QString &_path)
{
    m_currentProjectPath = _path;

    //m_saveAction->setEnabled(true);
    m_openInBrowserAction->setEnabled(true);
}

void FileBasedProjectP::onDisplayPathChanged(const QString &_path)
{
    const QString cPathText = tr("Текущий проект [%1] (%2)")
            .arg(_path)
            .arg(m_editMode ? tr("Чтение/запись") : tr("Только чтение"));

    m_currentProjectEdit->setText(cPathText);
}


void FileBasedProjectP::createToolBar()
{
    if(m_toolbar)
    {
        return;
    }

    m_toolbar = new QToolBar(m_parent);
    m_toolbar->setWindowTitle(tr("Панель управления проектом"));
    m_toolbar->setToolTip(tr("Панель управления проектом"));
    m_toolbar->setStatusTip(tr("Панель управления проектом"));
    m_toolbar->setObjectName("FileBasedProject/Toolbar1");

    m_createNewAction = m_toolbar->addAction("", q, &FileBasedProject::createNew);
    m_createNewAction->setShortcut(tr("CTRL+N"));

    m_loadAction = m_toolbar->addAction("", q, &FileBasedProject::load);
    m_loadAction->setShortcut(tr("CTRL+O"));

    m_saveAction = m_toolbar->addAction("", q, &FileBasedProject::save);
    m_saveAction->setShortcut(tr("CTRL+S"));

    m_saveAsAction = m_toolbar->addAction("", q, &FileBasedProject::saveAs);

    m_openInBrowserAction = m_toolbar->addAction("", q, &FileBasedProject::openInExplorer);

    m_reloadProject = m_toolbar->addAction("", q, &FileBasedProject::reloadFromDisk);

    m_saveAction->setEnabled(false);
}

void FileBasedProjectP::createCurrentProjEdit()
{
    if(m_currentProjectEdit)
    {
        return;
    }

    m_currentProjectEdit = new QLineEdit(m_parent);
    m_currentProjectEdit->setReadOnly(true);

    WidgetHelper::setWidgetFontPx(m_currentProjectEdit, 12);
}

void FileBasedProjectP::updateLanguage()
{
    m_toolbar->setWindowTitle(tr("Панель управления проектом"));
    m_toolbar->setToolTip(tr("Панель управления проектом"));
    m_toolbar->setStatusTip(tr("Панель управления проектом"));

    m_createNewAction->setText(tr("Создать новый проект"));
    m_createNewAction->setStatusTip(tr("Создать новый проект"));

    m_loadAction->setText(tr("Загрузить проект"));
    m_loadAction->setStatusTip(tr("Загрузить проект"));

    m_saveAction->setText(tr("Сохранить проект"));
    m_saveAction->setStatusTip(tr("Сохранить проект"));

    m_saveAsAction->setText(tr("Сохранить как..."));
    m_saveAsAction->setStatusTip(tr("Сохранить как..."));

    m_openInBrowserAction->setText(tr("Открыть каталог с файлом проекта"));
    m_openInBrowserAction->setStatusTip(tr("Открыть каталог с файлом проекта"));

    m_toolbar->setWindowTitle(tr("Панель управления проектом"));

    m_lastProjectMenu->setTitle(tr("Недавние файлы"));

    if(m_emptyAction)
    {
        m_emptyAction->setText(tr("Пусто"));
    }

    m_reloadProject->setText(tr("Перегрузить проект с диска"));
    m_reloadProject->setStatusTip(tr("Перегрузить проект с диска"));
}

void FileBasedProjectP::updateStyle()
{
    m_createNewAction->setIcon(IconsEnum::getIcon(IconsEnum::SP_AddDocument2));
    m_loadAction->setIcon(IconsEnum::getIcon(QStyle::SP_DialogOpenButton));
    m_saveAction->setIcon(IconsEnum::getIcon(IconsEnum::SP_Save1));
    m_saveAsAction->setIcon(IconsEnum::getIcon(IconsEnum::SP_SaveAs1));
    m_openInBrowserAction->setIcon(IconsEnum::getIcon(IconsEnum::SP_OpenInBrowser2));
    m_reloadProject->setIcon(IconsEnum::getIcon(IconsEnum::SP_Reload2));
}

QMenu *FileBasedProjectP::createLastProjectsMenu()
{
    if(m_lastProjectMenu)
    {
        return m_lastProjectMenu;
    }

    m_lastProjectMenu = new QMenu(m_parent);

    recreateActions();

    return m_lastProjectMenu;
}

void FileBasedProjectP::recreateActions()
{
    m_lastProjectMenu->clear();
    m_emptyAction = nullptr;

    for(int i = 0 ; i < m_lastProjectsList.size(); i++)
    {
        QAction *act = new QAction(m_lastProjectMenu);
        act->setText(QString("%1 %2")
                     .arg(i + 1)
                     .arg(Text::getShortFilePath(m_lastProjectsList[i], 65)));
        act->setData(m_lastProjectsList[i]);

        connect(act, &QAction::triggered, this, &FileBasedProjectP::onLastProjectActionClick);
        m_lastProjectMenu->addAction(act);
    }

    if(m_lastProjectsList.size() == 0)
    {
        m_emptyAction = new QAction("", m_lastProjectMenu);
        m_lastProjectMenu->addAction(m_emptyAction);
        m_emptyAction->setEnabled(false);
    }
}

void FileBasedProjectP::onLastProjectActionClick()
{
    QAction *act = static_cast<QAction*>(sender());
    const QString projectPath = act->data().toString();

    if(qApp->keyboardModifiers().testFlag(Qt::ControlModifier))
    {
        emit q->openExternalProject(projectPath);
        return;
    }

    updateRecentList(projectPath);
    q->loadProjectPriv(projectPath);
}

void FileBasedProjectP::onFileChanged(const QString &/*_path*/)
{
    if(m_checkFileChanged)
    {
        q->promtToReloadProject();
    }
}

void FileBasedProjectP::updateRecentList(const QString &_path)
{
    int index = -1;
    for(int i = 0 ; i < m_lastProjectsList.size(); i++)
    {
        if(_path.toUpper() == m_lastProjectsList.at(i).toUpper())
        {
            index = i;
            break;
        }
    }

    if(index != -1)
    {
        m_lastProjectsList.removeAt(index);
    }

    m_lastProjectsList.insert(0, _path);

    while(m_lastProjectsList.size() > m_lastProjectMaxCount)
    {
        m_lastProjectsList.removeLast();
    }

    recreateActions();
}

void FileBasedProjectP::createFSWatcher()
{
    if(m_fsWatcher) delete m_fsWatcher;
    m_fsWatcher = new QFileSystemWatcher(this);
    connect(m_fsWatcher, &QFileSystemWatcher::fileChanged, this, &FileBasedProjectP::onFileChanged);
    m_fsWatcher->addPath(m_currentProjectPath);
}



bool FileBasedProjectP::eventFilter(QObject *watched, QEvent *event)
{
    //фильтруем события родительского виджета, чтоб словить события смены языка и смены стиля
    if(watched == m_parent)
    {
        if(event->type() == QEvent::LanguageChange)
        {
            updateLanguage();
        } else if(event->type() == QEvent::StyleChange)
        {
            updateStyle();
        }
    }

    return QObject::eventFilter(watched, event);
}

}
