#pragma once

#include <QDialog>

#include "../export.h"
#include "../Widgets/extendeddialog.h"

namespace Ui {
class ResourceExplorerDialog;
}


class HELPERLIBRARY_EXPORT ResourceExplorerDialog : public ExtendedDialog
{
    Q_OBJECT
public:
    explicit ResourceExplorerDialog(QWidget *parent = nullptr);
    ~ResourceExplorerDialog();

    void setSelectedFile(const QString &_file);
    QString getSelectedFile() const;

private:
    Ui::ResourceExplorerDialog *ui;

private slots:
    void on_applyButton_clicked();
    void on_cancelButton_clicked();

    // ISaveWidget interface
public:
    virtual void loadState(const LayoutSaver &_saver) override;
    virtual void saveState(LayoutSaver &_saver) const override;
};

