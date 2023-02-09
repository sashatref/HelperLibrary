#include "variantmapeditor.h"
#include "ui_variantmapeditor.h"

#include "priv/variantmapmodel.h"
#include "../../Styles/iconsenum.h"
#include "../../converterfunctions.h"
#include "../../helperscontainter.h"

#include <QSortFilterProxyModel>

namespace HelperLibraryNS
{

VariantMapEditor::VariantMapEditor(QWidget *parent) :
    ExtendedWidget(parent),
    ui(new Ui::VariantMapEditor)
{
    ui->setupUi(this);

    m_model = new VariantMapModel(this);

    m_proxyModel = new QSortFilterProxyModel(this);
    m_proxyModel->setSourceModel(m_model);
    ui->tableView->setModel(m_proxyModel);

    initAll();
}

VariantMapEditor::~VariantMapEditor()
{
    delete ui;
}

void VariantMapEditor::setVariantMap(const QVariantMap &_map)
{
    m_model->setVariantMap(_map);
}

QVariantMap VariantMapEditor::getVariantMap() const
{
    return m_model->getVariantMap();
}

void VariantMapEditor::setItems(const QList<QPair<int, QString> > &_items)
{
    QList<QPair<QString, QVariant>> data;

    for(auto &it : _items)
    {
        data << qMakePair(QString::number(it.first), it.second);
    }

    m_model->setItems(data);
}

QList<QPair<int, QString> > VariantMapEditor::getItems() const
{
    QList<QPair<int, QString> > out;

    auto data = m_model->getItems();

    for(auto &it : data)
    {
        out << qMakePair(it.first.toInt(), it.second.toString());
    }

    return out;
}

void VariantMapEditor::on_addRowButton_clicked()
{
    m_model->addEmptyRow();
}


void VariantMapEditor::on_removeRowBtn_clicked()
{
    //список выбранных индексов прокси модели
    QModelIndexList selected = ui->tableView->selectionModel()->selectedIndexes();

    //список выбранных индексов исходной модели
    QModelIndexList sourceList;

    for(auto &index : selected)
    {
        sourceList << m_proxyModel->mapToSource(index);
    }

    QList<int> rows;    //список выбранных номеров строк исходной модели
    for(auto &index : sourceList)
    {
        rows << index.row();
    }

    m_model->removeRowsWithNums(rows);
}

void VariantMapEditor::loadState(const LayoutSaver &_saver)
{
    _saver.load(ui->tableView->horizontalHeader(), "horizontalHeader");
}

void VariantMapEditor::saveState(LayoutSaver &_saver) const
{
    _saver.save(ui->tableView->horizontalHeader(), "horizontalHeader");
}

void VariantMapEditor::on_clearButton_clicked()
{
    int res = QMessageBox::question(this, tr("Уверены?"),
                                    tr("Очистить таблицу?"));
    if(res == QMessageBox::Yes)
    {
        m_model->clear();
    }
}

void VariantMapEditor::updateLanguage()
{
    ui->retranslateUi(this);
}

void VariantMapEditor::updateStyle()
{
    ui->addRowButton->setIcon(IconsEnum::getIcon(IconsEnum::SP_Plus2));
    ui->removeRowBtn->setIcon(IconsEnum::getIcon(IconsEnum::SP_Minus2));

    ui->clearButton->setIcon(IconsEnum::getIcon(IconsEnum::SP_Erase1));
}


}







