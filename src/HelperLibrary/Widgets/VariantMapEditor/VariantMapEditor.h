#pragma once

#include <QWidget>
#include "../../export.h"
#include "../extendedwidget.h"

namespace Ui {
class VariantMapEditor;
}

class VariantMapModel;
class QSortFilterProxyModel;

namespace HelperLibraryNS
{

class HELPERLIBRARY_EXPORT VariantMapEditor : public ExtendedWidget
{
    Q_OBJECT
public:
    explicit VariantMapEditor(QWidget *parent = nullptr);
    ~VariantMapEditor();

    void setVariantMap(const QVariantMap &_map);
    QVariantMap getVariantMap() const;

    void setItems(const QList<QPair<int, QString>> &_items);
    QList<QPair<int, QString>> getItems() const;

private slots:
    void on_addRowButton_clicked();
    void on_removeRowBtn_clicked();

    void on_clearButton_clicked();

private:
    Ui::VariantMapEditor *ui;

    VariantMapModel *m_model = nullptr;
    QSortFilterProxyModel *m_proxyModel = nullptr;

    // ISaveWidget interface
public:
    virtual void loadState(const LayoutSaver &_saver) override;
    virtual void saveState(LayoutSaver &_saver) const override;
    virtual void updateLanguage() override;
    virtual void updateStyle() override;
};
}
