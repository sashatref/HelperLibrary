#pragma once

#include "FileBasedProject.h"

class QFileSystemWatcher;

namespace HelperLibraryNS
{

class FileBasedProject;
class FileBasedProjectP : public QObject
{
    Q_OBJECT
public:
    FileBasedProject *q;
    FileBasedProjectP(FileBasedProject *_q);

    QString m_fileFilter;       //фильтр для загрузки/сохранения файлов, напр "XML(*.xml)"

    bool m_hasChangedSinceSave = false; //флаг отображает, если в проекте были изменения после последнего сохранения
    bool m_editMode = false;    //флаг отображает, можно ли сохранить проект в тот же файл кнопкой "Сохранить"

    QString m_lastSavePath;         //последний путь сохранения файла
    QString m_currentProjectPath;   //путь к текущему проекту
    QStringList m_loadedProjects;

    QStringList m_lastProjectsList; //список недавних файлов
    int m_lastProjectMaxCount = 20; //максимальное количество недавних файлов

    QWidget *m_parent;              //родительский элекмент, относительно которого будут отображаться диалоги и
                                    //для которого будут созданы все виджеты

    QToolBar *m_toolbar = nullptr;  //тулбар с кнопками
    QLineEdit *m_currentProjectEdit = nullptr;  //строка состояния текущего проекта

    QAction *m_loadAction = nullptr;
    QAction *m_saveAction = nullptr;
    QAction *m_saveAsAction = nullptr;
    QAction *m_openInBrowserAction = nullptr;
    QAction *m_createNewAction = nullptr;
    QAction *m_reloadProject = nullptr;

    QMenu *m_lastProjectMenu = nullptr;
    QAction *m_emptyAction = nullptr;   //кнопка, которая создается, если список недавних файлов пуст

    QFileSystemWatcher *m_fsWatcher = nullptr;
    bool m_checkFileChanged = true;
    bool m_changesFileFlag = false;

    bool m_autoloadLastProject = true;

    void setCurrentProjectPath(const QString &_path);

    void createToolBar();
    void createCurrentProjEdit();

    void updateLanguage();
    void updateStyle();

    QMenu *createLastProjectsMenu();

    /*!
     * \brief recreateActions заново создает все QAction для недавно использованных файлов
     */
    void recreateActions();

    /*!
     * \brief updateRecentList обновляет список недавно использованных файлов
     * \param _path
     */
    void updateRecentList(const QString &_path);

    void createFSWatcher();

public slots:
    void onDisplayPathChanged(const QString &_path);

    void onLastProjectActionClick();

    void onFileChanged(const QString &_path);

    // QObject interface
public:
    virtual bool eventFilter(QObject *watched, QEvent *event) override;
};

}
