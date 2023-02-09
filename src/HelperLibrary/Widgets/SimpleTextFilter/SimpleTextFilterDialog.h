#pragma once

#include <QDialog>

#include "../../SimpleTextFilter.h"

namespace Ui {
class SimpleTextFilterDialog;
}

namespace HelperLibraryNS
{

class HELPERLIBRARY_EXPORT SimpleTextFilterDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SimpleTextFilterDialog(QWidget *parent = nullptr);
    ~SimpleTextFilterDialog();

    void setFilter(const SimpleTextFilter &_filter);
    void setAvailableRules(const QStringList &_rules);

    SimpleTextFilter getFilter();

    QVariantMap savePresets() const;
    void loadPresets(const QVariantMap &_m, const QString &_presetName);

private slots:
    void on_applyButton_clicked();

    void on_ruleList_customContextMenuRequested(const QPoint &pos);
    void onRowInserted(const QModelIndex &parent, int first, int last);

    void on_enableCheckBox_toggled(bool checked);

    void savePreset(const QString &_name);
    void applyPreset(const QVariant &_v);

private:
    void addRules(const QStringList &_rules);

    Ui::SimpleTextFilterDialog *ui;
};

}
