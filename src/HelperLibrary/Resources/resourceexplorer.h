#pragma once

#include "../export.h"
#include "../Widgets/extendedmainwindow.h"

class QTreeWidgetItem;

namespace Ui {
class ResourceExplorer;
}

class HELPERLIBRARY_EXPORT ResourceExplorer : public ExtendedMainWindow
{
    Q_OBJECT

public:
    enum DataRoles
    {
        AllFilesRole = Qt::UserRole,
        FilteredFilesRole
    };

    explicit ResourceExplorer(QWidget *parent = nullptr);
    ~ResourceExplorer();

    void reloadTree();


    QString getSelectedFile() const;
    void setSelectedFile(const QString &_file);

private:
    Ui::ResourceExplorer *ui;
    QMap<QString, QTreeWidgetItem*> m_nodeMap;

    void setListFiles(const QFileInfoList &_files);
    void listWidgetItemDoubleClicked(QListWidgetItem *item);

    void setListWidgetSelected(const QString &_filePath);
    void createSubItems(const QString &_basePath, QTreeWidgetItem *_parent);

    QFileInfoList filtered(const QFileInfoList &_arr) const;

    bool isChildrenEmpty(QTreeWidgetItem *_item);


signals:
    void fileDoubleClicked(const QString &_path);

public:
    virtual void updateLanguage() override;
    virtual void updateStyle() override;
    virtual void initUiComponets() override;
    virtual void loadState(const LayoutSaver &_saver) override;
    virtual void saveState(LayoutSaver &_saver) const override;
    virtual void initConnections() override;

private slots:
    void on_treeWidget_customContextMenuRequested(const QPoint &pos);
    void on_filterWidget_startFilter();
    void on_reloadButton_clicked();
    void on_treeWidget_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous);
};

