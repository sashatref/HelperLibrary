#pragma once

#include <QDialog>

#include "../../export.h"

namespace Ui {
class SelectListDialog;
}

namespace HelperLibraryNS
{

struct SelectListDialogP;
class HELPERLIBRARY_EXPORT SelectListDialog : public QDialog
{
    Q_OBJECT
    SelectListDialogP *p;
public:
    explicit SelectListDialog(QWidget *parent = nullptr);
    ~SelectListDialog();

    void setMultiSelection(bool _enabled);

    template<class Type>
    void setData(const QMap<QString, Type> &_items)
    {
        QVariantMap map;

        for(auto it = _items.begin(); it != _items.end(); ++it)
        {
            map[it.key()] = QVariant::fromValue(it.value());
        }

        setData(map);
    }

    void setData(const QStringList &_items);
    void setData(const QList<QPair<QString, QVariant>> &_items);
    void setData(const QVariantMap &_items);

    QStringList getSelectedDataAsList() const;
    QVariantMap getSelectedDataAsMap() const;

    //этот метод необходимо использовать если setMultiSelection(false);
    QString getSelectedItem() const;

    template<class Type>
    QMap<QString, Type> getSelectedDataAsMap() const
    {
        QVariantMap map = getSelectedDataAsMap();

        QMap<QString, Type> out;

        for(auto it = map.begin(); it != map.end(); ++it)
        {
            out[it.key()] = it.value().value<Type>();
        }

        return out;
    }

    QList<QPair<QString, QVariant>> getSelectedData() const;

    static QString getSelectedItemDialog(const QStringList &_data, const QString &_title, QWidget *_parent, bool *_isOk = nullptr);

private slots:
    void on_applyButton_clicked();
    void on_cancelButton_clicked();
    void on_selectAllButton_clicked();
    void on_resetAllBtn_clicked();

    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);

private:
    void applyMultiSelectMode();
    Ui::SelectListDialog *ui;
};

}
