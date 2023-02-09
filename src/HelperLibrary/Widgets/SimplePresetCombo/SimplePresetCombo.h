#pragma once

#include <QWidget>

#include "../../export.h"

namespace Ui {
class SimplePresetCombo;
}

namespace HelperLibraryNS
{

class HELPERLIBRARY_EXPORT SimplePresetCombo : public QWidget
{
    Q_OBJECT
public:
    explicit SimplePresetCombo(QWidget *parent = nullptr);
    ~SimplePresetCombo();

    void loadPresets(const QVariantMap &_m, const QString &_currentPreset);
    QVariantMap savePresets() const;

    void addPreset(const QString &_name, const QVariant &_data);

signals:
    void needSaveItem(const QString &_presetName);
    void loadPreset(const QVariant &_data);

private slots:
    void on_saveBtn_clicked();
    void on_removeBtn_clicked();

    void on_comboBox_currentIndexChanged(int index);

private:
    Ui::SimplePresetCombo *ui;
};

}
