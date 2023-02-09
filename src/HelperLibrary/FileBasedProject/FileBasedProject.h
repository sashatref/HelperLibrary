#pragma once

#include <QObject>

#include "../Widgets/isavewidget.h"
#include "../export.h"

class QToolBar;
class QMenu;
class QLineEdit;

/*!
 *  Класс для работы с проектами
 *  Реализует функционал: создать проект, загрузить проект, сохранить,
 *      сохранить как..., открыть каталог с проектом.
 *  Хранит последний загруженные проект и список последних проектом.
 *
 *  Для и использования необходимо лишь перегрузить виртуальные функции loadProject, saveProject
 *  После внесения изменений в проект, необходимо вызвать setChangedFlag(true).
 */

namespace HelperLibraryNS
{

class FileBasedProjectP;
class HELPERLIBRARY_EXPORT FileBasedProject : public QObject, public ISaveWidget
{
    Q_OBJECT
    friend class FileBasedProjectP;
public:
    enum DialogResult
    {
        rNotChanded = -1,
        rSaveAndClose = 0,
        rCloseWithoutSave = 1,
        rCancel = 2
    };
    Q_ENUM(DialogResult)

    enum FileFormat
    {
        ffXml,
        ffJson,
        ffBin
    };
    Q_ENUM(FileFormat)

    FileBasedProject(QWidget *_parent);
    ~FileBasedProject() override;

    void setAutoLoadLastProject(bool _autoLoad);

    void setCheckFileChanges(bool _check);

    void setLastProjectsMaxCount(int _count);

    DialogResult checkProjectForSave(bool _withCancel = true);
    void promtToReloadProject();

    void setFileExt(const QString &_filter);    //устанавалиет формат проекта, используется в диалогах загрузки/сохранения
    void setFileExt(FileFormat _fileFormat);    //выбор предустановленного формата проекта

    bool hasChangesSinceSaved() const;  //флаг указывает были ли изменения после последнего сохранения/загрузки

    void setChangedFlag(bool _isChanged);   //устанавалиает флаг об изменениях в проекте после последней загрузки/соъранения

    QToolBar *getToolBar();     //получить тулбар с кнопками Создать, загрузить, сохранить, сохранить как, открыть каталог
    QLineEdit *getCurrentProjectEdit(); //QLineEdit с текущим проектом и состоянием "изменен/не изменен"

    QMenu *createLastProjectsMenu();

    QString getCurrentProjectPath() const;

    QString getDisplayCurrentProjectPath() const;   //путь к проекту с звездочкой в случае наличия изменений

    bool getEditMode() const;
    void setEditMode(bool _editMode);

public slots:
    void loadFile(const QString &_filePath);
    void emitSaveProjectState();

signals:
    void message(const QString &_text, QtMsgType _type);
    void projectLoaded();

    void projectPreload(const QString &_projectPath);
    void loadStateForProject(const QString &_projectPath);
    void saveStateForProject(const QString &_projectPath);

    void projectPathChanged(const QString &_rawPath);
    void projectDisplayPathChanged(const QString &_displayPath);

    void openExternalProject(const QString &_path);

public slots:
    void createNew(bool _withPromt = true);
    void load();
    void save();
    void saveAs();
    void openInExplorer();
    void reloadFromDisk();

protected:
    virtual void loadProject(const QByteArray &_data, const QString &_projectPath) = 0;
    virtual QByteArray saveProject(const QString &_projectPath) = 0;
    virtual void createEmptyProject(const QString &_projectPath) = 0;


private:
    FileBasedProjectP *p;

    void loadProjectPriv(QString _fileName);
    void saveProjectPriv(QString _fileName);

    void emitProjectPathChanged();

public:
    virtual QString getWidgetUniqueName() const override;
    virtual void loadState(const LayoutSaver &_saver) override;
    virtual void saveState(LayoutSaver &_saver) const override;
};

}

