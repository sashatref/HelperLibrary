#include "SimpleTextFilterDialog.h"
#include "ui_SimpleTextFilterDialog.h"
#include "releaseassert.h"
#include "../SimplePresetCombo/SimplePresetCombo.h"
#include "../../Styles/iconsenum.h"

namespace HelperLibraryNS
{

SimpleTextFilterDialog::SimpleTextFilterDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SimpleTextFilterDialog)
{
    ui->setupUi(this);

    connect(ui->ruleList->model(), &QAbstractItemModel::rowsInserted, this, &SimpleTextFilterDialog::onRowInserted);
    connect(ui->presetCombo, &SimplePresetCombo::needSaveItem, this, &SimpleTextFilterDialog::savePreset);
    connect(ui->presetCombo, &SimplePresetCombo::loadPreset, this, &SimpleTextFilterDialog::applyPreset);

    ui->applyButton->setIcon(IconsEnum::applyButtonIcon());
}

SimpleTextFilterDialog::~SimpleTextFilterDialog()
{
    delete ui;
}

void SimpleTextFilterDialog::setFilter(const SimpleTextFilter &_filter)
{
    ui->enableCheckBox->setChecked(_filter.enabled);
    ui->filterTypeCombo->setCurrentIndex(_filter.checkType);
    ui->sensitivityComboBox->setCurrentIndex(_filter.sensitivity);
    ui->ruleList->clear();

    addRules(_filter.rules);

    on_enableCheckBox_toggled(_filter.enabled);
}

void SimpleTextFilterDialog::setAvailableRules(const QStringList &_rules)
{
    ui->newRuleList->clear();
    ui->newRuleList->addItems(_rules);
}

SimpleTextFilter SimpleTextFilterDialog::getFilter()
{
    SimpleTextFilter filter;
    filter.enabled = ui->enableCheckBox->isChecked();
    filter.checkType = static_cast<SimpleTextFilter::CheckType>(ui->filterTypeCombo->currentIndex());
    filter.sensitivity = static_cast<Qt::CaseSensitivity>(ui->sensitivityComboBox->currentIndex());

    for(int i = 0 ; i < ui->ruleList->count(); i++)
    {
        QListWidgetItem *item = ui->ruleList->item(i);
        filter.rules << item->text();
    }

    return filter;
}

QVariantMap SimpleTextFilterDialog::savePresets() const
{
    return ui->presetCombo->savePresets();
}

void SimpleTextFilterDialog::loadPresets(const QVariantMap &_m, const QString &_presetName)
{
    ui->presetCombo->loadPresets(_m, _presetName);
}


void SimpleTextFilterDialog::on_applyButton_clicked()
{
    accept();
}

void SimpleTextFilterDialog::on_ruleList_customContextMenuRequested(const QPoint &pos)
{
    QList<QListWidgetItem*> selected = ui->ruleList->selectedItems();

    QMenu menu;

    menu.addAction(tr("Добавить"), [=]
    {
        addRules({ "New rule" });
    });

    if(selected.size())
    {
        menu.addAction(tr("Удалить"), [=]
        {
            int res = QMessageBox::question(this, tr("Удалить?"), tr("Удалить выбранные правила? Количество [%1]")
                                  .arg(selected.size()));
            if(res == QMessageBox::Yes)
            {
                qDeleteAll(selected);
            }
        });
    }

    menu.exec(ui->ruleList->mapToGlobal(pos));
}

void SimpleTextFilterDialog::onRowInserted(const QModelIndex &/*parent*/, int first, int last)
{
    for(int i = first; i <= last ; i++)
    {
        QListWidgetItem *item = ui->ruleList->item(i);
        R_ASSERT(item);
        item->setFlags(item->flags() | Qt::ItemIsEditable);
    }
}

void SimpleTextFilterDialog::addRules(const QStringList &_rules)
{
    for(auto &it : _rules)
    {
        QListWidgetItem *item = new QListWidgetItem();
        item->setText(it);
        item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable);
        ui->ruleList->addItem(item);
    }
}

void SimpleTextFilterDialog::on_enableCheckBox_toggled(bool checked)
{
    ui->groupBox->setEnabled(checked);
    ui->groupBox_2->setEnabled(checked);
    ui->groupBox_3->setEnabled(checked);
    ui->groupBox_4->setEnabled(checked);
}

void SimpleTextFilterDialog::savePreset(const QString &_name)
{
    ui->presetCombo->addPreset(_name, getFilter().save());
}

void SimpleTextFilterDialog::applyPreset(const QVariant &_v)
{
    SimpleTextFilter filter;
    filter.load(_v);
    setFilter(filter);
}

}






