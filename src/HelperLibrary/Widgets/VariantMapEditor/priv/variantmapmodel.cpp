#include "variantmapmodel.h"




VariantMapModel::VariantMapModel(QObject *_parent):
    QAbstractTableModel(_parent)
{

}

void VariantMapModel::addEmptyRow()
{
    beginResetModel();

    m_data << qMakePair(QString::number(m_data.size()), QVariant("value"));

    endResetModel();
}

void VariantMapModel::clear()
{
    beginResetModel();

    m_data.clear();

    endResetModel();
}

void VariantMapModel::removeRowsWithNums(const QList<int> &_rows)
{
    beginResetModel();

    QList<int> newList = _rows.toSet().toList();

    qSort(newList);

    for(int rowIndex : newList)
    {
        m_data.removeAt(rowIndex);
    }

    endResetModel();
}

void VariantMapModel::setVariantMap(const QVariantMap &_map)
{
    QList<QPair<QString, QVariant> > data;

    for(auto it = _map.begin(); it != _map.end(); ++it)
    {
        data << qMakePair(it.key(), it.value());
    }

    setItems(data);
}

QVariantMap VariantMapModel::getVariantMap() const
{
    QVariantMap out;

    for(auto &item : m_data)
    {
        out[item.first] = item.second;
    }

    return out;
}

void VariantMapModel::setItems(const QList<QPair<QString, QVariant> > &_data)
{
    beginResetModel();

    m_data = _data;

    endResetModel();
}

QList<QPair<QString, QVariant> > VariantMapModel::getItems() const
{
    return m_data;
}

int VariantMapModel::rowCount(const QModelIndex &/*parent*/) const
{
    return m_data.size();
}

int VariantMapModel::columnCount(const QModelIndex &/*parent*/) const
{
    return 2;
}

QVariant VariantMapModel::data(const QModelIndex &index, int role) const
{
    if(!isValidIndex(index)) return QVariant();

    const int row = index.row();
    const int column = index.column();

    QVariant out;

    switch(role)
    {
        case Qt::DisplayRole:
        case Qt::EditRole:
        {
            switch(column)
            {
            case keyColumn:
                out = m_data.at(row).first;
                break;
            case valueColumn:
                out = m_data.at(row).second;
                break;
            }
        }

        break;
    }

    return out;
}

bool VariantMapModel::isValidIndex(const QModelIndex &_index) const
{
    if(!_index.isValid())
    {
        return false;
    }

    if(_index.column() < 0 || _index.column() > 1)
    {
        return false;
    }

    if(_index.row() < 0 || _index.row() > m_data.size() - 1)
    {
        return false;
    }

    return true;
}


QVariant VariantMapModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    QVariant out;

    if(orientation != Qt::Horizontal)
    {
        return QAbstractTableModel::headerData(section, orientation, role);
    }

    if(role != Qt::DisplayRole)
    {
        return QAbstractTableModel::headerData(section, orientation, role);
    }

    switch(section)
    {
    case keyColumn:
        out = tr("Ключ");
        break;
    case valueColumn:
        out = tr("Значение");
        break;
    }

    return out;
}


Qt::ItemFlags VariantMapModel::flags(const QModelIndex &index) const
{
    return QAbstractTableModel::flags(index) | Qt::ItemIsEditable;
}


bool VariantMapModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(!isValidIndex(index))
    {
        return false;
    }

    const int row = index.row();
    const int column = index.column();

    if(role == Qt::EditRole)
    {
        switch(column)
        {
        case keyColumn:
            m_data[row].first = value.toString();
            break;
        case valueColumn:
            m_data[row].second = value;
            break;
        }

        return true;
    }

    return false;
}
