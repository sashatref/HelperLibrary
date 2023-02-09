#include "resourceexplorer.h"
#include "ui_resourceexplorer.h"
#include "../functions.h"
#include "../Styles/iconsenum.h"


ResourceExplorer::ResourceExplorer(QWidget *parent) :
    ExtendedMainWindow  (),
    ui                  (new Ui::ResourceExplorer)
{
    ui->setupUi(this);
    setParent(parent);

    setPromtToClose(false);

    reloadTree();

    initAll();
}

ResourceExplorer::~ResourceExplorer()
{
    delete ui;
}

QString ResourceExplorer::getSelectedFile() const
{
    QList<QListWidgetItem*> selectedArr = ui->listWidget->selectedItems();
    if(selectedArr.size() == 0)
    {
        return QString();
    }

    return selectedArr.first()->data(Qt::UserRole).toString();
}

void ResourceExplorer::setSelectedFile(const QString &_file)
{
    if(_file.isEmpty())
    {
        return;
    }

    QFileInfo fInfo(_file);
    QString filePath = fInfo.absolutePath();

    auto it = m_nodeMap.find(filePath);
    if(it == m_nodeMap.end())
    {
        return;
    }

    it.value()->setSelected(true);
    setListFiles(it.value()->data(0, FilteredFilesRole).value<QFileInfoList>());
    setListWidgetSelected(_file);
}

void ResourceExplorer::setListFiles(const QFileInfoList &_files)
{
    ui->listWidget->clear();

    for(auto &file : _files)
    {
        QIcon icon(file.absoluteFilePath());
        QImage img(file.absoluteFilePath());

        QString tooltip;

        tooltip += tr("Размер файла: %1\n").arg(Text::fileSizeToString(file.size()));

        if(!img.isNull())
        {
            QSize size = img.size();
            tooltip += tr("Размер изображения: %1x%2\n").arg(size.width()).arg(size.height());
        }
        tooltip += file.absoluteFilePath();

        QListWidgetItem *item = new QListWidgetItem();
        item->setText(file.fileName());
        item->setData(Qt::UserRole, file.absoluteFilePath());
        item->setIcon(icon);
        item->setToolTip(tooltip);
        ui->listWidget->addItem(item);
    }
}

void ResourceExplorer::updateLanguage()
{
    ui->retranslateUi(this);
}

void ResourceExplorer::updateStyle()
{
    ui->reloadButton->setIcon(IconsEnum::getIcon(IconsEnum::SP_Reload2));
}

void ResourceExplorer::initUiComponets()
{

}

void ResourceExplorer::loadState(const LayoutSaver &_saver)
{
    _saver.loadMainWindow(this, "mw");
    _saver.load(ui->splitter, "splitter1");
    _saver.load(ui->filterWidget, "filterWidget");
    _saver.load(ui->treeWidget->header(), "treeWidgetHeader");
}

void ResourceExplorer::saveState(LayoutSaver &_saver) const
{
    _saver.saveMainWindow(this, "mw");
    _saver.save(ui->splitter, "splitter1");
    _saver.save(ui->filterWidget, "filterWidget");
    _saver.save(ui->treeWidget->header(), "treeWidgetHeader");
}

void ResourceExplorer::initConnections()
{
    connect(ui->listWidget, &QListWidget::itemDoubleClicked, this, &ResourceExplorer::listWidgetItemDoubleClicked);
}


void ResourceExplorer::listWidgetItemDoubleClicked(QListWidgetItem *item)
{
    if(item == nullptr)
    {
        return;
    }

    QString filePath = item->data(Qt::UserRole).toString();
    emit fileDoubleClicked(filePath);
}


void ResourceExplorer::createSubItems(const QString &_basePath, QTreeWidgetItem *_parent)
{
    QDir dir(_basePath);
    QStringList entries = dir.entryList(QStringList(), QDir::Dirs, QDir::Name);

    QFileInfo fInfo(_basePath);
    QString title = _basePath == ":" ? "<resource root>" : fInfo.fileName();
    QFileInfoList fInfoList = QDir(_basePath).entryInfoList(QDir::Files, QDir::Name);

    QTreeWidgetItem *node = new QTreeWidgetItem();
    node->setText(0, title);
    node->setData(0, AllFilesRole, QVariant::fromValue(fInfoList));
    node->setData(0, FilteredFilesRole, QVariant::fromValue(fInfoList));
    node->setText(1, QString::number(fInfoList.size()));
    _parent->addChild(node);
    m_nodeMap[_basePath] = node;

    for(auto &it : entries)
    {
        createSubItems(_basePath + "/" + it, node);
    }
}

QFileInfoList ResourceExplorer::filtered(const QFileInfoList &_arr) const
{
    QFileInfoList out;

    for(const QFileInfo &it : _arr)
    {
        if(ui->filterWidget->checkText(it.fileName()))
        {
            out << it;
        }
    }

    return out;
}



void ResourceExplorer::reloadTree()
{
    ui->treeWidget->clear();
    m_nodeMap.clear();

    createSubItems(":", ui->treeWidget->invisibleRootItem());
    ui->treeWidget->expandAll();

    ui->treeWidget->header()->resizeSections(QHeaderView::ResizeToContents);
}

void ResourceExplorer::setListWidgetSelected(const QString &_filePath)
{
    for(int i = 0 ; i < ui->listWidget->count(); i++)
    {
        QListWidgetItem *item = ui->listWidget->item(i);
        if(item->data(Qt::UserRole).toString() == _filePath)
        {
            item->setSelected(true);
            return;
        }
    }
}

void ResourceExplorer::on_reloadButton_clicked()
{
    reloadTree();
}

void ResourceExplorer::on_treeWidget_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem * /*previous*/)
{
    if(current)
    {
        setListFiles(current->data(0, FilteredFilesRole).value<QFileInfoList>());
    }
}

bool itemHasFilteredFiles(QTreeWidgetItem *_item)
{
    return _item->data(0, ResourceExplorer::FilteredFilesRole).value<QFileInfoList>().size();
}

//bool ResourceExplorer::isChildrenEmpty(QTreeWidgetItem *_item)
//{
//    bool hasChildNotEmpty = false;

//    for(int i = 0 ; i < _item->childCount(); i++)
//    {
//        QTreeWidgetItem *child = _item->child(i);

//        bool hasFiles = itemHasFilteredFiles(child);

//        bool childrendEmpty = isChildrenEmpty(child);

//        if(hasFiles || !childrendEmpty)
//        {
//            hasChildNotEmpty = true;
//        }
//    }
//}

void ResourceExplorer::on_filterWidget_startFilter()
{
    {
        QTreeWidgetItemIterator it(ui->treeWidget, QTreeWidgetItemIterator::All);
        while (*it)
        {
            QFileInfoList filteredArr = filtered((*it)->data(0, AllFilesRole).value<QFileInfoList>());
            (*it)->setData(0, FilteredFilesRole, QVariant::fromValue(filteredArr));
            (*it)->setText(1, QString::number(filteredArr.size()));

            ++it;
        }
    }

    QList<QTreeWidgetItem *> selectedArr = ui->treeWidget->selectedItems();
    if(selectedArr.size())
    {
        on_treeWidget_currentItemChanged(selectedArr.first(), nullptr);
    }
}

void ResourceExplorer::on_treeWidget_customContextMenuRequested(const QPoint &pos)
{
    QMenu menu;

    menu.addAction(tr("Развернуть все"), this, [=]
    {
        ui->treeWidget->expandAll();
    });
    menu.addAction(tr("Свернуть все"), this, [=]
    {
        ui->treeWidget->collapseAll();
    });

    menu.exec(ui->treeWidget->mapToGlobal(pos));
}












