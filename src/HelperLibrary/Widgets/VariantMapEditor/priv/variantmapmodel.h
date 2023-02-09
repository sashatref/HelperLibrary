#pragma once

#include "project_pch.h"

class VariantMapModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    enum
    {
        keyColumn = 0,
        valueColumn = 1
    };

    VariantMapModel(QObject *_parent = nullptr);

    void addEmptyRow();

    void clear();

    void removeRowsWithNums(const QList<int> &_rows);

    void setVariantMap(const QVariantMap &_map);
    QVariantMap getVariantMap() const;

    void setItems(const QList<QPair<QString, QVariant>> &_data);
    QList<QPair<QString, QVariant>> getItems() const;

public:
    virtual int rowCount(const QModelIndex &parent) const override;
    virtual int columnCount(const QModelIndex &parent) const override;
    virtual QVariant data(const QModelIndex &index, int role) const override;
    virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    virtual Qt::ItemFlags flags(const QModelIndex &index) const override;
    virtual bool setData(const QModelIndex &index, const QVariant &value, int role) override;

private:
    bool isValidIndex(const QModelIndex &_index) const;

    QList<QPair<QString, QVariant>> m_data; //key, value

    // QAbstractItemModel interface

};
