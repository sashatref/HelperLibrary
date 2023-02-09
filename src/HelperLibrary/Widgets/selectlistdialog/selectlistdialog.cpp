#include "selectlistdialog.h"
#include "ui_selectlistdialog.h"
#include "../../Styles/iconsenum.h"

namespace HelperLibraryNS
{

struct SelectListDialogP
{
    bool multiSelectMode = true;
};

void setCheckedState(QListWidget *_lw, Qt::CheckState _state)
{
    int c = _lw->count();

    for(int i = 0 ; i < c; i++)
    {
        QListWidgetItem *item = _lw->item(i);
        item->setCheckState(_state);
    }
}

SelectListDialog::SelectListDialog(QWidget *parent) :
    QDialog     (parent),
    ui          (new Ui::SelectListDialog),
    p           (new SelectListDialogP())
{
    ui->setupUi(this);

    ui->applyButton->setIcon(IconsEnum::getIcon(IconsEnum::SP_Apply2));
    ui->cancelButton->setIcon(IconsEnum::getIcon(QStyle::SP_DialogCloseButton));

    ui->selectAllButton->setIcon(IconsEnum::getIcon(IconsEnum::SP_Check1));
    ui->resetAllBtn->setIcon(IconsEnum::getIcon(IconsEnum::SP_Uncheck1));

    setMultiSelection(true);
}

SelectListDialog::~SelectListDialog()
{
    delete ui;
}

void SelectListDialog::setMultiSelection(bool _enabled)
{
    p->multiSelectMode = _enabled;

    applyMultiSelectMode();
}

void SelectListDialog::setData(const QStringList &_items)
{
    QList<QPair<QString, QVariant> > list;

    for(auto &item : _items)
    {
        list << qMakePair(item, QVariant());
    }

    setData(list);
}

void SelectListDialog::setData(const QList<QPair<QString, QVariant> > &_items)
{
    ui->listWidget->clear();

    for(auto &it : _items)
    {
        QListWidgetItem *listItem = new QListWidgetItem();

        if(p->multiSelectMode)
        {
            listItem->setFlags(listItem->flags() | Qt::ItemIsUserCheckable);
            listItem->setCheckState(Qt::Checked);
        }

        listItem->setSizeHint(QSize(24, 24));

        listItem->setText(it.first);
        listItem->setData(Qt::UserRole, it.second);
        ui->listWidget->addItem(listItem);
    }
}

void SelectListDialog::setData(const QVariantMap &_items)
{
    QList<QPair<QString, QVariant> > list;

    for(auto it = _items.begin(); it != _items.end(); ++it)
    {
        list << qMakePair(it.key(), it.value());
    }

    setData(list);
}

QStringList SelectListDialog::getSelectedDataAsList() const
{
    QStringList out;

    auto val = getSelectedData();

    for(auto &it : val)
    {
        out << it.first;
    }

    return out;
}

QVariantMap SelectListDialog::getSelectedDataAsMap() const
{
    QVariantMap out;

    auto val = getSelectedData();

    for(auto &it : val)
    {
        out[it.first] = it.second;
    }

    return out;
}

QString SelectListDialog::getSelectedItem() const
{
    QList<QListWidgetItem*> selected = ui->listWidget->selectedItems();
    if(selected.size() == 1)
    {
        return selected.first()->text();
    }

    return QString();
}

QList<QPair<QString, QVariant> > SelectListDialog::getSelectedData() const
{
    QList<QPair<QString, QVariant> > out;

    const int count = ui->listWidget->count();

    for(int i = 0 ; i < count; i++)
    {
        QListWidgetItem *item = ui->listWidget->item(i);
        if(item->checkState() == Qt::Checked)
        {
            out << qMakePair(item->text(), item->data(Qt::UserRole));
        }
    }

    return out;
}

QString SelectListDialog::getSelectedItemDialog(const QStringList &_data, const QString &_title, QWidget *_parent, bool *_isOk)
{
    SelectListDialog dialog(_parent);
    dialog.setMultiSelection(false);
    dialog.setData(_data);
    dialog.setWindowTitle(_title);
    if(dialog.exec() == QDialog::Accepted)
    {
        if(_isOk)
        {
            *_isOk = true;
        }

        return dialog.getSelectedItem();
    }

    if(_isOk)
    {
        *_isOk = false;
    }

    return QString();
}

void SelectListDialog::on_applyButton_clicked()
{
    accept();
}

void SelectListDialog::on_cancelButton_clicked()
{
    reject();
}

void SelectListDialog::on_selectAllButton_clicked()
{
    setCheckedState(ui->listWidget, Qt::Checked);
}

void SelectListDialog::on_resetAllBtn_clicked()
{
    setCheckedState(ui->listWidget, Qt::Unchecked);
}

void SelectListDialog::applyMultiSelectMode()
{
    if(p->multiSelectMode)
    {
        ui->listWidget->setSelectionMode(QAbstractItemView::ExtendedSelection);
        setCheckedState(ui->listWidget, Qt::Checked);
    } else
    {
        ui->listWidget->setSelectionMode(QAbstractItemView::SingleSelection);
        setCheckedState(ui->listWidget, (Qt::CheckState)-1);
    }

    ui->topFrame->setVisible(p->multiSelectMode);
}

void SelectListDialog::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    Q_UNUSED(item);

    if(!p->multiSelectMode)
    {
        accept();
    }
}

}


